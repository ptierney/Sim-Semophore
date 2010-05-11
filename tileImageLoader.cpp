
#include <QImage>

#include <tileImageLoader.h>

namespace Sem {

  TileImageLoader::TileImageLoader(QObject* parent) :
      QObject(parent) {
  }

  void TileImageLoader::init(){

    city_image_.load(":/media/cities.png");
    grass_image_.load(":/media/g.png");
    plane_image_.load(":/media/p.png");
    forest_image_.load(":/forests.png");
    hill_image_.load(":/media/hills.png");
    mountain_image_.load(":/media/mountains.png");
    farmland_image_.load(":/media/farmlands.png");
    irrigation_image_.load(":/media/irrigations.png");
    road_image_.load(":/media/roads.png");
    railroad_image_.load(":/media/rails.png");
    swamp_image_.load(":/media/swamps.png");
  }

  QImage TileImageLoader::loadImage(TileType tile_type, int x_index, int y_index){
    if(tile_type == CITY){

    }
    return city_image_;
  }

}
