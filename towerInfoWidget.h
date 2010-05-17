#ifndef TOWERINFOWIDGET_H
#define TOWERINFOWIDGET_H

#include <QWidget>
#include <QtGui>

namespace Sem {
  class Device;
  class InfoBox;
  class Tower;

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

    void payChanged(int);
    void speed1Changed(int);
    void speed2Changed(int);
    void speed3Changed(int);
    void speed4Changed(int);
    void speed5Changed(int);

  private:
    Device* d_;
    InfoBox* info_box_;
    int spacing_;

    QVBoxLayout* layout_;

    QLabel* connected_to_paris_;

    QPushButton* set_tower_1_;
    QPushButton* set_tower_2_;

    QLabel* pay_label_;
    QSlider* pay_slider_;

    QHBoxLayout* pay_layout_;
    QHBoxLayout* speed_layout_;
    QHBoxLayout* speed_layout_text_;
    QSlider* speed_slider_1_;
    QSlider* speed_slider_2_;
    QSlider* speed_slider_3_;
    QSlider* speed_slider_4_;
    QSlider* speed_slider_5_;
    QLabel* pay_;
    QLabel* speeds_label_;
    QLabel* speed_1_;
    QLabel* speed_2_;
    QLabel* speed_3_;
    QLabel* speed_4_;
    QLabel* speed_5_;

    QLabel* accuracy_;
    QLabel* total_balance_;
    QLabel* total_messages_sent_;

    Tower* current_tower_;
  };
}

#endif // TOWERINFOWIDGET_H
