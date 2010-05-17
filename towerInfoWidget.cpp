
#include <QtGui>

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
    connected_to_paris_ = new QLabel(this);

    set_tower_1_ = new QPushButton(tr("Set connection towards frontier"));
    set_tower_2_ = new QPushButton(tr("Set connection towards Paris"));

    connect(set_tower_1_, SIGNAL(released()),
            this, SLOT(setTower1()));
    connect(set_tower_2_, SIGNAL(released()),
            this, SLOT(setTower2()));

    pay_slider_ = new QSlider(Qt::Horizontal, this);
    speed_layout_ = new QHBoxLayout();
    speed_slider_1_ = new QSlider(Qt::Vertical, this);
    speed_slider_1_->setMinimumHeight(100);
    speed_slider_2_ = new QSlider(Qt::Vertical, this);
    speed_slider_3_ = new QSlider(Qt::Vertical, this);
    speed_slider_4_ = new QSlider(Qt::Vertical, this);
    speed_slider_5_ = new QSlider(Qt::Vertical, this);
    speed_layout_->addWidget(speed_slider_1_);
    speed_layout_->addWidget(speed_slider_2_);
    speed_layout_->addWidget(speed_slider_3_);
    speed_layout_->addWidget(speed_slider_4_);
    speed_layout_->addWidget(speed_slider_5_);

    accuracy_ = new QLabel(this);
    total_balance_ = new QLabel(this);
    total_messages_sent_ = new QLabel(this);

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
    layout_->addWidget(info_box_->operating_since_);
    layout_->addWidget(connected_to_paris_);
    layout_->addSpacing(spacing_);
    //layout_->addWidget(info_box_->engineers_);
    //layout_->addWidget(info_box_->engineer_1_);
    //layout_->addWidget(info_box_->engineer_2_);
    //layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->towers_);
    layout_->addWidget(info_box_->tower_1_);
    layout_->addWidget(set_tower_1_);
    layout_->addWidget(info_box_->tower_2_);
    layout_->addWidget(set_tower_2_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(pay_slider_);
    layout_->addLayout(speed_layout_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(accuracy_);
    layout_->addWidget(total_balance_);
    layout_->addWidget(total_messages_sent_);

    setLayout(layout_);
  }


}
