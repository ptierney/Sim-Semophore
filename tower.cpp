
#include <tower.h>
#include <engineer.h>
#include <tile.h>

namespace Sem {

  Tower::Tower(Device* d, Tile* tile){
    d_ = d;
    tile_ = tile;
    name_ = "Poste telegraphique de region sauvage";
    tower_1_ = NULL;
    tower_2_ = NULL;
    operating_percentage_ = 100;
    message_rate_ = 100;
  }

  void Tower::init(){
    engineer_1_ = new Engineer(d_, this);
    engineer_2_ = new Engineer(d_, this);

    if(tile_->arrondissement_set()){
      name_ = "Poste telegraphique de " + tile_->arrondissement();
    } else {
      QString x, y;
      x.setNum(tile_->x_index());
      y.setNum(tile_->y_index());
      name_ = "Poste telegraphique " + x + " par " + y;
    }
  }

  const QDate& Tower::date_created(){
    return date_created_;
  }

  const QString& Tower::name(){
    return name_;
  }

  Engineer* Tower::engineer_1(){
    return engineer_1_;
  }

  Engineer* Tower::engineer_2(){
    return engineer_2_;
  }

  Tower* Tower::tower_1(){
    return tower_1_;
  }

  Tower* Tower::tower_2(){
    return tower_2_;
  }

  float Tower::operating_percentage(){
    return operating_percentage_;
  }

  float Tower::message_rate(){
    return message_rate_;
  }
}
