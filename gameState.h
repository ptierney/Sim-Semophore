#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <map>

#include <QObject>
#include <QDate>

namespace Sem {
  class Device;

  class GameState : public QObject {
  public:
    GameState(Device*);

    const QDate& current_date();
    const QDate& end_date();
    int daysRemaining();
    int money();
    void addMoney(int);
    void set_money(int);

    enum Title {
      BOTTOM,
      LOW,
      MEDIUM,
      HIGH,
      HIGHEST
    };

    enum Rank {
      FIRST,
      SECOND,
      THIRD,
      FORTH,
      FIFTH
    };

    Rank rank();
    QString rankString();
    Title title();
    QString titleString();

    int grass_cost() { return grass_cost_; }
    int plane_cost() { return plane_cost_; }
    int forest_cost() { return forest_cost_; }
    int hill_cost() { return hill_cost_; }
    int mountain_cost() { return mountain_cost_; }
    int city_cost() { return city_cost_; }
    int farm_cost() { return farm_cost_; }
    int railroad_cost() { return railroad_cost_; }

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

  };

}

#endif // GAMESTATE_H
