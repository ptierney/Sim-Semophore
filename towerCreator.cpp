
#include <towerCreator.h>
#include <tile.h>
#include <tower.h>
#include <device.h>
#include <gameScene.h>

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

    active_tower_ = new Tower(d_, last_hover_tile_);
    active_tower_->init();
    active_tower_->set_view_mode(Tower::RANGE);
    towers_.push_back(active_tower_);
    d_->game_scene()->addItem(active_tower_);
  }

  void TowerCreator::registerEnter(Tile* tile){
    if(!active_) {
      last_hover_tile_ = tile;
      return;
    }

    active_tower_->set_tile(tile);
    active_tower_->update();

    last_hover_tile_ = tile;
  }

  void TowerCreator::registerClick(Tile* tile){
    if(!active_){
      last_click_tile_ = tile;
      return;
    }

    active_ = false;

    active_tower_->set_view_mode(Tower::NORMAL);
    active_tower_->update();
    tile->set_tower(active_tower_);
  }

  std::vector<Tower*>& TowerCreator::towers(){
    return towers_;
  }
}
