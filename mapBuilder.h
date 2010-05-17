#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include <string>
#include <vector>

#include <QObject>
#include <QFile>

namespace Sem {
  class Device;
  class Tile;
  class MapChanger;

  class MapBuilder : public QObject {
    Q_OBJECT

  public:
    MapBuilder(Device*, QObject* parent = 0);
    ~MapBuilder();
    void init();

    void buildMap();

    void loadConfig();
    void saveConfig();

    MapChanger* map_changer();

    int num_tiles_x();
    int num_tiles_y();

    int num_cities();

    std::vector<Tile*>& map_tiles();

  private:
    Device* d_;
    MapChanger* map_changer_;
    QString config_file_name_;
    QFile* config_file_;

    int num_tiles_x_;
    int num_tiles_y_;

    int num_cities_;

    std::vector<Tile*> map_tiles_;
  };

}

#endif // MAPBUILDER_H
