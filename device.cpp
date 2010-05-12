
#include <QMainWindow>

#include <device.h>
#include <gameScene.h>
#include <gameView.h>
#include <tileImageLoader.h>

namespace Sem {

  Device::Device(QMainWindow* main_window) :
      QObject(main_window) {
    main_window_ = main_window;
  }

  void Device::init() {
    game_scene_ = new GameScene(this, main_window_);
    game_scene_->init();
    game_view_ = new GameView(this, game_scene_);
    game_view_->init();

    main_window_->setCentralWidget(game_view_);

    tile_image_loader_ = new TileImageLoader(this);
    tile_image_loader_->init();
    tile_image_loader_->loadTest();
  }

  Device::~Device(){
    // Nothing here
  }

  TileImageLoader* Device::tile_image_loader(){
    return tile_image_loader_;
  }

  GameScene* Device::game_scene(){
    return game_scene_;
  }

}
