
#include <iostream>

#include <QPainter>

#include <tile.h>
#include <device.h>
#include <gameScene.h>
#include <tileImageLoader.h>
#include <mapChanger.h>
#include <gameState.h>
#include <tower.h>
#include <infoBox.h>
#include <towerCreator.h>

namespace Sem {

  Tile::Tile(Device* d, QGraphicsItem* parent) :
      QGraphicsObject(parent) {
    d_ = d;
    width_ = 128;
    height_ = 64;

    terrain_type_ = TileImageLoader::NONE;
    covering_terrain_type_ = TileImageLoader::NONE;
    covering_object_type_ = TileImageLoader::NONE;
    terrain_index_.first = 0;
    terrain_index_.second = 0;

    elevation_ = qrand() % 100;

    axon_image_ = QImage();
    tower_ = NULL;
    arrondissement_ = "Region sauvage";
    arrondissement_set_ = false;
    show_text_ = false;
    selected_ = false;
    ghosted_tower_ = false;

    ellipse_color_ = QColor(255, 0, 255, 100);
  }

  void Tile::init(){
    updateDrawRect();
    updateClipPath();
    setBoundingRegionGranularity(0.9);

    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptsHoverEvents(true);
    //setFlag(QGraphicsItem::ItemClipsToShape, true);
    selected_icon_ = d_->tile_image_loader()->loadImage(TileImageLoader::SELECT, 0, 0);
    tower_object_ = d_->tile_image_loader()->loadImage(TileImageLoader::SEMAPHORE, 0, 0);
  }

  QRectF Tile::boundingRect() const{
    qreal adjust = 2;
    return draw_rect_.adjusted(-adjust, -adjust, adjust, adjust).normalized();
  }

  QPainterPath Tile::shape() const{
    return clip_path_;
  }

