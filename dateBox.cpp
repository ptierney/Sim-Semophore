
#include <QLabel>
#include <QtGui>

#include <dateBox.h>
#include <device.h>
#include <gameState.h>

namespace Sem {

  DateBox::DateBox(Device* d, QWidget* parent) :
      QWidget(parent) {
    d_ = d;
  }

  void DateBox::init(){
    QVBoxLayout* main_layout = new QVBoxLayout;
    current_date_ = new QLabel();
    remaining_time_ = new QLabel();
    end_date_ = new QLabel();
    money_ = new QLabel();
    title_ = new QLabel();
    rank_ = new QLabel();

    updateLabels();

    main_layout->addWidget(current_date_);
    main_layout->addWidget(end_date_);
    main_layout->addWidget(remaining_time_);
    main_layout->addWidget(money_);
    main_layout->addWidget(title_);
    main_layout->addWidget(rank_);

    setLayout(main_layout);

    update();
  }

  void DateBox::updateLabels(){
    current_date_->setText(tr("Current Date: ") +
                           d_->game_state()->current_date().toString(tr("MMMM d, yyyy")));
    current_date_->update();
    end_date_->setText(tr("Electrification of telegraphs: ") +
                       d_->game_state()->end_date().toString(tr("MMMM d, yyyy")));
    QString days_remaining;
    days_remaining.setNum(d_->game_state()->daysRemaining());
    remaining_time_->setText(tr("Days remaining: ") + days_remaining);
    remaining_time_->update();

    QString money;
    money.setNum(d_->game_state()->money());
    money_->setText(tr("Money: Fr. ") + money);

    title_->setText(tr("Title: ") + d_->game_state()->titleString());
    rank_->setText(tr("Rank: ") + d_->game_state()->rankString());

  }
}
