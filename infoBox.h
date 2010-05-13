#ifndef INFOBOX_H
#define INFOBOX_H

#include <QWidget>
#include <QtGui>

namespace Sem {
  class Device;
  class Tile;
  class Tower;
  class TowerInfoWidget;
  class TerrainInfoWidget;

  class InfoBox : public QWidget {
  public:
    InfoBox(Device*, QWidget* parent = 0);
    void init();

    friend class TowerInfoWidget;
    friend class TerrainInfoWidget;

    enum SelectType {
      TERRAIN,
      SEMAPHORE
    };

    void registerSelect(Tile*);

  private:
    Device* d_;
    Tile* last_tile_;

    TowerInfoWidget* tower_widget_;
    TerrainInfoWidget* terrain_widget_;

    QVBoxLayout* terrain_layout_;
    QVBoxLayout* tower_layout_;
    QVBoxLayout* main_layout_;
    QWidget* main_widget_;

    QLabel* cost_;
    QLabel* elevation_;

    QLabel* engineers_;
    QLabel* engineer_1_;
    QLabel* engineer_2_;

    QLabel* tower_name_;
    QLabel* towers_;
    QLabel* tower_1_;
    QLabel* tower_2_;

    QLabel* operating_since_;
    QLabel* operating_percentage_;
    QLabel* message_rate_;

    void updateTerrainValues(Tile*);
    void updateTowerValues(Tower*);
    void createTerrainLayout();
    void createTowerLayout();

    void deleteLayouts();
  };
}

#endif // INFOBOX_H
