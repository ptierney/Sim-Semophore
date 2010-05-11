
#include <QGLWidget>

#include <gameView.h>
#include <gameScene.h>

namespace Sem {
  GameView::GameView(Device* d, GameScene* scene) :
      QGraphicsView(scene) {
    d_ = d;

    if(USE_OPENGL){
      QGLFormat format;
      format.setSampleBuffers(true);
      // This is how you force the View to draw everything in OpenGL
      QGLWidget* gl_widget = new QGLWidget(format);
      setViewport(gl_widget);
    }

    setScene(scene);

    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);

    setDragMode( QGraphicsView::ScrollHandDrag);
  }

}
