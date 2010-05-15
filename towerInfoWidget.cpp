
#include <towerInfoWidget.h>
#include <infoBox.h>
#include <device.h>
#include <towerCreator.h>
#include <tile.h>

namespace Sem {

  TowerInfoWidget::TowerInfoWidget(Device* d, InfoBox* info_box, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
    info_box_ = info_box;
    spacing_ = 10;
  }

  void TowerInfoWidget::init(){
    set_tower_1_ = new QPushButton(tr("Set connecting tower #1"));
    set_tower_2_ = new QPushButton(tr("Set connecting tower #2"));

    connect(set_tower_1_, SIGNAL(pressed()),
            this, SLOT(setTower1()));
    connect(set_tower_2_, SIGNAL(pressed()),
            this, SLOT(setTower2()));

    createLayout();
  }

  void TowerInfoWidget::setTower1(){
    d_->tower_creator()->beginSettingConnection(info_box_->last_tile_->tower(), Tower::TOWER_1);
  }

  void TowerInfoWidget::setTower2(){
    d_->tower_creator()->beginSettingConnection(info_box_->last_tile_->tower(), Tower::TOWER_2);
  }

  void TowerInfoWidget::createLayout(){
    if(layout())
      return;

    layout_ = new QVBoxLayout();
    layout_->addWidget(info_box_->tower_name_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->elevation_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->engineers_);
    layout_->addWidget(info_box_->engineer_1_);
    layout_->addWidget(info_box_->engineer_2_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->towers_);
    layout_->addWidget(info_box_->tower_1_);
    layout_->addWidget(set_tower_1_);
    layout_->addWidget(info_box_->tower_2_);
    layout_->addWidget(set_tower_2_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->operating_since_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->operating_percentage_);
    layout_->addWidget(info_box_->message_rate_);

    setLayout(layout_);
  }


}
