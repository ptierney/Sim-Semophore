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
    Tower(Device*, Tile*,
          std::vector<QImage>& t_r,
          std::vector<QImage>& t_l,
          std::vector<QImage>& t_v,
          std::vector<QImage>& t_h );
    void init();

    enum ViewMode {
      HIDDEN,
      NORMAL,
      RANGE,
      CONNECTIONS,
      SET_CONNECTION
    };

    enum Connection {
      TOWER_1,
      TOWER_2
    };

    enum State {
      HORIZONTAL,
      VERTICAL,
      RIGHT,
      LEFT
    };

    void set_tile(Tile*);

    const QDate& date_created();
    const QString& name();
    Engineer* engineer_1();
    Engineer* engineer_2();
    Tower* tower_1();
    Tower* tower_2();

    Tile* tile();

    QPointF getTrueCenter();

    ViewMode view_mode();
    void set_view_mode(ViewMode);


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void updateDrawRect();

    void beginSettingTower(Connection);
    void setConnectingTower(Tower*, Connection);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void timerEvent(QTimerEvent*);

    void updateValues(int days);
    bool connected_to_paris();

    void set_pay_rate(int);
    void set_speed_1(int);
    void set_speed_2(int);
    void set_speed_3(int);
    void set_speed_4(int);
    void set_speed_5(int);

    int pay_rate();
    int speed_1();
    int speed_2();
    int speed_3();
    int speed_4();
    int speed_5();

    float getAccuracy();
    float getMessageRate();
    int collectMoney();
    int total_balance();
    int total_messages_sent();

    float accuracy();
    float message_rate();
    float operating_percentage(); // This doesn't do anything

  private:
    Device* d_;
    Tile* tile_;

    QDate date_created_;
    QString name_;

    Engineer* engineer_1_;
    Engineer* engineer_2_;

    Tower* tower_1_; // Tower towards frontier
    Tower* tower_2_; // Tower towards Paris

    int messages_sent_;
    int mistakes_;

    float operating_percentage_;
    float message_rate_;
    float accuracy_;

    float range_;

    bool connected_to_paris_;

    ViewMode view_mode_;
    QRectF draw_rect_;
    QImage tower_image_;
    int width_;
    int height_;
    int tile_width_;
    int tile_height_;
    QPointF true_center_;
    QColor ellipse_color_;
    QColor ellipse_boarder_color_;
    QColor set_connection_color_;
    QColor connection_color_;
    float connection_line_width_;

    Connection current_connection_set_;

    void drawTower(QPainter*);
    int getRangeFromElevation(int);

    State state_;
    int balance_; // Money owed or gained
    int total_balance_;
    int total_days_;
    int total_messages_sent_;

    int last_update_month_;

    int pay_rate_; // Amount an engineer earns per day
    int speed_1_;
    int speed_2_;
    int speed_3_;
    int speed_4_;
    int speed_5_;
    int total_time_;

    const std::vector<QImage>& towers_r_;
    const std::vector<QImage>& towers_l_;
    const std::vector<QImage>& towers_v_;
    const std::vector<QImage>& towers_h_;

    void checkConnectedToParis();
    bool parisTrace(Tower*);
  };

}

#endif // TOWER_H
