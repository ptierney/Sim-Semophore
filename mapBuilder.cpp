
#include <iostream>

#include <QTextStream>
#include <QStringList>

#include <mapBuilder.h>
#include <device.h>
#include <tile.h>
#include <tileImageLoader.h>
#include <gameScene.h>
#include <mapChanger.h>

namespace Sem {

  MapBuilder::MapBuilder(Device* d, QObject* parent) :
      QObject(parent) {
    d_ = d;
    config_file_name_ = "config.txt";
    num_tiles_x_ = 250;
    num_tiles_y_ = 250 * 2;
  }

  void MapBuilder::init() {

    loadConfig();
  }

  MapBuilder::~MapBuilder(){
    saveConfig();
    for(std::vector<Tile*>::iterator it = map_tiles_.begin(); it != map_tiles_.end(); ++it){
      delete (*it);
    }
  }


  void MapBuilder::loadConfig(){
    std::cout << "Loading config" << std::endl;

    config_file_ = new QFile(config_file_name_);
    config_file_->open(QIODevice::ReadWrite);
    QTextStream stream(config_file_);

    QString num_x = stream.readLine();
    QString num_y = stream.readLine();

    Tile* tile;
    num_tiles_x_ = num_x.toInt();
    num_tiles_y_ = num_y.toInt();

    int x_spacing = d_->tile_image_loader()->tile_width();
    int y_spacing = d_->tile_image_loader()->tile_height()/2;
    QString line;
    QStringList list;
    QImage temp_image;
    int index1;
    int index2;
    TileImageLoader::TileType type;
    int parse;
    int x_pos;

    bool hit_sea;


    for(int y = 0; y < num_tiles_y_; ++y){
      hit_sea = false;
      for(int x = 0; x < num_tiles_x_; ++x){
        //std::cerr << x << " : " << y << std::endl;

        tile = new Tile(d_);
        tile->init();

        line = stream.readLine();
        list = line.split(tr(","));

        /*
        if( list.length() < 11){
          foreach(QString str, list){
            std::cerr << str.toStdString() << std::endl;
          }
        }
        */

        parse = list[0].toInt();
        index1 = list[1].toInt();
        index2 = list[2].toInt();

        switch(parse){
        case 1:
          type = TileImageLoader::GRASSLAND;
          if(false && hit_sea == false){
            type = TileImageLoader::SEA;
            index1 = 0;
            index2 = 0;
          }
          break;
        case 2:
          type = TileImageLoader::PLANE;
          break;
        case 3:
          type = TileImageLoader::SEA;
          hit_sea = true;
          break;
        default:
          type = TileImageLoader::PLANE;
          break;
        }

        /*
        if(x >= 42 && x <= 58 &&
           y >= 127 && y <= 182){
          type = TileImageLoader::SEA;
          index1 = 0;
          index2 = 0;
        }

        if(x >= 58 && x <= 76 &&
           y >= 127 && y <= 158){
          type = TileImageLoader::SEA;
          index1 = 0;
          index2 = 0;
        }


        if( x >= 207 && x <= 236 &&
            y >=485 && y <= 499){
          type = TileImageLoader::SEA;
          index1 = 0;
          index2 = 0;

        }

        if( x >= 222 && x <= 240 &&
            y >= 476 && y <= 486){
          type = TileImageLoader::SEA;
          index1 = 0;
          index2 = 0;
        }
        */



        temp_image = d_->tile_image_loader()->loadImage(type, index1, index2);
        tile->set_axon_image(temp_image, type, index1, index2);

        parse = list[3].toInt();
        switch(parse){
        case 1:
          type = TileImageLoader::HILL;
          break;
        case 2:
          type = TileImageLoader::FOREST;
          break;
        case 3:
          type = TileImageLoader::MOUNTAIN;
          break;
        case 4:
          type = TileImageLoader::SWAMP;
          break;
        case 5:
          type = TileImageLoader::RIVER;
          break;
        default:
          type = TileImageLoader::NONE;
          break;
        }
/*
        if( x >= 203 && x <= 226 &&
            y >= 398 && y <= 469){
          type = TileImageLoader::NONE;
        }
        */

        if(type != TileImageLoader::NONE){
          index1 = list[4].toInt();
          index2 = list[5].toInt();
          temp_image = d_->tile_image_loader()->loadImage(type, index1, index2);
          tile->set_covering_terrain(temp_image, type, index1, index2);
        }

        parse = list[6].toInt();
        switch(parse){
        case 1:
          type = TileImageLoader::CITY;
          break;
        case 2:
          type = TileImageLoader::FARMLAND;
          /*
          temp_image = d_->tile_image_loader()->loadImage(TileImageLoader::PLANE,
                                                          2, 14);
          tile->set_axon_image(temp_image, TileImageLoader::PLANE, 2, 14);
          */
          break;
        case 3:
          type = TileImageLoader::IRRIGATION;
          break;
        case 4:
          type = TileImageLoader::ROAD;
          break;
        case 5:
          type = TileImageLoader::RAILROAD;
          break;
        default:
          type = TileImageLoader::NONE;
          break;
        }

        if(type != TileImageLoader::NONE){
          index1 = list[7].toInt();
          index2 = list[8].toInt();
          temp_image = d_->tile_image_loader()->loadImage(type, index1, index2);
          tile->set_covering_object(temp_image, type, index1, index2);
        }

        tile->set_arrondissement(list[9]);
        bool show_text;
        if(list[10].toInt() == 1)
          show_text = true;
        else
          show_text = false;

        x_pos = x * x_spacing;
        if(y % 2 == 0)
           x_pos -= x_spacing / 2;
        tile->setPos(x_pos, y * y_spacing);
        tile->set_x_index(x);
        tile->set_y_index(y);
        tile->set_show_text(show_text); // Needs to go after pos has been set
        d_->game_scene()->addItem(tile);
        map_tiles_.push_back(tile);
      }
    }

    config_file_->close();
  }

