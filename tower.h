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
    Engineer* engineer_1();
    Engineer* engineer_2();

  private:
    Device* d_;
    Tile* tile_;

    QDate date_created_;

    Engineer* engineer_1_;
    Engineer* engineer_2_;

    int messages_sent_;
    int mistakes_;
  };

}

#endif // TOWER_H
