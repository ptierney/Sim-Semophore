#ifndef TOWERINFOWIDGET_H
#define TOWERINFOWIDGET_H

#include <QWidget>

#include <infoBox.h>

namespace Sem {
  class Device;
  class InfoBox;

  class TowerInfoWidget : public QWidget {
    Q_OBJECT
  public:
    TowerInfoWidget(Device*, InfoBox*, QWidget* parent = 0);
    void init();

    void createLayout();

  public slots:
    void setTower1();
    void setTower2();

  private:
    Device* d_;
    InfoBox* info_box_;
    int spacing_;

    QVBoxLayout* layout_;

    QPushButton* set_tower_1_;
    QPushButton* set_tower_2_;
  };
}

#endif // TOWERINFOWIDGET_H
