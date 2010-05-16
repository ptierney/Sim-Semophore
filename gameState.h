#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <map>

#include <QObject>
#include <QDate>

namespace Sem {
  class Device;

  class GameState : public QObject {
    Q_OBJECT
  public:
    GameState(Device*);
    void init();

    const QDate& current_date();
    const QDate& end_date();
    int daysRemaining();
    int money();
    void addMoney(int);
    void set_money(int);

    enum Title {
      LEVEL_1,
      LEVEL_2,
      LEVEL_3,
      LEVEL_4,
      LEVEL_5
    };

    enum Rank {
      FIRST,
      SECOND,
      THIRD,
      FORTH,
      FIFTH
    };

    enum GameSpeed {
      SLOW,
      MEDIUM,
      FAST,
      ELEVEN
    };

    enum Zoom {
      NORMAL,
      OUT_1,
      OUT_2,
      OUT_3
    };

    Rank rank();
    QString rankString();
    Title title();
    QString titleString();

    void set_zoom(Zoom);
    void set_game_speed(GameSpeed);

    int grass_cost() { return grass_cost_; }
    int plane_cost() { return plane_cost_; }
    int forest_cost() { return forest_cost_; }
    int hill_cost() { return hill_cost_; }
    int mountain_cost() { return mountain_cost_; }
    int city_cost() { return city_cost_; }
    int farm_cost() { return farm_cost_; }
    int railroad_cost() { return railroad_cost_; }

  protected:
    void timerEvent(QTimerEvent *);

  private:
    Device* d_;
    QDate current_date_;
    QDate end_date_;

    int money_;

    std::map<Title, QString> title_map_;
    std::map<Rank, QString> rank_map_;

    Title title_;
    Rank rank_;

    int grass_cost_;
    int plane_cost_;
    int forest_cost_;
    int hill_cost_;
    int mountain_cost_;
    int city_cost_;
    int farm_cost_;
    int railroad_cost_;

    Zoom zoom_;
    GameSpeed game_speed_;
  };

}

#endif // GAMESTATE_H
