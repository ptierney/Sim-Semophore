#ifndef NEWTOWERDIALOG_H
#define NEWTOWERDIALOG_H

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace Sem {
  class Device;
  class Tower;

  class NewTowerDialog : public QDialog {

  public:
    NewTowerDialog(Device*,
                   Tower*,
                   QImage,
                   QWidget* parent = 0);
    void init(QWidget* parent);

    enum TowerType {
      CITY,
      WILDERNESS
    };

  private:
    Device* d_;
    QPixmap main_image_;
    QLabel* tower_image_;
    QLabel* tower_created_;
    QLabel* date_created_;
    Tower* tower_;
  };
}

#endif // NEWTOWERDIALOG_H
