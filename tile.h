#ifndef TILE_H
#define TILE_H

#include <QImage>
#include <QGraphicsObject>
#include <QGraphicsItem>

#include <tileImageLoader.h>

namespace Sem {
  class Device;

  class Tile : public QGraphicsObject {
    Q_OBJECT
  public:
    Tile(Device*, QGraphicsItem* parent = 0);
    void init();

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void updateDrawRect();
    void updateClipPath();

    QPainterPath shape() const;

    void set_axon_image(const QImage&, TileImageLoader::TileType);
    void set_covering_terrain(const QImage&, TileImageLoader::TileType);
    void set_covering_object(const QImage&, TileImageLoader::TileType);

    TileImageLoader::TileType terrain_type();
    TileImageLoader::TileType covering_terrain_type();
    TileImageLoader::TileType covering_object_type();

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

  private:
    Device* d_;
    QImage axon_image_;
    TileImageLoader::TileType terrain_type_;
    QImage selected_icon_;
    bool selected_;
    // Covering terrain is forest or mountains
    QImage covering_terrain_;
    bool terrain_covering_;
    TileImageLoader::TileType covering_terrain_type_;
    // Covering object is a road, rail, or city
    QImage covering_object_;
    bool object_covering_;
    TileImageLoader::TileType covering_object_type_;

    int width_;
    int height_;
    QRectF draw_rect_;
    QPainterPath clip_path_;
  };

}

#endif // TILE_H
