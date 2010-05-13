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

  private:
    Device* d_;
    InfoBox* info_box_;

    QVBoxLayout* layout_;
  };
}

#endif // TOWERINFOWIDGET_H
