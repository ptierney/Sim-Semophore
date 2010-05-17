
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
    forest_image_.load("media/forests.png");
    hill_image_.load("media/hills.png");
    mountain_image_.load("media/mountains.png");
    farmland_image_.load("media/farmlands.png");
    irrigation_image_.load("media/irrigations.png");
    road_image_.load("media/roads.png");
    railroad_image_.load("media/rails.png");
    swamp_image_.load("media/swamps.png");
    select_image_.load("media/select-alpha.png");
    river_image_.load("media/rivers.png");
    sea_image_.load("media/s.png");
    semaphore_image_.load("media/semaphore.png");

    select_icon_ = loadImage(TileImageLoader::SELECT, 0, 0);

    towers_r_.push_back(QImage(tr("animation/sem_r1.png")));
    towers_r_.push_back(QImage(tr("animation/sem_r2.png")));
    towers_r_.push_back(QImage(tr("animation/sem_r3.png")));

    towers_l_.push_back(QImage(tr("animation/sem_l1.png")));
    towers_l_.push_back(QImage(tr("animation/sem_l2.png")));
    towers_l_.push_back(QImage(tr("animation/sem_l3.png")));
    towers_l_.push_back(QImage(tr("animation/sem_l4.png")));
    towers_l_.push_back(QImage(tr("animation/sem_l5.png")));

    towers_v_.push_back(QImage(tr("animation/sem_v1.png")));
    towers_v_.push_back(QImage(tr("animation/sem_v2.png")));
    towers_v_.push_back(QImage(tr("animation/sem_v3.png")));
    towers_v_.push_back(QImage(tr("animation/sem_v4.png")));
    towers_v_.push_back(QImage(tr("animation/sem_v5.png")));
    towers_v_.push_back(QImage(tr("animation/sem_v6.png")));

    towers_h_.push_back(QImage(tr("animation/sem_h1.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h2.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h3.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h4.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h5.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h6.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h7.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h8.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h9.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h10.png")));
    towers_h_.push_back(QImage(tr("animation/sem_h11.png")));
  }

  QImage& TileImageLoader::loadImage(TileType tile_type, int x_index, int y_index){
    QImage* temp_image;
    int image_height;

    QImage& found_image = image_cache_[tile_type][x_index][y_index];
    if( found_image.width() != 0 )
      return found_image;//image_cache_[tile_type][x_index][y_index];

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
    case SELECT:
      temp_image = &select_image_;
      image_height = TILE_HEIGHT;
      break;
    case RIVER:
      temp_image = &river_image_;
      image_height = TILE_HEIGHT;
      break;
    case SEMAPHORE:
      temp_image = &semaphore_image_;
      image_height = LARGE_TILE_HEIGHT;
      break;
    case SEA:
      temp_image = &sea_image_;
      image_height = TILE_HEIGHT;
      break;
    default:
      return city_image_;
      image_height = TILE_HEIGHT;
    }

    image_cache_[tile_type][x_index][y_index] = cropImage(*temp_image, x_index, y_index, image_height);
    return image_cache_[tile_type][x_index][y_index];
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
    //Tile* tile = new Tile(d_);
    //tile->init();

    //tile->set_axon_image(loadImage(MOUNTAIN, 2, 1), 2, 1);
    //d_->game_scene()->addItem(tile);
    //tile->update();
  }

  int TileImageLoader::tile_width(){
    return TILE_WIDTH;
  }

  int TileImageLoader::tile_height(){
    return TILE_HEIGHT;
  }

  std::vector<QImage>& TileImageLoader::towers_r(){
    return towers_r_;
  }

  std::vector<QImage>& TileImageLoader::towers_l(){
    return towers_l_;
  }

  std::vector<QImage>& TileImageLoader::towers_v(){
    return towers_v_;
  }

  std::vector<QImage>& TileImageLoader::towers_h(){
    return towers_h_;
  }

  QImage& TileImageLoader::null_image(){
    return null_image_;
  }

  QImage& TileImageLoader::select_icon(){
    return select_icon_;
  }

}
