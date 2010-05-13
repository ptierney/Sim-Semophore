#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QDate>

namespace Sem {
  class Device;
  class Tile;
  class Engineer;

  class Tower : public QObject {
    Q_OBJECT

  public:
    Tower(Device*, Tile*);
    void init();

    void update();

    const QDate& date_created();
    const QString& name();
    Engineer* engineer_1();
    Engineer* engineer_2();
    Tower* tower_1();
    Tower* tower_2();

    float operating_percentage();
    float message_rate();

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
  };

}

#endif // TOWER_H
