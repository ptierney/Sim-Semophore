
#include <QtGui>
#include <QVariant>


#include <mapChanger.h>
#include <tile.h>
#include <device.h>
#include <mapBuilder.h>

namespace Sem {

  MapChanger::MapChanger(Device* d, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
  }

  void MapChanger::init() {
    terrain_box_ = new QComboBox(this);
    terrain_box_->addItem(tr("plane"), TileImageLoader::PLANE);
    terrain_box_->addItem(tr("grass"), TileImageLoader::GRASSLAND);
    terrain_box_->addItem(tr("sea"), TileImageLoader::SEA);
    terrain_box_->addItem(tr("ignore"), -1);

    covering_terrain_box_ = new QComboBox(this);
    covering_terrain_box_->addItem(tr("ignore"), -1);
    covering_terrain_box_->addItem(tr("hill"), TileImageLoader::HILL);
    covering_terrain_box_->addItem(tr("forest"), TileImageLoader::FOREST);
    covering_terrain_box_->addItem(tr("mountain"), TileImageLoader::MOUNTAIN);
    covering_terrain_box_->addItem(tr("swamp"), TileImageLoader::SWAMP);
    covering_terrain_box_->addItem(tr("river"), TileImageLoader::RIVER);
    covering_terrain_box_->addItem(tr("none"), TileImageLoader::NONE);

    covering_object_box_ = new QComboBox(this);
    covering_object_box_->addItem(tr("ignore"), -1);
    covering_object_box_->addItem(tr("city"), TileImageLoader::CITY);
    covering_object_box_->addItem(tr("road"), TileImageLoader::ROAD);
    covering_object_box_->addItem(tr("railroad"), TileImageLoader::RAILROAD);
    covering_object_box_->addItem(tr("farmland"), TileImageLoader::FARMLAND);
    covering_object_box_->addItem(tr("irrigation"), TileImageLoader::IRRIGATION);
    covering_object_box_->addItem(tr("semaphore"), TileImageLoader::SEMAPHORE);
    covering_object_box_->addItem(tr("none"), TileImageLoader::NONE);

    terrain_index_1 = new QLineEdit(this);
    terrain_index_2 = new QLineEdit(this);
    covering_terrain_index_1 = new QLineEdit(this);
    covering_terrain_index_2 = new QLineEdit(this);
    covering_object_index_1 = new QLineEdit(this);
    covering_object_index_2 = new QLineEdit(this);
    arrondissement_ = new QLineEdit(this);
    show_text_ = new QCheckBox(this);
    expand_name_ = new QCheckBox(this);

    x_spread_ = new QLineEdit(this);
    y_spread_ = new QLineEdit(this);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(terrain_box_);
    main_layout->addWidget(terrain_index_1);
    main_layout->addWidget(terrain_index_2);
    main_layout->addWidget(covering_terrain_box_);
    main_layout->addWidget(covering_terrain_index_1);
    main_layout->addWidget(covering_terrain_index_2);
    main_layout->addWidget(covering_object_box_);
    main_layout->addWidget(covering_object_index_1);
    main_layout->addWidget(covering_object_index_2);
    main_layout->addSpacing(20);
    main_layout->addWidget(arrondissement_);
    main_layout->addWidget(show_text_);
    main_layout->addWidget(expand_name_);
    main_layout->addSpacing(20);
    main_layout->addWidget(x_spread_);
    main_layout->addWidget(y_spread_);

    setLayout(main_layout);
  }

  void MapChanger::objectSelected(Tile *tile){
    QString num_x_str = x_spread_->text();
    QString num_y_str = y_spread_->text();
    int num_x, num_y;

    if(expand_name_->checkState() == Qt::Checked){
      arrondissement_->setText(tile->arrondissement());
    }

    if(!num_x_str.toStdString().empty() &&
       !num_y_str.toStdString().empty() ){
      num_x = num_x_str.toInt();
      num_y = num_y_str.toInt();
      int start_x = tile->x_index() - num_x / 2;
      int start_y = tile->y_index() - num_y / 2;

      for(int y = start_y; y < start_y + num_y; ++y){
        for(int x = start_x; x < start_x + num_x; ++x){
          int index = y * 250 + x;
          changeTile(d_->map_builder()->map_tiles()[index], true);
        }
      }
    } else {
      changeTile(tile, false);
    }
  }

  void MapChanger::changeTile(Tile* tile, bool multi){

    bool set_terrain = terrain_box_->itemData(terrain_box_->currentIndex()).toInt() < 0 ? false : true;
    bool set_cover = covering_terrain_box_->itemData(covering_terrain_box_->currentIndex()).toInt() < 0 ? false : true;
    bool set_object = covering_object_box_->itemData(covering_object_box_->currentIndex()).toInt() < 0 ? false : true;

    TileImageLoader::TileType terrain_type = (TileImageLoader::TileType)
                                             terrain_box_->itemData(terrain_box_->currentIndex()).toInt();
    TileImageLoader::TileType cov_terrain_type = (TileImageLoader::TileType)
                                                 covering_terrain_box_->itemData(covering_terrain_box_->currentIndex()).toInt();
    TileImageLoader::TileType cov_object_type = (TileImageLoader::TileType)
                                                covering_object_box_->itemData(covering_object_box_->currentIndex()).toInt();

    int index1, index2;
    QImage image;

    if(set_terrain){
      index1 = terrain_index_1->text().toInt();
      index2 = terrain_index_2->text().toInt();

      image = d_->tile_image_loader()->loadImage(terrain_type, index1, index2);
      tile->set_axon_image(image, terrain_type, index1, index2);
    }

    if(set_cover){
      index1 = covering_terrain_index_1->text().toInt();
      index2 = covering_terrain_index_2->text().toInt();

      image = d_->tile_image_loader()->loadImage(cov_terrain_type, index1, index2);
      tile->set_covering_terrain(image, cov_terrain_type, index1, index2);
    }

    if(set_object){
        index1 = covering_object_index_1->text().toInt();
        index2 = covering_object_index_2->text().toInt();

        image = d_->tile_image_loader()->loadImage(cov_object_type, index1, index2);
        tile->set_covering_object(image, cov_object_type, index1, index2);
    }

    if(!arrondissement_->text().toStdString().empty())
      tile->set_arrondissement(arrondissement_->text());

    if(!multi){
      if(show_text_->checkState() == Qt::Checked)
        tile->set_show_text(true);
      else
        tile->set_show_text(false);
    }
  }


}
