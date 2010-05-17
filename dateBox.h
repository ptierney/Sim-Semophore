#ifndef DATEBOX_H
#define DATEBOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace Sem {
  class Device;

  class DateBox : public QWidget {

  public:
    DateBox(Device*, QWidget* parent = 0);
    void init();

    void updateLabels();

  private:
    Device* d_;
    QLabel* current_date_;
    QLabel* end_date_;
    QLabel* remaining_time_;
    QLabel* money_;
    QLabel* title_;
    QLabel* rank_;
    QLabel* cities_connected_;
  };
}

#endif // DATEBOX_H
