#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

namespace Sem {
  class Device;

  class GameScene : public QGraphicsScene {
    Q_OBJECT

  public:
    GameScene(Device*, QObject* parent = 0);
    void init();

    QSize sizeHint() const;

    static const int DEFAULT_WINDOW_WIDTH = 1000;
    static const int DEFAULT_WINDOW_HEIGHT = 750;

  private:
    Device* d_;
  };
}

#endif // GAMESCENE_H
