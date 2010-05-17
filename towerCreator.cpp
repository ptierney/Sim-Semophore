
#include <iostream>
#include <algorithm>

#include <towerCreator.h>
#include <tile.h>
#include <tower.h>
#include <device.h>
#include <gameScene.h>
#include <infoBox.h>
#include <newTowerDialogCreator.h>
#include <gameState.h>
#include <dateBox.h>

namespace Sem {

  TowerCreator::TowerCreator(Device* d) {
    d_ = d;
    active_ = false;
    last_hover_tile_ = NULL;
    last_click_tile_ = NULL;
    set_connection_tower_ = NULL;
    active_tower_ = NULL;
  }

  void TowerCreator::init(){

  }

  void TowerCreator::build(){
    if(last_hover_tile_ == NULL)
      return;

    active_ = true;

    active_tower_ = new Tower(d_, last_hover_tile_,
                              d_->tile_image_loader()->towers_r(),
                              d_->tile_image_loader()->towers_l(),
                              d_->tile_image_loader()->towers_v(),
                              d_->tile_image_loader()->towers_h() );
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

    d_->game_state()->addMoney(tile->cost() * -1);
    d_->date_box()->updateLabels();
    d_->date_box()->update();

    d_->new_tower_dialog_creator()->create(active_tower_);
  }

  std::vector<Tower*>& TowerCreator::towers(){
    return towers_;
  }

  Tile* TowerCreator::last_hover_tile(){
    return last_hover_tile_;
  }

  void TowerCreator::mousePressEvent(Tower* sending_tower, QGraphicsSceneMouseEvent* /*event*/){
    if(set_connection_tower_ && set_connection_tower_ != sending_tower){
      set_connection_tower_->setConnectingTower(sending_tower,
                                                set_connection_type_);
      Tower::Connection other_type;
      if(set_connection_type_ == Tower::TOWER_1)
        other_type = Tower::TOWER_2;
      else if(set_connection_type_ == Tower::TOWER_2)
        other_type = Tower::TOWER_1;
      else
        std::cerr<< "Oh fuck" << std::endl;

      sending_tower->setConnectingTower(set_connection_tower_, other_type);

      set_connection_tower_ = NULL;
    }
  }

  void TowerCreator::beginSettingConnection(Tower* tower, Tower::Connection setting_type){
    set_connection_tower_ = tower;
    set_connection_type_ = setting_type;
    tower->beginSettingTower(setting_type);
  }

  void TowerCreator::changeGlobally(){

  }

  void TowerCreator::updateTowers(int days){
    for(std::vector<Tower*>::const_iterator it = towers_.begin(); it != towers_.end(); ++it){
      (*it)->updateValues(days);
    }
  }

  int TowerCreator::collectMoney(){
    int towers_balance = 0;
    for(std::vector<Tower*>::const_iterator it = towers_.begin(); it != towers_.end(); ++it){
      towers_balance += (*it)->collectMoney();
    }

    return towers_balance;
  }

  int TowerCreator::getCitiesConnected(){
    int num_cities = 0;

    //std::cerr << towers_.size() << std::endl;

    std::vector<QString> cities;
    std::vector<QString>::iterator cities_it;
    for(std::vector<Tower*>::const_iterator it = towers_.begin(); it != towers_.end(); ++it){
      QString name = (*it)->tile()->arrondissement();

      if((*it)->tower_1() == NULL &&
         (*it)->tower_2() == NULL)
        continue;

      if(name == tr("frontiere"))
        continue;

      cities_it = find(cities.begin(), cities.end(), name);

      if(cities_it == cities.end()){
        num_cities++;
        cities.push_back(name);
      }
    }
    return num_cities;
  }

}
