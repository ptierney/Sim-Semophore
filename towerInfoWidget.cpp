
#include <iostream>

#include <QtGui>

#include <towerInfoWidget.h>
#include <infoBox.h>
#include <device.h>
#include <towerCreator.h>
#include <tile.h>
#include <gameState.h>

namespace Sem {

  TowerInfoWidget::TowerInfoWidget(Device* d, InfoBox* info_box, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
    info_box_ = info_box;
    spacing_ = 10;
    current_tower_ = NULL;
  }

  void TowerInfoWidget::init(){
    connected_to_paris_ = new QLabel(this);
    connected_to_paris_->setFont(*(d_->bold_font()));

    set_tower_1_ = new QPushButton(tr("Set connection towards frontier"));
    set_tower_2_ = new QPushButton(tr("Set connection towards Paris"));
    set_tower_1_->setFont(*(d_->game_font()));
    set_tower_2_->setFont(*(d_->game_font()));

    connect(set_tower_1_, SIGNAL(released()),
            this, SLOT(setTower1()));
    connect(set_tower_2_, SIGNAL(released()),
            this, SLOT(setTower2()));

    pay_ = new QLabel(this);
    pay_->setFont(*(d_->game_font()));
    pay_label_ = new QLabel(this);
    pay_label_->setFont(*(d_->bold_font()));
    pay_label_->setToolTip(tr("Increasing pay increases accuracy."));
    pay_slider_ = new QSlider(Qt::Horizontal, this);
    pay_slider_->setMinimum(0);
    pay_slider_->setMaximum(GameState::max_pay);
    connect(pay_slider_, SIGNAL(valueChanged(int)),
            this, SLOT(payChanged(int)));

    pay_layout_ = new QHBoxLayout();
    pay_layout_->addWidget(pay_slider_);
    pay_layout_->addWidget(pay_);

    speed_layout_ = new QHBoxLayout();
    speed_slider_1_ = new QSlider(Qt::Vertical, this);
    speed_slider_1_->setMinimumHeight(60);
    speed_slider_1_->setMinimum(1);
    speed_slider_1_->setMaximum(30);
    speed_slider_1_->setToolTip(tr("Time to observe neighboring station."));
    connect(speed_slider_1_, SIGNAL(valueChanged(int)),
            this, SLOT(speed1Changed(int)));
    speed_slider_2_ = new QSlider(Qt::Vertical, this);
    speed_slider_2_->setMinimum(1);
    speed_slider_2_->setMaximum(30);
    speed_slider_2_->setToolTip(tr("Time to form signal on the oblique."));
    connect(speed_slider_2_, SIGNAL(valueChanged(int)),
            this, SLOT(speed2Changed(int)));
    speed_slider_3_ = new QSlider(Qt::Vertical, this);
    speed_slider_3_->setMinimum(1);
    speed_slider_3_->setMaximum(30);
    speed_slider_3_->setToolTip(tr("Time to observe neighboring stationg forming signal, and replicating it."));
    connect(speed_slider_3_, SIGNAL(valueChanged(int)),
            this, SLOT(speed3Changed(int)));
    speed_slider_4_ = new QSlider(Qt::Vertical, this);
    speed_slider_4_->setMinimum(1);
    speed_slider_4_->setMaximum(30);
    speed_slider_4_->setToolTip(tr("Time to record signal in log book."));
    connect(speed_slider_4_, SIGNAL(valueChanged(int)),
            this, SLOT(speed4Changed(int)));
    speed_slider_5_ = new QSlider(Qt::Vertical, this);
    speed_slider_5_->setMinimum(1);
    speed_slider_5_->setMaximum(30);
    speed_slider_5_->setToolTip(tr("Time to verify the next signal correctly replicated signal."));
    connect(speed_slider_5_, SIGNAL(valueChanged(int)),
            this, SLOT(speed5Changed(int)));

    speed_layout_->addWidget(speed_slider_1_);
    speed_layout_->addWidget(speed_slider_2_);
    speed_layout_->addWidget(speed_slider_3_);
    speed_layout_->addWidget(speed_slider_4_);
    speed_layout_->addWidget(speed_slider_5_);

    speeds_label_ = new QLabel(this);
    speeds_label_->setFont(*(d_->bold_font()));
    speeds_label_->setToolTip(tr("Changing speeds affects efficiency and mission transmit rate."));
    speed_1_ = new QLabel(this);
    speed_1_->setFont(*(d_->game_font()));
    speed_2_ = new QLabel(this);
    speed_2_->setFont(*(d_->game_font()));
    speed_3_ = new QLabel(this);
    speed_3_->setFont(*(d_->game_font()));
    speed_4_ = new QLabel(this);
    speed_4_->setFont(*(d_->game_font()));
    speed_5_ = new QLabel(this);
    speed_5_->setFont(*(d_->game_font()));

    speed_layout_text_ = new QHBoxLayout();
    speed_layout_text_->addWidget(speed_1_);
    speed_layout_text_->addWidget(speed_2_);
    speed_layout_text_->addWidget(speed_3_);
    speed_layout_text_->addWidget(speed_4_);
    speed_layout_text_->addWidget(speed_5_);

    accuracy_ = new QLabel(this);
    accuracy_->setFont(*(d_->game_font()));
    total_balance_ = new QLabel(this);
    total_balance_->setFont(*(d_->bold_font()));
    total_messages_sent_ = new QLabel(this);
    total_messages_sent_->setFont(*(d_->game_font()));

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

    //std::cerr << "Layout" << std::endl;

    layout_ = new QVBoxLayout();
    layout_->addWidget(info_box_->tower_name_);

    //layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->elevation_);
    layout_->addWidget(info_box_->operating_since_);
    layout_->addWidget(connected_to_paris_);
    //layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->towers_);
    layout_->addWidget(info_box_->tower_1_);
    layout_->addWidget(set_tower_1_);
    layout_->addWidget(info_box_->tower_2_);
    layout_->addWidget(set_tower_2_);
    //layout_->addSpacing(spacing_);
    layout_->addWidget(pay_label_);
    layout_->addLayout(pay_layout_);
    layout_->addWidget(speeds_label_);
    layout_->addLayout(speed_layout_);
    layout_->addLayout(speed_layout_text_);
    //layout_->addSpacing(spacing_);
    layout_->addWidget(accuracy_);
    layout_->addWidget(total_balance_);
    layout_->addWidget(total_messages_sent_);

    setLayout(layout_);
  }

