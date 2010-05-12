
#include <iostream>

#include <QTextStream>

#include <mapBuilder.h>
#include <device.h>
#include <tile.h>
#include <tileImageLoader.h>
#include <gameScene.h>

namespace Sem {

  MapBuilder::MapBuilder(Device* d, QObject* parent) :
      QObject(parent) {
    d_ = d;
    config_file_name_ = "config.txt";
  }

  void MapBuilder::init() {
    loadConfig();

  }


  void MapBuilder::loadConfig(){
    config_file_ = new QFile(config_file_name_);
    config_file_->open(QIODevice::ReadWrite);
    QTextStream stream(config_file_);

    QString num_x = stream.readLine();
    QString num_y = stream.readLine();

    num_tiles_x_ = num_x.toInt();
    num_tiles_y_ = num_y.toInt();

    config_file_->close();
  }

  void MapBuilder::saveConfig(){
    config_file_ = new QFile(config_file_name_);
    config_file_->open(QIODevice::Truncate); // erase old contents

    QTextStream stream(config_file_);

    QString num_x, num_y;
    num_x.setNum(num_tiles_x_);
    num_y.setNum(num_tiles_y_);

    stream << num_x << "\n" << num_y << "\n";

    for(std::vector<Tile*>::const_iterator it = map_tiles_.begin(); it != map_tiles_.end(); ++it){


    }

  }



  void MapBuilder::buildMap(){
    int x_spacing = d_->tile_image_loader()->tile_width();
    int y_spacing = d_->tile_image_loader()->tile_height()/2;
    QImage default_image = d_->tile_image_loader()->loadImage(TileImageLoader::GRASSLAND, 1, 7);
    QImage default_object = d_->tile_image_loader()->loadImage(TileImageLoader::RAILROAD, 15, 15);
    QImage default_terrain = d_->tile_image_loader()->loadImage(TileImageLoader::HILL, 0, 0);
    int x_pos;

      for(int y = 0; y < num_tiles_y_; ++y){
        for(int x = 0; x < num_tiles_x_; ++x){
        Tile* tile = new Tile(d_);
        tile->init();
        tile->set_axon_image(default_image, TileImageLoader::GRASSLAND);
        tile->set_covering_object(default_object, TileImageLoader::RAILROAD);
        //tile->set_covering_terrain(default_terrain, TileImageLoader::HILL);
        x_pos = x * x_spacing;
        if(y % 2 == 0)
           x_pos -= x_spacing / 2;
        tile->setPos(x_pos, y * y_spacing);
        d_->game_scene()->addItem(tile);
        map_tiles_.push_back(tile);
      }
    }

  }



}
