#ifndef MINIMAPVIEW_H
#define MINIMAPVIEW_H

#include <QGraphicsView>

namespace Sem {
  class Device;
  class GameScene;

  class MiniMapView : public QGraphicsView {
    Q_OBJECT

  public:
    MiniMapView(Device*, GameScene* scene);
    void init();

    static const bool USE_OPENGL = true;

  private:
    Device* d_;
    GameScene* game_scene_;
  };
}

#endif // MINIMAPVIEW_H
