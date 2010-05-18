
#include <iostream>

#include <QGraphicsObject>
#include <QPainter>

#include <tower.h>
#include <engineer.h>
#include <tile.h>
#include <device.h>
#include <infoBox.h>
#include <towerCreator.h>
#include <gameState.h>

namespace Sem {

  Tower::Tower(Device* d, Tile* tile,
               std::vector<QImage>& t_r,
               std::vector<QImage>& t_l,
               std::vector<QImage>& t_v,
               std::vector<QImage>& t_h )
                 : towers_r_(t_r),
  towers_l_(t_l),
  towers_v_(t_v),
  towers_h_(t_h) {
    d_ = d;
    tile_ = tile;
    name_ = "Poste telegraphique de region sauvage";
    tower_1_ = NULL;
    tower_2_ = NULL;
    operating_percentage_ = 100;
    message_rate_ = 100;
    range_ = 200;
    width_ = 128;
    height_ = 64;
    tile_width_ = 128;
    tile_height_ = 64;
    ellipse_color_ = QColor(0, 121, 144, 75);
    ellipse_boarder_color_ = QColor(255, 255, 255, 150);
    set_connection_color_ = QColor(255, 0, 0, 150);
    connection_color_ = QColor(255, 255, 0, 200);
    connection_line_width_ = 3;
    true_center_ = QPointF(0, -height_/2);

    // Payment variables
    pay_rate_ = 4;

    total_messages_sent_ = 0;
    total_days_ = 0;
    balance_ = 0;
    total_balance_ = 0;

    speed_1_ = 4;
    speed_2_ = 4;
    speed_3_ = 4;
    speed_4_ = 4;
    speed_5_ = 4;

    connected_to_paris_ = false;
  }

  void Tower::init(){
    engineer_1_ = new Engineer(d_, this);
    engineer_2_ = new Engineer(d_, this);

    tower_image_ = d_->tile_image_loader()->loadImage(TileImageLoader::SEMAPHORE, 0, 0);

    date_created_ = d_->game_state()->current_date();

    set_tile(tile_);
  }

  const QDate& Tower::date_created(){
    return date_created_;
  }

  const QString& Tower::name(){
    return name_;
  }

  Engineer* Tower::engineer_1(){
    return engineer_1_;
  }

  Engineer* Tower::engineer_2(){
    return engineer_2_;
  }

  Tower* Tower::tower_1(){
    return tower_1_;
  }

  Tower* Tower::tower_2(){
    return tower_2_;
  }

  float Tower::operating_percentage(){
    return operating_percentage_;
  }

  float Tower::message_rate(){
    return message_rate_;
  }

  QRectF Tower::boundingRect() const {
    qreal adjust = 2;
    return draw_rect_.adjusted(-adjust, -adjust, adjust, adjust).normalized();
  }

