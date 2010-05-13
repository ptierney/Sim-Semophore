
#include <engineer.h>
#include <device.h>
#include <tower.h>
#include <gameState.h>

namespace Sem {

  Engineer::Engineer(Device* d, Tower* tower){
    d_ = d;
    tower_ = tower;
    messages_sent_ = 0;
    mistakes_ = 0;
    name_ = "Claude Chappe";
  }

  void Engineer::init(){
    date_hired_ = d_->game_state()->current_date();
  }

  const QDate& Engineer::date_hired(){
    return date_hired();
  }

  float Engineer::accuracy(){
    return 1.0;
  }

  float Engineer::speed(){
    return 1.0;
  }

  float Engineer::satisfaction(){
    return 1.0;
  }

  int Engineer::mistakes(){
    return mistakes_;
  }

  int Engineer::messages_sent(){
    return messages_sent_;
  }

  const QString& Engineer::name(){
    return name_;
  }

}
