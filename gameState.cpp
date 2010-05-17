
#include <iostream>

#include <gameState.h>
#include <device.h>
#include <dateBox.h>
#include <gameView.h>
#include <towerCreator.h>
#include <infoBox.h>

namespace Sem {

  GameState::GameState(Device* d){
    d_ = d;
    current_date_ = QDate(1793, 9, 24);
    end_date_ = QDate(1846, 7, 3);
    title_ = LEVEL_1;
    rank_ = FIRST;
    money_ = 58400;

    title_map_[LEVEL_1] = QString("Inenieur Telegraphe");
    title_map_[LEVEL_2] = tr("Ministre des Telegraphes");
    title_map_[LEVEL_3] = tr("Chevaliers de Legione d'Honneur");
    title_map_[LEVEL_4] = tr("President");
    title_map_[LEVEL_5] = tr("Napoleon V");

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

    cities_connected_ = 0;

    zoom_ = NORMAL;
    game_speed_ = MEDIUM;
  }

  void GameState::init(){
    startTimer(2000);
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

  void GameState::timerEvent(QTimerEvent* /*event*/){
    int day_jump;

    switch(game_speed_){
    case SLOW:
      day_jump = 1;
      break;
    case FAST:
      day_jump = (qrand() % 4 + 8) * 2; // One game in 15 minutes
      break;
    case ELEVEN:
      day_jump = qrand() % 10 + 70;
      break;
    case MEDIUM:
    default:
      day_jump = qrand() % 4 + 8; // One game in 30 minutes
      break;
    }

    updateTowers(day_jump);

    // Collect money
    money_ += d_->tower_creator()->collectMoney();

    // Get cites
    cities_connected_ = d_->tower_creator()->getCitiesConnected();

    // Check Rank and Title
    updateRank();
    updateTitle();

    current_date_ = current_date_.addDays(day_jump);
    d_->date_box()->updateLabels();
    d_->date_box()->update();
    d_->info_box()->updateValues();
    d_->info_box()->update();
  }

  void GameState::set_zoom(Zoom zoom){
    zoom_ = zoom;

    QMatrix zoom_matrix = d_->game_view()->matrix();
    QMatrix new_matrix;
    float scale_amount;

    switch (zoom_){
    case OUT_1:
      scale_amount = 0.75;
      break;
    case OUT_2:
      scale_amount = 0.5;
      break;
    case OUT_3:
      scale_amount = 0.25;
      break;
    case NORMAL:
    default:
      scale_amount = 1.0;
      break;
    }

    new_matrix.setMatrix(scale_amount, zoom_matrix.m12(), zoom_matrix.m21(), scale_amount,
                         zoom_matrix.dx(), zoom_matrix.dy());

    d_->game_view()->setMatrix(new_matrix);
  }


  void GameState::set_game_speed(GameSpeed speed){
    game_speed_ = speed;
  }

  void GameState::updateTowers(int days){
    d_->tower_creator()->updateTowers(days);
  }

  // Rank is based on money
  // 0-7 = 1
  // 8-49 = 2
  // 49-100 = 3
  // 100-200 = 4
  // >200 = 5
  void GameState::updateTitle(){
    if(cities_connected_ < 8 )
    title_ = LEVEL_1;
    else if(cities_connected_ < 50)
    title_ = LEVEL_2;
    else if(cities_connected_ < 100)
    title_ = LEVEL_3;
    else if(cities_connected_ < 200)
    title_ = LEVEL_4;
    else
    title_ = LEVEL_5;
  }

  // Title is based on cities connected
  // 0 - 65000
  // 130000
  // 260000
  // 520000
  // 1040000
  void GameState::updateRank(){
    if(money_ < 65000)
      rank_ = FIRST;
    else if(money_ < 130000)
      rank_ = SECOND;
    else if(money_ < 260000)
      rank_ = THIRD;
    else if(money_ < 520000)
      rank_ = FORTH;
    else
      rank_ = FIFTH;
  }

  int GameState::cities_connected(){
    return cities_connected_;
  }

}
