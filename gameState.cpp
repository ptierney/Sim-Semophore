
#include <gameState.h>

namespace Sem {

  GameState::GameState(Device* d){
    d_ = d;
    current_date_ = QDate(1793, 9, 24);
    end_date_ = QDate(1846, 7, 3);
    title_ = BOTTOM;
    rank_ = FIRST;
    money_ = 58400;

    title_map_[BOTTOM] = QString("Inenieur Telegraphe");
    title_map_[LOW] = tr("Bonne");
    title_map_[MEDIUM] = tr("Chevaliers de Legione d'Honneur");
    title_map_[HIGH] = tr("Tres Bonne");
    title_map_[HIGHEST] = tr("Napoleon V");

    rank_map_[FIRST] = tr("Lueutenant");
    rank_map_[SECOND] = tr("Capitaine");
    rank_map_[THIRD] = tr("Commandant");
    rank_map_[FORTH] = tr("Colonel");
    rank_map_[FIFTH] = tr("Emperor");

    grass_cost_ = 3500;
    plane_cost_ = 2500;
    forest_cost_ = -400;
    hill_cost_ = -400;
    mountain_cost_ = -2000;
    city_cost_ = 1000;
    farm_cost_ = 600;
    railroad_cost_ = -400;
  }

  int GameState::daysRemaining(){
    return current_date_.daysTo(end_date_);
  }

  const QDate& GameState::current_date(){
    return current_date_;
  }

  const QDate& GameState::end_date(){
    return end_date_;
  }

  int GameState::money(){
    return money_;
  }

  void GameState::addMoney(int money){
    money_ += money;
  }

  void GameState::set_money(int money){
    money_ = money;
  }

  GameState::Rank GameState::rank(){
    return rank_;
  }

  QString GameState::rankString(){
    return rank_map_[rank_];
  }

  GameState::Title GameState::title(){
    return title_;
  }

  QString GameState::titleString(){
    return title_map_[title_];
  }

}
