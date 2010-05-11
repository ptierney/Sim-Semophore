
#include <gameScene.h>

namespace Sem {
  GameScene::GameScene(Device* d,
                       QObject* parent) :
  QGraphicsScene(parent) {
    d_ = d;
  }

  QSize GameScene::sizeHint() const {
    return QSize(DEFAULT_WINDOW_WIDTH,
                 DEFAULT_WINDOW_HEIGHT);
  }

}
