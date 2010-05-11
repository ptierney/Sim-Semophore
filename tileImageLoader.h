#ifndef TILEIMAGELOADER_H
#define TILEIMAGELOADER_H

#include <QImage>

namespace Sem {

class TileImageLoader : public QObject {
  Q_OBJECT

public:
  TileImageLoader(QObject* parent = 0);
  void init();

  enum TileType {
    CITY,
    GRASSLAND,
    PLANE,
    FOREST,
    HILL,
    MOUNTAIN,
    FARMLAND,
    IRRIGATION,
    ROAD,
    RAILROAD,
    SWAMP
  };

  static const int TILE_WIDTH = 128;
  static const int TILE_HEIGHT = 64;

  QImage loadImage(TileType, int, int);

private:
  QImage city_image_;
  QImage grass_image_;
  QImage plane_image_;
  QImage forest_image_;
  QImage hill_image_;
  QImage mountain_image_;
  QImage farmland_image_;
  QImage irrigation_image_;
  QImage road_image_;
  QImage railroad_image_;
  QImage swamp_image_;



};

}


#endif // TILEIMAGELOADER_H
