
#include <QtGui>

#include <terrainInfoWidget.h>
#include <infoBox.h>

namespace Sem {

  TerrainInfoWidget::TerrainInfoWidget(Device* d, InfoBox* info_box, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
    info_box_ = info_box;
  }

  void TerrainInfoWidget::init(){
  }

  void TerrainInfoWidget::createLayout(){
    if(layout())
      return;

    layout_ = new QVBoxLayout();
    layout_->addWidget(info_box_->cost_);
    layout_->addWidget(info_box_->elevation_);

    setLayout(layout_);
  }


}