  void Tower::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/){
    if(view_mode_ == RANGE){
      painter->setBrush(QBrush(ellipse_color_));
      painter->setPen(QPen(QBrush(ellipse_boarder_color_), 3.5));
      painter->drawEllipse(true_center_, range_, range_/2.0);
    }



    if(view_mode_ == SET_CONNECTION){
      painter->setPen(QPen(QBrush(set_connection_color_), 5, Qt::DashLine));
      QPointF terminate = d_->tower_creator()->last_hover_tile()->pos();
      terminate = QPointF(terminate.x(), terminate.y() - 32) - pos();
      painter->drawLine(true_center_, terminate);
    }

    if(view_mode_ == CONNECTIONS){
      painter->setPen(QPen(QBrush(connection_color_),
                           connection_line_width_,
                           Qt::DotLine));
      if(tower_1_){
        QPointF other_pos = tower_1_->getTrueCenter() - pos();
        painter->drawLine(true_center_, other_pos);
      }

      if(tower_2_){
        QPointF other_pos = tower_2_->getTrueCenter() - pos();
        painter->drawLine(true_center_, other_pos);
      }
    }

    drawTower(painter);
  }

  void Tower::drawTower(QPainter* painter){
    painter->drawImage(QPoint(-width_/2.0,
                              -height_ - 24),
                       tower_image_);
  }

  void Tower::updateDrawRect(){
    if(view_mode_ == RANGE){
      draw_rect_ = QRectF(-range_, -range_/2.0,
                          range_*2.0, range_);
    }
  }

  Tower::ViewMode Tower::view_mode(){
    return view_mode_;
  }

  void Tower::set_view_mode(ViewMode mode){
    view_mode_ = mode;
  }

  void Tower::set_tile(Tile* tile){
    tile_ = tile;

    // SET NAME
    if(tile_->arrondissement_set()){
      name_ = "Poste telegraphique de " + tile_->arrondissement();
    } else {
      QString x, y;
      x.setNum(tile_->x_index());
      y.setNum(tile_->y_index());
      name_ = "Poste telegraphique " + x + " par " + y;
    }

    // SET POSITION
    setPos(tile->pos());

    // SET RANGE
    range_ = getRangeFromElevation(tile->getPlacementElevation());
  }

  void Tower::hoverEnterEvent(QGraphicsSceneHoverEvent* /*event*/){
    if(view_mode_ == SET_CONNECTION)
      return;

    view_mode_ = RANGE;
    // Update the info box
  }

  void Tower::hoverLeaveEvent(QGraphicsSceneHoverEvent* /*event*/){
    if(view_mode_ == SET_CONNECTION)
      return;

      view_mode_ = NORMAL;
  }

  void Tower::mousePressEvent(QGraphicsSceneMouseEvent* event){
    d_->tower_creator()->mousePressEvent(this, event);

    if(view_mode_ == SET_CONNECTION)
      return;

    view_mode_ = CONNECTIONS;
  }

  // Logic for range: at 0 you get 6, plus a max of 4 for
  // hills, cities, etc.
  int Tower::getRangeFromElevation(int elevation){
    return 5 * tile_width_ + elevation / 500.0 * tile_width_;
  }

  int Tower::getRange(){
    return getRangeFromElevation(tile_->elevation());
  }

  void Tower::beginSettingTower(Connection type){
    current_connection_set_ = type;
    view_mode_ = SET_CONNECTION;
  }

  void Tower::setConnectingTower(Tower* tower, Connection connection){
    if(tower_1_ == NULL && tower_2_ == NULL){
      startTimer(2500);
    }

    if(connection == TOWER_1)
      tower_1_ = tower;
    else if(connection == TOWER_2)
      tower_2_ = tower;
    else
      std::cerr << "Oh fuck" << std::endl;

    view_mode_ = NORMAL;
  }

  QPointF Tower::getTrueCenter(){
    return pos() + true_center_;
  }

  Tile* Tower::tile(){
    return tile_;
  }

  void Tower::timerEvent(QTimerEvent* /*event*/){
    if(state_ == HORIZONTAL ||
       state_ == VERTICAL){
      if(qrand() % 2 == 0)
        state_ = RIGHT;
      else
        state_ = LEFT;
    } else {
      if(qrand() % 2 == 0)
        state_ = HORIZONTAL;
      else
        state_ = VERTICAL;
    }

    switch(state_){
    case HORIZONTAL:
      tower_image_ = towers_h_[qrand() % 11];
      break;
    case VERTICAL:
      tower_image_ = towers_v_[qrand() % 6];
      break;
    case RIGHT:
      tower_image_ = towers_r_[qrand() % 3];
      break;
    case LEFT:
      tower_image_ = towers_l_[qrand() % 5];
      break;
    }

    update();
  }

  void Tower::updateValues(int days){
    checkConnectedToParis();

    // Based on settings, determine how many messages
    // this tower sent.
    // If it is on a city square,
    // and is connected to Paris
    // it gets money.
    total_days_ += days;
    int hours_operating;
    // If summer...
    if(d_->game_state()->current_date().month() >= 4 &&
       d_->game_state()->current_date().month() <= 9 ) {
      hours_operating = 6 * days;
    } else {
      hours_operating = 3 * days;
    }

    message_rate_ = getMessageRate();
    accuracy_ = getAccuracy();

    int messages_sent;
    if(tower_1_ || tower_2_)
      messages_sent = hours_operating * message_rate_ * accuracy_;
    else
      messages_sent = 0;

    if(connected_to_paris_ &&
       tile_->arrondissement() != tr("frontiere") )
      balance_ += messages_sent * GameState::message_price;

    total_messages_sent_ += messages_sent;

    // Subtract the payments for the workers
    balance_ -= pay_rate_ * days * 2;

    total_balance_ += balance_;
  }

  float Tower::getMessageRate(){
    total_time_ = speed_1_ +
                     speed_2_ +
                     speed_3_ +
                     speed_4_ +
                     speed_5_;

    float rate = 60.0 / (float)total_time_;
    return rate;
  }

  float Tower::getAccuracy(){
    float accuracy = (float)(total_time_ - 7) / 53.0;
    int max_pay = GameState::max_pay;

    if(pay_rate_ < 4)
      accuracy -= (float)(4 - pay_rate_) / 4.0;
    else if(pay_rate_ > 4 && pay_rate_ <= max_pay)
      accuracy += (float)(pay_rate_) / max_pay;
    else if (pay_rate_ > max_pay)
      return 1.0;

    if(accuracy < 0.0)
      accuracy = 0.0;

    if(accuracy > 1.0)
      accuracy = 1.0;

    /*
    if(total_time_ <= 7)
      return 0.0;

    if(total_time_ > 60)
      return 1.0;
      */

    return accuracy;
  }

  bool Tower::connected_to_paris(){
    return connected_to_paris_;
  }

  void Tower::checkConnectedToParis(){
    connected_to_paris_ = parisTrace(this);
  }

  bool Tower::parisTrace(Tower* tower){
    if(tower == NULL)
      return false;

    if(tower->tile()->arrondissement() == tr("Paris") ||
       tower->tile()->arrondissement() == tr("Lille") ||
       tower->tile()->arrondissement() == tr("Rennes") ||
       tower->tile()->arrondissement() == tr("Bordeaux") ||
       tower->tile()->arrondissement() == tr("Lyon") ||
       tower->tile()->arrondissement() == tr("Metz")
       )
      return true;

    if(tower->tower_2() == NULL)
      return false;

    return parisTrace(tower->tower_2());
  }

  int Tower::collectMoney(){
    int temp_balance = balance_;
    balance_ = 0;
    return temp_balance;
  }

  void Tower::set_pay_rate(int pay){
    pay_rate_ = pay;
  }

  void Tower::set_speed_1(int speed){ speed_1_ = speed; }
  void Tower::set_speed_2(int speed){ speed_2_ = speed; }
  void Tower::set_speed_3(int speed){ speed_3_ = speed; }
  void Tower::set_speed_4(int speed){ speed_4_ = speed; }
  void Tower::set_speed_5(int speed){ speed_5_ = speed; }

  int Tower::total_balance(){
    return total_balance_;
  }

  int Tower::total_messages_sent(){
    return total_messages_sent_;
  }

  float Tower::accuracy(){
    return accuracy_;
  }

  int Tower::pay_rate(){
    return pay_rate_;
  }

  int Tower::speed_1(){
    return speed_1_;
  }

  int Tower::speed_2(){
    return speed_2_;
  }

  int Tower::speed_3(){
    return speed_3_;
  }

  int Tower::speed_4(){
    return speed_4_;
  }

  int Tower::speed_5(){
    return speed_5_;
  }

}
