
#include <math.h>

#include <iostream>

#include <QGLWidget>
#include <QWheelEvent>

#include <gameView.h>
#include <gameScene.h>

namespace Sem {
  GameView::GameView(Device* d, GameScene* scene) :
      QGraphicsView(scene) {
    d_ = d;
    setScene(scene);
    game_scene_ = scene;
  }

  void GameView::init(){
    if(USE_OPENGL){
      QGLFormat format;
      format.setSampleBuffers(true);
      // This is how you force the View to draw everything in OpenGL
      QGLWidget* gl_widget = new QGLWidget(format);
      setViewport(gl_widget);
    }

    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);

    setDragMode( QGraphicsView::ScrollHandDrag);

    setMinimumSize(game_scene_->DEFAULT_WINDOW_WIDTH,
                   game_scene_->DEFAULT_WINDOW_HEIGHT);
  }

  void GameView::wheelEvent(QWheelEvent* event) {
    scaleView(pow((double)2, event->delta() / 540.0));
  }

  void GameView::scaleView(qreal scale_factor){
      scale(scale_factor, scale_factor);
  }
}