  void MapBuilder::saveConfig(){
    std::cout << "Saving config" << std::endl;

    config_file_ = new QFile(config_file_name_);
    config_file_->open(QIODevice::ReadWrite | QIODevice::Truncate); // erase old contents

    QTextStream stream(config_file_);

    QString num_x, num_y;
    num_x.setNum(num_tiles_x_);
    num_y.setNum(num_tiles_y_);

    stream << num_x << "\n" << num_y << "\n";

    for(std::vector<Tile*>::const_iterator it = map_tiles_.begin(); it != map_tiles_.end(); ++it){
      Tile* tile = (*it);
      TileImageLoader::TileType terrain_type = tile->terrain_type();
      TileImageLoader::TileType covering_terrain_type = tile->covering_terrain_type();
      TileImageLoader::TileType covering_object_type = tile->covering_object_type();

      if(terrain_type != TileImageLoader::NONE){
        switch(terrain_type) {
        case TileImageLoader::GRASSLAND:
          stream << "1,";
          break;
        case TileImageLoader::PLANE:
          stream << "2,";
          break;
        case TileImageLoader::SEA:
          stream << "3,";
          break;
        default:
          stream << "0,";
          std::cerr << "ERROR saving config" << std::endl;
          break;
        }

        QString in1, in2;
        in1.setNum(tile->terrain_index().first);
        in2.setNum(tile->terrain_index().second);
        stream << in1 << "," << in2 << ",";
      } else {
        stream << "0,0,0,";
      }

      if(covering_terrain_type != TileImageLoader::NONE){
        switch(covering_terrain_type){
        case TileImageLoader::HILL:
          stream << "1,";
          break;
        case TileImageLoader::FOREST:
          stream << "2,";
          break;
        case TileImageLoader::MOUNTAIN:
          stream << "3,";
          break;
        case TileImageLoader::SWAMP:
          stream << "4,";
          break;
        case TileImageLoader::RIVER:
          stream << "5,";
          break;
        default:
          stream << "0,";
          std::cerr << "ERROR saving config" << std::endl;
          break;

        }

        QString in1, in2;
        in1.setNum(tile->covering_terrain_index().first);
        in2.setNum(tile->covering_terrain_index().second);
        stream << in1 << "," << in2 << ",";

      } else {
        stream << "0,0,0,";
      }

      if(covering_object_type != TileImageLoader::NONE){
        switch(covering_object_type){
        case TileImageLoader::CITY:
          stream << "1,";
          break;
        case TileImageLoader::FARMLAND:
          stream << "2,";
          break;
        case TileImageLoader::IRRIGATION:
          stream << "3,";
          break;
        case TileImageLoader::ROAD:
          stream << "4,";
          break;
        case TileImageLoader::RAILROAD:
          stream << "5,";
          break;
        default:
          stream << "0,";
          std::cerr << "ERROR saving config" << std::endl;
          break;
        }

        QString in1, in2;
        in1.setNum(tile->covering_object_index().first);
        in2.setNum(tile->covering_object_index().second);
        stream << in1 << "," << in2 << ",";
      } else {
        stream << "0,0,0,";
      }

      stream << tile->arrondissement();

      if(tile->show_text())
        stream << ",1";
      else
        stream << ",0";

      stream << "\n";
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
        tile->set_axon_image(default_image, TileImageLoader::GRASSLAND, 1, 7);
        //tile->set_covering_object(default_object, TileImageLoader::RAILROAD, 15, 15);
        //tile->set_covering_terrain(default_terrain, TileImageLoader::HILL, 0, 0);
        x_pos = x * x_spacing;
        if(y % 2 == 0)
           x_pos -= x_spacing / 2;
        tile->setPos(x_pos, y * y_spacing);
        d_->game_scene()->addItem(tile);
        map_tiles_.push_back(tile);
      }
    }

  }

  int MapBuilder::num_tiles_x(){
    return num_tiles_x_;
  }

  int MapBuilder::num_tiles_y(){
    return num_tiles_y_;
  }

  std::vector<Tile*>& MapBuilder::map_tiles(){
    return map_tiles_;
  }

}
