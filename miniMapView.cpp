
#include <QGLWidget>

#include <miniMapView.h>
#include <gameScene.h>
#include <device.h>

namespace Sem {

  MiniMapView::MiniMapView(Device* d, GameScene* scene) :
      QGraphicsView(scene) {
    d_ = d;
    setScene(scene);
    game_scene_ = scene;
  }

  void MiniMapView::init(){
    if(USE_OPENGL){
      QGLFormat format;
      format.setSampleBuffers(true);
      // This is how you force the View to draw everything in OpenGL
      QGLWidget* gl_widget = new QGLWidget(format);
      setViewport(gl_widget);
    }

    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);

    setMinimumSize(200, 200);

    fitInView(game_scene_->itemsBoundingRect());
  }

}
