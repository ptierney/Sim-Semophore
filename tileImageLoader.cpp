
#include <iostream>

#include <QImage>

#include <tileImageLoader.h>
#include <tile.h>
#include <device.h>
#include <gameScene.h>

namespace Sem {

  TileImageLoader::TileImageLoader(Device* d, QObject* parent) :
      QObject(parent) {
    d_ = d;
  }

  void TileImageLoader::init(){

    city_image_.load("media/cities.png");
    grass_image_.load("media/g.png");
    plane_image_.load("media/p.png");
    forest_image_.load("forests.png");
    hill_image_.load("media/hills.png");
    mountain_image_.load("media/mountains.png");
    farmland_image_.load("media/farmlands.png");
    irrigation_image_.load("media/irrigations.png");
    road_image_.load("media/roads.png");
    railroad_image_.load("media/rails.png");
    swamp_image_.load("media/swamps.png");
  }

  QImage TileImageLoader::loadImage(TileType tile_type, int x_index, int y_index){
    QImage* temp_image;
    int image_height;

    switch(tile_type) {
    case CITY:
      temp_image = &city_image_;
      image_height = TILE_HEIGHT;
      break;
    case GRASSLAND:
      temp_image = &grass_image_;
      image_height = TILE_HEIGHT;
      break;
    case PLANE:
      temp_image = &plane_image_;
      image_height = TILE_HEIGHT;
      break;
    case FOREST:
      temp_image = &forest_image_;
      image_height = LARGE_TILE_HEIGHT;
      break;
    case HILL:
      temp_image = &hill_image_;
      image_height = TILE_HEIGHT;
      break;
    case MOUNTAIN:
      temp_image = &mountain_image_;
      image_height = LARGE_TILE_HEIGHT;
      break;
    case FARMLAND:
      temp_image = &farmland_image_;
      image_height = TILE_HEIGHT;
      break;
    case IRRIGATION:
      temp_image = &irrigation_image_;
      image_height = TILE_HEIGHT;
      break;
    case ROAD:
      temp_image = &road_image_;
      image_height = TILE_HEIGHT;
      break;
    case RAILROAD:
      temp_image = &railroad_image_;
      image_height = TILE_HEIGHT;
      break;
    case SWAMP:
      temp_image = &swamp_image_;
      image_height = TILE_HEIGHT;
      break;
    default:
      return city_image_;
      image_height = TILE_HEIGHT;
    }

    return cropImage(*temp_image, x_index, y_index, image_height);
  }

  QImage TileImageLoader::cropImage(const QImage& image, int x_index, int y_index,
                                    int image_height){
    QImage::Format format = image.format();
    int new_data_x = 0;
    int new_data_y = 0;

    QImage new_image = QImage(TILE_WIDTH, image_height, format);

    for(int y = y_index * image_height; y < (y_index+1) * image_height; ++y){
      new_data_x = 0;
      for(int x = x_index * TILE_WIDTH; x < (x_index+1) * TILE_WIDTH; ++x) {
        new_image.setPixel(new_data_x, new_data_y, image.pixel(x, y));
        ++new_data_x;
      }
      ++new_data_y;
    }

    return new_image;
  }

  void TileImageLoader::loadTest(){
    Tile* tile = new Tile(d_);
    tile->init();

    tile->set_axon_image(loadImage(MOUNTAIN, 2, 1));
    d_->game_scene()->addItem(tile);
    tile->update();
  }

}
