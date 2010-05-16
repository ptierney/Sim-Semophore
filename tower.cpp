
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

  Tower::Tower(Device* d, Tile* tile){
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
    return 4 * tile_width_ + elevation / 500.0 * tile_width_;
  }

  void Tower::beginSettingTower(Connection type){
    current_connection_set_ = type;
    view_mode_ = SET_CONNECTION;
  }

  void Tower::setConnectingTower(Tower* tower, Connection connection){
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

}
