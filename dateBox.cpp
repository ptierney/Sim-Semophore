
#include <QLabel>
#include <QtGui>

#include <dateBox.h>
#include <device.h>
#include <gameState.h>
#include <towerCreator.h>

namespace Sem {

  DateBox::DateBox(Device* d, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
  }

  void DateBox::init(){
    QVBoxLayout* main_layout = new QVBoxLayout;
    current_date_ = new QLabel();
    current_date_->setFont(*(d_->game_font()));
    remaining_time_ = new QLabel();
    remaining_time_->setFont(*(d_->game_font()));
    end_date_ = new QLabel();
    end_date_->setFont(*(d_->game_font()));
    money_ = new QLabel();
    money_->setFont(*(d_->game_font()));
    title_ = new QLabel();
    title_->setFont(*(d_->game_font()));
    rank_ = new QLabel();
    rank_->setFont(*(d_->game_font()));
    cities_connected_ = new QLabel();
    cities_connected_->setFont(*(d_->game_font()));

    updateLabels();

    main_layout->addWidget(current_date_);
    main_layout->addWidget(end_date_);
    main_layout->addWidget(remaining_time_);
    main_layout->addWidget(money_);
    main_layout->addWidget(cities_connected_);
    main_layout->addWidget(title_);
    main_layout->addWidget(rank_);

    setLayout(main_layout);

    update();
  }

  void DateBox::updateLabels(){
    current_date_->setText(tr("Current Date: ") +
                           d_->game_state()->current_date().toString(tr("MMMM d, yyyy")));
    current_date_->update();
    end_date_->setText(tr("Telegraph Electrification: ") +
                       d_->game_state()->end_date().toString(tr("MMMM d, yyyy")));
    QString days_remaining;
    days_remaining.setNum(d_->game_state()->daysRemaining());
    remaining_time_->setText(tr("Days remaining: ") + days_remaining);
    remaining_time_->update();

    QString money;
    money.setNum(d_->game_state()->money());
    money_->setText(tr("Money: Fr. ") + money);

    QString num_cities;
    num_cities.setNum(d_->game_state()->cities_connected());
    cities_connected_->setText(tr("Cities in network: ") + num_cities);

    title_->setText(tr("Title: ") + d_->game_state()->titleString());
    rank_->setText(tr("Rank: ") + d_->game_state()->rankString());

  }
}
