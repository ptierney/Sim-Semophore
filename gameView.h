#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

namespace Sem {
  class Device;
  class GameScene;

  class GameView : public QGraphicsView {
    Q_OBJECT

  public:
    GameView(Device*, GameScene* scene);
    void init();

    static const bool USE_OPENGL = true;

  protected:
    void wheelEvent(QWheelEvent* event);
    void scaleView(qreal);

  private:
    Device* d_;
    GameScene* game_scene_;
  };
}

#endif // GAMEVIEW_H
