#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QGraphicsObject>
#include <QDate>

namespace Sem {
  class Device;
  class Tile;
  class Engineer;

  class Tower : public QGraphicsObject {
    Q_OBJECT

  public:
    Tower(Device*, Tile*);
    void init();

    enum ViewMode {
      HIDDEN,
      NORMAL,
      RANGE,
      CONNECTIONS
    };

    void set_tile(Tile*);

    const QDate& date_created();
    const QString& name();
    Engineer* engineer_1();
    Engineer* engineer_2();
    Tower* tower_1();
    Tower* tower_2();

    ViewMode view_mode();
    void set_view_mode(ViewMode);
    float operating_percentage();
    float message_rate();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void updateDrawRect();

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

  private:
    Device* d_;
    Tile* tile_;

    QDate date_created_;
    QString name_;

    Engineer* engineer_1_;
    Engineer* engineer_2_;

    Tower* tower_1_;
    Tower* tower_2_;

    int messages_sent_;
    int mistakes_;

    float operating_percentage_;
    float message_rate_;

    float range_;

    ViewMode view_mode_;
    QRectF draw_rect_;
    QImage tower_image_;
    int width_;
    int height_;
    int tile_width_;
    int tile_height_;

    void drawTower(QPainter*);
    int getRangeFromElevation(int);
  };

}

#endif // TOWER_H