  void TowerInfoWidget::payChanged(int){
    current_tower_->set_pay_rate(pay_slider_->value());
    pay_->setText(tr("Fr. ") + QString().setNum(pay_slider_->value()));
    update();
  }

  void TowerInfoWidget::speed1Changed(int){
    current_tower_->set_speed_1(speed_slider_1_->value());
    speed_1_->setText(QString().setNum(speed_slider_1_->value()) + tr(" sec."));
    update();
  }

  void TowerInfoWidget::speed2Changed(int){
    current_tower_->set_speed_2(speed_slider_2_->value());
    speed_2_->setText(QString().setNum(speed_slider_2_->value()) + tr(" sec."));
    update();
  }

  void TowerInfoWidget::speed3Changed(int){
    current_tower_->set_speed_3(speed_slider_3_->value());
    speed_3_->setText(QString().setNum(speed_slider_3_->value()) + tr(" sec."));
    update();
  }

  void TowerInfoWidget::speed4Changed(int){
    current_tower_->set_speed_4(speed_slider_4_->value());
    speed_4_->setText(QString().setNum(speed_slider_4_->value()) + tr(" sec."));
    update();
  }

  void TowerInfoWidget::speed5Changed(int){
    current_tower_->set_speed_5(speed_slider_5_->value());
    speed_5_->setText(QString().setNum(speed_slider_5_->value())  + tr(" sec."));
    update();
  }

}
