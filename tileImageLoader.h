#ifndef TILEIMAGELOADER_H
#define TILEIMAGELOADER_H

#include <QImage>

namespace Sem {
  class Device;

class TileImageLoader : public QObject {
  Q_OBJECT

public:
  TileImageLoader(Device*, QObject* parent = 0);
  void init();

  enum TileType {
    CITY,
    GRASSLAND,
    PLANE,
    FOREST, // NOTE: large tile
    HILL,
    MOUNTAIN, // NOTE: large tile
    FARMLAND,
    IRRIGATION,
    ROAD,
    RAILROAD,
    SWAMP
  };

  static const int TILE_WIDTH = 128;
  static const int TILE_HEIGHT = 64;
  static const int LARGE_TILE_HEIGHT = 88;

  QImage loadImage(TileType, int, int);
  void loadTest();
  QImage cropImage(const QImage&, int x_index, int y_index,
                   int image_height);

private:
  Device* d_;

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