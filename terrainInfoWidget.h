#ifndef TERRAININFOWIDGET_H
#define TERRAININFOWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

namespace Sem {
  class Device;
  class InfoBox;

  class TerrainInfoWidget : public QWidget {
    Q_OBJECT
  public:
    TerrainInfoWidget(Device*, InfoBox*, QWidget* parent = 0);
    void init();

    void createLayout();

  private:
    Device* d_;
    InfoBox* info_box_;

    QVBoxLayout* layout_;
  };


}

#endif // TERRAININFOWIDGET_H
