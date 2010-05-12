
#include <iostream>

#include <QPainter>

#include <tile.h>
#include <device.h>
#include <gameScene.h>
#include <tileImageLoader.h>

namespace Sem {

  Tile::Tile(Device* d, QGraphicsItem* parent) :
      QGraphicsObject(parent) {
    d_ = d;

  }

  void Tile::init(){
    width_ = 128;
    height_ = 64;

    updateDrawRect();
    updateClipPath();
    setBoundingRegionGranularity(0.9);

    setAcceptedMouseButtons(Qt::LeftButton);
    //setFlag(QGraphicsItem::ItemClipsToShape, true);
  }

  void Tile::set_axon_image(const QImage& image){
    axon_image_ = image;
    width_ = axon_image_.width();
    height_ = axon_image_.height();
    updateDrawRect();
    updateClipPath();
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

    painter->setPen(QPen(QBrush(Qt::black), 0.15));

    painter->drawPath(clip_path_);
    painter->drawRect(draw_rect_);
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
    std::cerr << "Press" << std::endl;
  }


}
