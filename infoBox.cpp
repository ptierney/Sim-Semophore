
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
    current_tile_ = NULL;
  }

  void InfoBox::init(){
    cost_ = new QLabel();
    cost_->setFont(*(d_->game_font()));
    elevation_ = new QLabel();
    elevation_->setFont(*(d_->game_font()));
    arrondissement_ = new QLabel();
    arrondissement_->setFont(*(d_->game_font()));
    coordinates_ = new QLabel();
    coordinates_->setFont(*(d_->game_font()));
    engineers_ = new QLabel();
    engineer_1_ = new QLabel();
    engineer_2_ = new QLabel();
    towers_ = new QLabel();
    towers_->setFont(*(d_->bold_font()));
    tower_name_ = new QLabel();
    tower_name_->setFont(*(d_->bold_font()));
    tower_1_ = new QLabel();
    tower_1_->setFont(*(d_->game_font()));
    tower_2_ = new QLabel();
    tower_2_->setFont(*(d_->game_font()));
    operating_since_ = new QLabel();
    operating_since_->setFont(*(d_->game_font()));
    operating_percentage_ = new QLabel();
    operating_percentage_->setFont(*(d_->game_font()));
    message_rate_ = new QLabel();
    message_rate_->setFont(*(d_->game_font()));

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
    if(last_tile_ &&
       last_tile_ != tile){
      last_tile_->set_selected(false);
      last_tile_->update();
    }
    current_tile_ = tile;
    updateValues();

    main_layout_->update();
    main_widget_->update();
    update();
    last_tile_ = tile;
  }

  void InfoBox::updateValues(){
    if(current_tile_ == NULL)
      return;

    if(current_tile_->tower()){
      tower_widget_->show();

      updateTerrainValues(current_tile_);
      updateTowerValues(current_tile_->tower());
      tower_widget_->createLayout();

      main_layout_->removeWidget(main_widget_);
      main_widget_ = tower_widget_;
      main_layout_->addWidget(main_widget_);

      terrain_widget_->hide();
    } else {
      terrain_widget_->show();

      updateTerrainValues(current_tile_);
      terrain_widget_->createLayout();

      main_layout_->removeWidget(main_widget_);
      main_widget_ = terrain_widget_;
      main_layout_->addWidget(main_widget_);

      tower_widget_->hide();
    }

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
    tower_widget_->current_tower_ = tower;
    tower_name_->setText(tower->name());
    engineers_->setText(tr("Engineers:"));
    engineer_1_->setText(tower->engineer_1()->name());
    engineer_2_->setText(tower->engineer_2()->name());
    if(tower->connected_to_paris())
      tower_widget_->connected_to_paris_->setText(tr("Connected to Paris: YES"));
    else
      tower_widget_->connected_to_paris_->setText(tr("Connected to Paris: NO"));

    towers_->setText(tr("Connected towers:"));
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

    tower_widget_->pay_label_->setText(tr("Set engineer pay:"));
    //tower_widget_->pay_slider_->setValue(tower->pay_rate());
    //tower_widget_->pay_->setText(QString().setNum(tower->pay_rate()));

    tower_widget_->speeds_label_->setText(tr("Set tower operation speeds:"));

    tower_widget_->pay_->setText(tr(" Fr.") + QString().setNum(tower->pay_rate()));
    tower_widget_->pay_slider_->setValue(tower->pay_rate());

    tower_widget_->speed_1_->setText(QString().setNum(tower->speed_1()) + tr(" sec."));
    tower_widget_->speed_slider_1_->setValue(tower->speed_1());

    tower_widget_->speed_2_->setText(QString().setNum(tower->speed_2()) + tr(" sec."));
    tower_widget_->speed_slider_2_->setValue(tower->speed_2());

    tower_widget_->speed_3_->setText(QString().setNum(tower->speed_3()) + tr(" sec."));
    tower_widget_->speed_slider_3_->setValue(tower->speed_3());

    tower_widget_->speed_4_->setText(QString().setNum(tower->speed_4()) + tr(" sec."));
    tower_widget_->speed_slider_4_->setValue(tower->speed_4());

    tower_widget_->speed_5_->setText(QString().setNum(tower->speed_5()) + tr(" sec."));
    tower_widget_->speed_slider_5_->setValue(tower->speed_5());

    /*
    tower_widget_->payChanged(tower->pay_rate());
    tower_widget_->speed1Changed(tower->speed_1());
    tower_widget_->speed2Changed(tower->speed_2());
    tower_widget_->speed3Changed(tower->speed_3());
    tower_widget_->speed4Changed(tower->speed_4());
    tower_widget_->speed5Changed(tower->speed_5());
    */

    operating_since_->setText(tr("Operating since: ") +
                              tower->date_created().toString("dddd MMMM d, yyyy"));
    QString accuracy, balance, messages_sent, message_rate;
    accuracy.setNum((int)(tower->accuracy() * 100.0));
    tower_widget_->accuracy_->setText(tr("Accuracy: ") + accuracy + tr("%"));

    balance.setNum(tower->total_balance());
    tower_widget_->total_balance_->setText(tr("Net profit: Fr. ") + balance);

    messages_sent.setNum(tower->total_messages_sent());
    tower_widget_->total_messages_sent_->setText(tr("Total messages transmitted: ") + messages_sent);

    message_rate.setNum(tower->message_rate());
    message_rate_->setText(tr("Sending ") + message_rate + tr(" messages a second."));
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
