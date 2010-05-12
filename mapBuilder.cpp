
#include <mapBuilder.h>
#include <device.h>
#include <tile.h>
#include <tileImageLoader.h>
#include <gameScene.h>

namespace Sem {

  MapBuilder::MapBuilder(Device* d, QObject* parent) :
      QObject(parent) {
    d_ = d;
    config_file_ = "config.txt";

  }

  void MapBuilder::init() {

  }

  void MapBuilder::buildMap(){
    int x_spacing = d_->tile_image_loader()->tile_width()/2;
    int y_spacing = d_->tile_image_loader()->tile_height();
    QImage default_image = d_->tile_image_loader()->loadImage(TileImageLoader::GRASSLAND, 1, 7);
    int y_pos;

    for(int x = 0; x < 1; ++x){
      for(int y = 0; y < 1; ++y){
        Tile* tile = new Tile(d_);
        tile->init();
        tile->set_axon_image(default_image);
        y_pos = y * y_spacing;
        if(x % 2 == 0)
           y_pos += y_spacing / 2;
        tile->setPos(x * x_spacing, y_pos);
        d_->game_scene()->addItem(tile);
        map_tiles_.push_back(tile);
      }
    }

  }



}
