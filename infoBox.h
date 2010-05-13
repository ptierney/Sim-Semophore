#ifndef INFOBOX_H
#define INFOBOX_H

#include <QWidget>
#include <QtGui>

namespace Sem {
  class Device;
  class Tile;
  class Tower;

  class InfoBox : public QWidget {
  public:
    InfoBox(Device*, QWidget* parent = 0);
    void init();

    enum SelectType {
      TERRAIN,
      SEMAPHORE
    };

    void registerSelect(Tile*);

  private:
    Device* d_;

    QVBoxLayout* terrain_layout_;
    QVBoxLayout* semaphore_layout_;

    QLabel* cost_;
    QLabel* elevation_;

    QLabel* engineer_1_;
    QLabel* engineer_2_;

    QLabel* semaphore_1_;
    QLabel* semaphore_2_;

    QLabel* operating_since_;
    QLabel* operating_percentage_;
    QLabel* message_rate_;

    void updateTerrainValues(Tile*);
    void updateSemaphoreValues(Tower*);
    void createTerrainLayout();
  };
}

#endif // INFOBOX_H
