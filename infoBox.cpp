
#include <iostream>

#include <infoBox.h>
#include <device.h>
#include <tile.h>
#include <tower.h>
#include <engineer.h>
#include <towerInfoWidget.h>
#include <terrainInfoWidget.h>

namespace Sem {

  InfoBox::InfoBox(Device* d, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
    terrain_layout_ = NULL;
    tower_layout_ = NULL;
    last_tile_ = NULL;
  }

  void InfoBox::init(){
    cost_ = new QLabel();
    elevation_ = new QLabel();
    arrondissement_ = new QLabel();
    coordinates_ = new QLabel();
    engineers_ = new QLabel();
    engineer_1_ = new QLabel();
    engineer_2_ = new QLabel();
    towers_ = new QLabel();
    tower_name_ = new QLabel();
    tower_1_ = new QLabel();
    tower_2_ = new QLabel();
    operating_since_ = new QLabel();
    operating_percentage_ = new QLabel();
    message_rate_ = new QLabel();

    terrain_widget_ = new TerrainInfoWidget(d_, this, this);
    terrain_widget_->init();
    tower_widget_ = new TowerInfoWidget(d_, this, this);
    tower_widget_->init();

    std::cerr << "Test" << std::endl;
    main_layout_ = new QVBoxLayout;
    main_widget_ = terrain_widget_;
    main_layout_->addWidget(main_widget_);
    setLayout(main_layout_);

    //terrain_widget_->hide();
    //tower_widget_->hide();
  }

  void InfoBox::createTerrainLayout(){
    /*
    //deleteLayouts();
    if(terrain_layout_){
      delete terrain_layout_;
      terrain_layout_ = NULL;
    }

    terrain_layout_ = new QVBoxLayout();
    terrain_layout_->addWidget(cost_);
    terrain_layout_->addWidget(elevation_);

    setLayout(terrain_layout_);
    */
  }

  void InfoBox::createTowerLayout(){
    /*
    //deleteLayouts();
    if(terrain_layout_){
      delete terrain_layout_;
      terrain_layout_ = NULL;
    }

    if(layout())
      std::cerr << "Oh fuck" << std::endl;

    terrain_layout_ = new QVBoxLayout();
    terrain_layout_->addWidget(tower_name_);
    //terrain_layout_->addSpacing(5);
    terrain_layout_->addWidget(elevation_);
    //terrain_layout_->addSpacing(5);
    terrain_layout_->addWidget(engineers_);
    terrain_layout_->addWidget(engineer_1_);
    terrain_layout_->addWidget(engineer_2_);
    //terrain_layout_->addSpacing(5);
    terrain_layout_->addWidget(towers_);
    terrain_layout_->addWidget(tower_1_);
    terrain_layout_->addWidget(tower_2_);
    //terrain_layout_->addSpacing(5);
    terrain_layout_->addWidget(operating_since_);
    //terrain_layout_->addSpacing(5);
    terrain_layout_->addWidget(operating_percentage_);
    terrain_layout_->addWidget(message_rate_);

    setLayout(terrain_layout_);
    */
  }

  void InfoBox::registerSelect(Tile* tile){
    tile->set_selected(true);
    tile->update();
    if(last_tile_){
      last_tile_->set_selected(false);
      last_tile_->update();
    }
    if(tile->tower()){
      tower_widget_->show();

      updateTerrainValues(tile);
      updateTowerValues(tile->tower());
      tower_widget_->createLayout();

      main_layout_->removeWidget(main_widget_);
      main_widget_ = tower_widget_;
      main_layout_->addWidget(main_widget_);

      terrain_widget_->hide();
    } else {
      terrain_widget_->show();

      updateTerrainValues(tile);
      terrain_widget_->createLayout();

      main_layout_->removeWidget(main_widget_);
      main_widget_ = terrain_widget_;
      main_layout_->addWidget(main_widget_);

      tower_widget_->hide();
    }
    main_layout_->update();
    main_widget_->update();
    update();
    last_tile_ = tile;
  }

  void InfoBox::updateTerrainValues(Tile* tile){
    arrondissement_->setText(tile->arrondissement());

    QString cost;
    cost.setNum(tile->cost());
    cost_->setText(tr("Cost: Fr. ") + cost);

    QString elevation;
    elevation.setNum(tile->elevation());
    elevation_->setText(tr("Elevation: ") + elevation);

    QString x, y;
    x.setNum(tile->x_index());
    y.setNum(tile->y_index());
    coordinates_->setText(x + tr(" : ") + y);
  }

  void InfoBox::updateTowerValues(Tower* tower){
    tower_name_->setText(tower->name());
    engineers_->setText(tr("Engineers:"));
    engineer_1_->setText(tower->engineer_1()->name());
    engineer_2_->setText(tower->engineer_2()->name());
    towers_->setText(tr("Connected towers"));
    if(tower->tower_1()){
      tower_1_->setText(tower->tower_1()->name());
    } else {
      tower_1_->setText(tr("Nothing set"));
    }
    if(tower->tower_2()){
      tower_2_->setText(tower->tower_2()->name());
    } else {
      tower_2_->setText(tr("Nothing set"));
    }
    operating_since_->setText(tr("Operating since:") +
                              tower->date_created().toString("dddd MMMM d, yyyy"));
    QString per;
    per.setNum(tower->operating_percentage());
    operating_percentage_->setText(tr("Operating percentage: ") + per + "%");
    message_rate_->setText(tr("Message rate"));
  }

  void InfoBox::deleteLayouts(){
    if(terrain_layout_){
      delete terrain_layout_;
      terrain_layout_ = NULL;
    }

    if(tower_layout_) {
      delete tower_layout_;
      tower_layout_ = NULL;
    }
  }
}
