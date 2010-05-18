#ifndef TOWERCREATOR_H
#define TOWERCREATOR_H

#include <vector>

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <tower.h>

namespace Sem {
  class Device;
  class Tile;
  class Tower;

  class TowerCreator : public QObject {
  public:
    TowerCreator(Device*);
    void init();

    void registerEnter(Tile*);
    void registerClick(Tile*);

    void build(); // Called by the main window
    void cancelBuilding();
    void cancelConnection(); // Cancels creating a connection
    std::vector<Tower*>& towers();
    void changeGlobally(); // Spawns a dialog

    Tile* last_hover_tile();

    void mousePressEvent(Tower* sending_tower, QGraphicsSceneMouseEvent* event);

    void beginSettingConnection(Tower*, Tower::Connection);

    void updateTowers(int days);
    int collectMoney();
    int getCitiesConnected();

  private:
    Device* d_;
    bool active_;

    Tile* last_hover_tile_;
    Tile* last_click_tile_;

    Tower* active_tower_;
    Tower* set_connection_tower_;
    Tower::Connection set_connection_type_;
    std::vector<Tower*> towers_;

  };
}

#endif // TOWERCREATOR_H
