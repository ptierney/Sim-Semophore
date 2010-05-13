
#include <towerCreator.h>
#include <tile.h>
#include <tower.h>

namespace Sem {

  TowerCreator::TowerCreator(Device* d) {
    d_ = d;
    active_ = false;
    last_hover_tile_ = NULL;
    last_click_tile_ = NULL;
  }

  void TowerCreator::init(){

  }

  void TowerCreator::build(){
    active_ = true;

  }

  void TowerCreator::registerEnter(Tile* tile){
    if(!active_) {
      last_hover_tile_ = tile;
      return;
    }

    if(last_hover_tile_)
      last_hover_tile_->set_ghosted_tower(false);

    tile->set_ghosted_tower(true);
    last_hover_tile_ = tile;
  }

  void TowerCreator::registerClick(Tile* tile){
    if(!active_){
      last_click_tile_ = tile;
      return;
    }

    active_ = false;
    last_hover_tile_->set_ghosted_tower(false);
    tile->set_ghosted_tower(false);
    Tower* tower = new Tower(d_, tile);
    tower->init();
    tile->set_tower(tower);
    // Make a new tower, place it
  }


}
