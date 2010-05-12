
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
    setBoundingRegionGranularity(0.9);

    setAcceptedMouseButtons(Qt::LeftButton);
  }

  void Tile::set_axon_image(const QImage& image){
    axon_image_ = image;
    width_ = axon_image_.width();
    height_ = axon_image_.height();
    updateDrawRect();
  }

  QRectF Tile::boundingRect() const{
    qreal adjust = 2;
    return draw_rect_.adjusted(-adjust, -adjust, adjust, adjust).normalized();
  }

  void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/){
    painter->drawImage(QPoint(-width_/2.0,
                              -height_/2.0),
                       axon_image_);

  }

  void Tile::updateDrawRect(){
    draw_rect_ = QRectF(-width_/2.0, -height_/2.0,
                        width_, height_);
  }

  void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event){
    std::cerr << "Press" << std::endl;
  }


}
