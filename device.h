#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QApplication;
class QMainWindow;
QT_END_NAMESPACE

namespace Sem {
  class GameScene;
  class GameView;
  class TileImageLoader;
  class MapBuilder;
  class MapChanger;
  class MiniMapView;
  class GameState;
  class DateBox;
  class InfoBox;
  class TowerCreator;

  class Device : public QObject {
    Q_OBJECT

  public:
    Device(QMainWindow*);
    ~Device();
    void init();

    TileImageLoader* tile_image_loader();
    GameScene* game_scene();
    MapChanger* map_changer();
    GameState* game_state();
    InfoBox* info_box();
    TowerCreator* tower_creator();

  private:
    QMainWindow* main_window_;

    GameScene* game_scene_;
    GameView* game_view_;
    MiniMapView* mini_map_view_;
    TileImageLoader* tile_image_loader_;
    MapBuilder* map_builder_;
    MapChanger* map_changer_;
    GameState* game_state_;
    DateBox* date_box_;
    InfoBox* info_box_;
    TowerCreator* tower_creator_;

    void createMapChanger();
    void createMiniMap();
    void createDateBox();
    void createInfoBox();
  };

}


#endif // DEVICE_H
