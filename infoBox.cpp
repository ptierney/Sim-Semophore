
#include <infoBox.h>
#include <device.h>
#include <tile.h>

namespace Sem {

  InfoBox::InfoBox(Device* d, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
    terrain_layout_ = NULL;
    semaphore_layout_ = NULL;
    last_tile_ = NULL;
  }

  void InfoBox::init(){
    cost_ = new QLabel();
    elevation_ = new QLabel();
  }

  void InfoBox::createTerrainLayout(){
    /*
    QLayout* old_layout = layout();
    if(old_layout)
      delete old_layout;
      */

    if(terrain_layout_)
      delete terrain_layout_;

    terrain_layout_ = new QVBoxLayout();
    terrain_layout_->addWidget(cost_);
    terrain_layout_->addWidget(elevation_);

    setLayout(terrain_layout_);
  }

  void InfoBox::registerSelect(Tile* tile){
    tile->set_selected(true);
    tile->update();
    if(last_tile_){
      last_tile_->set_selected(false);
      last_tile_->update();
    }
    if(tile->tower())
      return;

    updateTerrainValues(tile);
    createTerrainLayout();
    update();
    last_tile_ = tile;
  }

  void InfoBox::updateTerrainValues(Tile* tile){
    QString cost;
    cost.setNum(tile->cost());
    cost_->setText(tr("Cost: Fr ") + cost);

    QString elevation;
    elevation.setNum(tile->elevation());
    elevation_->setText(tr("Elevation: ") + elevation);
  }
}
