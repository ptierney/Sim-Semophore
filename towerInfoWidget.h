#ifndef TOWERINFOWIDGET_H
#define TOWERINFOWIDGET_H

#include <QWidget>
#include <QtGui>

namespace Sem {
  class Device;
  class InfoBox;

  class TowerInfoWidget : public QWidget {
    Q_OBJECT
  public:
    TowerInfoWidget(Device*, InfoBox*, QWidget* parent = 0);
    void init();

    void createLayout();

    friend class InfoBox;

  public slots:
    void setTower1();
    void setTower2();

  private:
    Device* d_;
    InfoBox* info_box_;
    int spacing_;

    QVBoxLayout* layout_;

    QLabel* connected_to_paris_;

    QPushButton* set_tower_1_;
    QPushButton* set_tower_2_;

    QSlider* pay_slider_;

    QHBoxLayout* speed_layout_;
    QSlider* speed_slider_1_;
    QSlider* speed_slider_2_;
    QSlider* speed_slider_3_;
    QSlider* speed_slider_4_;
    QSlider* speed_slider_5_;

    QLabel* accuracy_;
    QLabel* total_balance_;
    QLabel* total_messages_sent_;

  };
}

#endif // TOWERINFOWIDGET_H
