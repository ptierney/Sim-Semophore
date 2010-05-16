
#include <iostream>

#include <QMainWindow>
#include <QDockWidget>

#include <newTowerDialogCreator.h>
#include <device.h>
#include <tower.h>
#include <tile.h>
#include <device.h>
#include <newTowerDialog.h>

namespace Sem {

  NewTowerDialogCreator::NewTowerDialogCreator(Device* d) {
    d_ = d;
    image_height_ = 500;
  }

  void NewTowerDialogCreator::init(){
    city_images_.push_back(QImage(tr("images/city1.png")).scaledToHeight(image_height_));
    city_images_.push_back(QImage(tr("images/city2.png")).scaledToHeight(image_height_));
    wild_images_.push_back(QImage(tr("images/wild1.png")).scaledToHeight(image_height_));
    wild_images_.push_back(QImage(tr("images/wild2.png")).scaledToHeight(image_height_));
    wild_images_.push_back(QImage(tr("images/wild3.png")).scaledToHeight(image_height_));
    wild_images_.push_back(QImage(tr("images/wild4.png")).scaledToHeight(image_height_));
    wild_images_.push_back(QImage(tr("images/wild5.png")).scaledToHeight(image_height_));
    wild_images_.push_back(QImage(tr("images/wild6.png")).scaledToHeight(image_height_));
    wild_images_.push_back(QImage(tr("images/wild7.png")).scaledToHeight(image_height_));
  }

  void NewTowerDialogCreator::create(Tower* tower){
    NewTowerDialog::TowerType type;
    int ran_index;
    QImage tower_image;

    if(tower->tile()->covering_object_type() == TileImageLoader::CITY){
      type = NewTowerDialog::CITY;
      ran_index = qrand() % 2;
      tower_image = city_images_[ran_index];
    } else {
      type = NewTowerDialog::WILDERNESS;
      ran_index = qrand() % 7;
      tower_image = wild_images_[ran_index];
    }

    std::cerr << tower_image.width() << std::endl;

    QDockWidget* dock = new QDockWidget(tower->name(), d_->main_window());
    NewTowerDialog* dialog = new NewTowerDialog(d_, tower, tower_image);
    dialog->init(dock);
    dock->setFloating(1);
    dock->setWidget(dialog);
    dock->setAllowedAreas(Qt::NoDockWidgetArea);
    dock->move(QPoint(100, 50));
    d_->main_window()->addDockWidget(Qt::RightDockWidgetArea, dock);
  }


}
