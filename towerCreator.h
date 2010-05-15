#ifndef TOWERCREATOR_H
#define TOWERCREATOR_H

#include <vector>

#include <QObject>

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
    std::vector<Tower*>& towers();

  private:
    Device* d_;
    bool active_;

    Tile* last_hover_tile_;
    Tile* last_click_tile_;

    Tower* active_tower_;
    std::vector<Tower*> towers_;

  };
}

#endif // TOWERCREATOR_H
