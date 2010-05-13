
#include <towerInfoWidget.h>
#include <infoBox.h>

namespace Sem {

  TowerInfoWidget::TowerInfoWidget(Device* d, InfoBox* info_box, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
    info_box_ = info_box;
    spacing_ = 10;
  }

  void TowerInfoWidget::init(){
    createLayout();
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
    layout_->addWidget(info_box_->tower_2_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->operating_since_);
    layout_->addSpacing(spacing_);
    layout_->addWidget(info_box_->operating_percentage_);
    layout_->addWidget(info_box_->message_rate_);

    setLayout(layout_);
  }


}
