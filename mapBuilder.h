#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include <string>
#include <vector>

#include <QObject>

namespace Sem {
  class Device;
  class Tile;

  class MapBuilder : public QObject {
    Q_OBJECT

  public:
    MapBuilder(Device*, QObject* parent = 0);
    void init();

    void buildMap();

  private:
    Device* d_;
    std::string config_file_;

    std::vector<Tile*> map_tiles_;
  };

}

#endif // MAPBUILDER_H
