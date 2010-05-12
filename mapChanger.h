#ifndef MAPCHANGER_H
#define MAPCHANGER_H

#include <QWidget>
#include <QtGui>

#include <tileImageLoader.h>

namespace Sem {
  class Device;
  class Tile;

  class MapChanger : public QWidget {
    Q_OBJECT

  public:
    MapChanger(Device*, QWidget* parent = 0);
    void init();

    void objectSelected(Tile*);

  private:
    Device* d_;

    QComboBox* terrain_box_;
    QComboBox* covering_terrain_box_;
    QComboBox* covering_object_box_;

    QLineEdit* terrain_index_1;
    QLineEdit* terrain_index_2;
    QLineEdit* covering_terrain_index_1;
    QLineEdit* covering_terrain_index_2;
    QLineEdit* covering_object_index_1;
    QLineEdit* covering_object_index_2;
  };


}


#endif // MAPCHANGER_H
