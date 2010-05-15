
#include <towerCreator.h>
#include <tile.h>
#include <tower.h>
#include <device.h>
#include <gameScene.h>
#include <infoBox.h>

namespace Sem {

  TowerCreator::TowerCreator(Device* d) {
    d_ = d;
    active_ = false;
    last_hover_tile_ = NULL;
    last_click_tile_ = NULL;
    set_connection_tower_ = NULL;
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

  void TowerCreator::cancelBuilding(){
    active_ = false;
    if(active_tower_){
      delete active_tower_;
      active_tower_ = NULL;
    }
    towers_.pop_back();
  }

  void TowerCreator::registerEnter(Tile* tile){
    if(!active_) {
      last_hover_tile_ = tile;
      return;
    }

    active_tower_->set_tile(tile);
    active_tower_->update();

    last_hover_tile_ = tile;

    d_->info_box()->registerSelect(tile);
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

  Tile* TowerCreator::last_hover_tile(){
    return last_hover_tile_;
  }

  void TowerCreator::mousePressEvent(Tower* sending_tower, QGraphicsSceneMouseEvent* event){
    if(set_connection_tower_ && set_connection_tower_ != sending_tower){
      set_connection_tower_->setConnectingTower(sending_tower,
                                                set_connection_type_);
      set_connection_tower_ = NULL;
    }
  }

  void TowerCreator::beginSettingConnection(Tower* tower, Tower::Connection setting_type){
    set_connection_tower_ = tower;
    set_connection_type_ = setting_type;
    tower->beginSettingTower(setting_type);
  }

}
