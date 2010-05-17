#ifndef TILEIMAGELOADER_H
#define TILEIMAGELOADER_H

#include <map>

#include <QImage>

namespace Sem {
  class Device;

class TileImageLoader : public QObject {
  Q_OBJECT

public:
  TileImageLoader(Device*, QObject* parent = 0);
  void init();

  enum TileType {
    NONE = 0,
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
    RIVER,
    SWAMP,
    SEA,
    SEMAPHORE,
    SELECT
  };

  static const int TILE_WIDTH = 128;
  static const int TILE_HEIGHT = 64;
  static const int LARGE_TILE_HEIGHT = 88;

  int tile_width();
  int tile_height();

  QImage& loadImage(TileType, int, int);
  void loadTest();
  QImage cropImage(const QImage&, int x_index, int y_index,
                   int image_height);

  std::vector<QImage>& towers_r();
  std::vector<QImage>& towers_l();
  std::vector<QImage>& towers_v();
  std::vector<QImage>& towers_h();

  QImage& null_image();

  QImage& select_icon();

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
  QImage select_image_;
  QImage river_image_;
  QImage sea_image_;
  QImage semaphore_image_;

  QImage null_image_;
  QImage select_icon_;

  std::vector<QImage> towers_r_;
  std::vector<QImage> towers_l_;
  std::vector<QImage> towers_v_;
  std::vector<QImage> towers_h_;

  std::map<TileType, std::map<int, std::map<int, QImage> > > image_cache_;
};

}


#endif // TILEIMAGELOADER_H
