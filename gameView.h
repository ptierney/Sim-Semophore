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

    static const bool USE_OPENGL = true;

  private:
    Device* d_;
  };
}

#endif // GAMEVIEW_H
