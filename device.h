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

  class Device : public QObject {
    Q_OBJECT

  public:
    Device(QMainWindow*);
    ~Device();
    void init();

    TileImageLoader* tile_image_loader();
    GameScene* game_scene();

  private:
    QMainWindow* main_window_;

    GameScene* game_scene_;
    GameView* game_view_;
    TileImageLoader* tile_image_loader_;

  };

}


#endif // DEVICE_H
