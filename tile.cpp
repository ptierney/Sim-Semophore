
#include <iostream>

#include <QPainter>

#include <tile.h>
#include <device.h>
#include <gameScene.h>
#include <tileImageLoader.h>
#include <mapChanger.h>

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
  }

  void Tile::init(){
    updateDrawRect();
    updateClipPath();
    setBoundingRegionGranularity(0.9);

    setAcceptedMouseButtons(Qt::LeftButton);
    //setFlag(QGraphicsItem::ItemClipsToShape, true);
    selected_icon_ = d_->tile_image_loader()->loadImage(TileImageLoader::SELECT, 0, 0);
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

    if(terrain_covering_) {
      int terrain_covering_height = -height_;
      if(covering_terrain_type_ == TileImageLoader::FOREST ||
         covering_terrain_type_ == TileImageLoader::MOUNTAIN)
        terrain_covering_height -= 24;

      painter->drawImage(QPoint(-width_/2.0,
                                terrain_covering_height),
                         covering_terrain_);
    }

    if(object_covering_){
      int object_covering_height = -height_;
      if(covering_object_type_ == TileImageLoader::SEMAPHORE)
        object_covering_height -= 24;
      painter->drawImage(QPoint(-width_/2.0,
                                object_covering_height),
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

  void Tile::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/){
    selected_ = !selected_;
    d_->map_changer()->objectSelected(this);
    update();
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

}