  void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/){
    painter->drawImage(QPoint(-width_/2.0,
                              -height_),
                       axon_image_);

   // painter->setPen(QPen(QBrush(Qt::black), 0.15));

    //painter->drawPath(clip_path_);
    //painter->drawRect(draw_rect_);

    if(terrain_covering_ &&
       covering_terrain_type_ != TileImageLoader::NONE) {
      int terrain_covering_height = -height_;
      if(covering_terrain_type_ == TileImageLoader::FOREST ||
         covering_terrain_type_ == TileImageLoader::MOUNTAIN)
        terrain_covering_height -= 24;

      painter->drawImage(QPoint(-width_/2.0,
                                terrain_covering_height),
                         covering_terrain_);
    }

    if(object_covering_ &&
       covering_object_type_ != TileImageLoader::NONE){
      painter->drawImage(QPoint(-width_/2.0,
                                -height_),
                         covering_object_);
    }

    if(selected_){
      painter->drawImage(QPoint(-width_/2.0,
                                -height_),
                         selected_icon_);
    }

  }

  void Tile::set_axon_image(const QImage& image, TileImageLoader::TileType type, int x, int y){
    axon_image_ = image;
    terrain_type_ = type;
    terrain_index_.first = x;
    terrain_index_.second = y;
    width_ = axon_image_.width();
    height_ = axon_image_.height();
    updateDrawRect();
    updateClipPath();
  }

  void Tile::set_covering_terrain(const QImage& terrain, TileImageLoader::TileType type, int x, int y){
    covering_terrain_ = terrain;
    covering_terrain_type_ = type;
    covering_terrain_index_.first = x;
    covering_terrain_index_.second = y;
    terrain_covering_ = true;

    if(covering_terrain_type_ == TileImageLoader::HILL)
      elevation_ = 250 + qrand() % 1250;
    else if(covering_terrain_type_ == TileImageLoader::MOUNTAIN)
      elevation_ = 1500 + qrand() % 5000;
  }

  void Tile::set_covering_object(const QImage& object, TileImageLoader::TileType type, int x, int y){
    covering_object_ = object;
    covering_object_type_ = type;
    covering_object_index_.first = x;
    covering_object_index_.second = y;
    object_covering_ = true;
  }

  void Tile::updateDrawRect(){
    draw_rect_ = QRectF(-width_/2.0, -height_,
                        width_, height_);
  }

  void Tile::updateClipPath(){
    clip_path_ = QPainterPath();
    int tile_width = d_->tile_image_loader()->tile_width();
    int tile_height = d_->tile_image_loader()->tile_height();

    QVector<QPointF> points;
    points.push_back(QPointF(0, 0));
    points.push_back(QPointF(-tile_width/2.0, -tile_height/2.0));
    points.push_back(QPointF(0.0, -tile_height));
    points.push_back(QPointF(tile_width/2.0, -tile_height/2.0));
    points.push_back(QPointF(0, 0));
    QPolygonF diamond = QPolygonF(points);
    clip_path_.addPolygon(diamond);
  }

  void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event){
    //d_->map_changer()->objectSelected(this);
    d_->info_box()->registerSelect(this);
    d_->tower_creator()->registerClick(this);

    if(tower_)
      tower_->mousePressEvent(event);

    update();
    QGraphicsObject::mousePressEvent(event);
  }

  void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
    d_->tower_creator()->registerEnter(this);
    if(tower_)
      tower_->hoverEnterEvent(event);

    QGraphicsObject::hoverEnterEvent(event);
  }

  void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent* event){
    if(tower_)
      tower_->hoverLeaveEvent(event);

    QGraphicsObject::hoverLeaveEvent(event);
  }

  TileImageLoader::TileType Tile::terrain_type(){
    return terrain_type_;
  }

  TileImageLoader::TileType Tile::covering_terrain_type(){
    return covering_terrain_type_;
  }

  TileImageLoader::TileType Tile::covering_object_type(){
    return covering_object_type_;
  }

  std::pair<int, int> Tile::terrain_index(){
    return terrain_index_;
  }

  std::pair<int, int> Tile::covering_terrain_index(){
    return covering_terrain_index_;
  }

  std::pair<int, int> Tile::covering_object_index(){
    return covering_object_index_;
  }

  int Tile::cost(){
    int c = 0;

    switch(terrain_type_){
    case TileImageLoader::GRASSLAND:
      c += d_->game_state()->grass_cost();
      break;
    case TileImageLoader::PLANE:
      c += d_->game_state()->plane_cost();
      break;
    default:
      break;
    }

    switch(covering_terrain_type_){
    case TileImageLoader::FOREST:
      c += d_->game_state()->forest_cost();
      break;
    case TileImageLoader::HILL:
      c += d_->game_state()->hill_cost();
      break;
    case TileImageLoader::MOUNTAIN:
      c += d_->game_state()->mountain_cost();
      break;
    default:
      break;
    }

    switch(covering_object_type_){
    case TileImageLoader::CITY:
      c += d_->game_state()->city_cost();
      break;
    case TileImageLoader::FARMLAND:
      c += d_->game_state()->farm_cost();
      break;
    case TileImageLoader::RAILROAD:
      c += d_->game_state()->railroad_cost();
      break;
    default:
      break;
    }

    if( c < 0)
      c = 0;

    return c;
  }

  Tower* Tile::tower(){
    return tower_;
  }

  void Tile::set_tower(Tower* tower){
    tower_ = tower;
  }

  int Tile::elevation(){
    return elevation_;
  }


  void Tile::set_ghosted_tower(bool ghosted){
    ghosted_tower_ = ghosted;
  }

  void Tile::set_selected(bool select){
    selected_ = select;
  }

  bool Tile::selected(){
    return selected_;
  }

  void Tile::set_x_index(int index){
    x_index_ = index;
  }

  void Tile::set_y_index(int index){
    y_index_ = index;
  }

  int Tile::x_index(){
    return x_index_;
  }

  int Tile::y_index(){
    return y_index_;
  }

  const QString& Tile::arrondissement(){
    return arrondissement_;
  }

  void Tile::set_arrondissement(const QString& arrond){
    arrondissement_ = arrond;
    arrondissement_set_ = true;
  }

  bool Tile::show_text(){
    return show_text_;
  }

  // Note this function should only be called once
  void Tile::set_show_text(bool text){
    show_text_ = text;

    if(text){
      QGraphicsTextItem* text_object = new QGraphicsTextItem();
      text_object->setDefaultTextColor(Qt::white);
      text_object->setPlainText(arrondissement_);
      text_object->scale(2.0, 2.0);
      text_object->setPos(QPointF(pos().x() + width_/ 4.0,
                                  pos().y() - height_/2.0 -
                                  text_object->boundingRect().height()/2.0));
      d_->labels().push_back(text_object);
      //d_->game_scene()->addItem(text_object);
    }
  }

  bool Tile::arrondissement_set(){
    return arrondissement_set_;
  }

  int Tile::getPlacementElevation(){
    if(covering_object_type_ == TileImageLoader::CITY)
      return elevation_ + 150;
    else
      return elevation_;
  }

}
