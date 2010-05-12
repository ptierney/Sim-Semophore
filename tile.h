#ifndef TILE_H
#define TILE_H

#include <QImage>
#include <QGraphicsObject>
#include <QGraphicsItem>

namespace Sem {
  class Device;

  class Tile : public QGraphicsObject {
    Q_OBJECT
  public:
    Tile(Device*, QGraphicsItem* parent = 0);
    void init();

    void set_axon_image(const QImage&);

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void updateDrawRect();
    void updateClipPath();

    QPainterPath shape() const;

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

  private:
    Device* d_;
    QImage axon_image_;

    int width_;
    int height_;
    QRectF draw_rect_;
    QPainterPath clip_path_;
  };

}

#endif // TILE_H
