
#include <tower.h>
#include <engineer.h>

namespace Sem {

  Tower::Tower(Device* d, Tile* tile){
    d_ = d;
    tile_ = tile;
  }

  void Tower::init(){
    engineer_1_ = new Engineer(d_, this);
    engineer_2_ = new Engineer(d_, this);
  }

  const QDate& Tower::date_created(){
    return date_created_;
  }

  Engineer* Tower::engineer_1(){
    return engineer_1_;
  }

  Engineer* Tower::engineer_2(){
    return engineer_2_;
  }

}
