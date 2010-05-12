
#include <QMainWindow>

#include <device.h>
#include <gameScene.h>
#include <gameView.h>
#include <tileImageLoader.h>
#include <mapBuilder.h>

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
    //tile_image_loader_->loadTest();

    map_builder_ = new MapBuilder(this);
    map_builder_->init();
    //map_builder_->buildMap();
  }

  Device::~Device(){
    delete map_builder_;
    delete tile_image_loader_;
  }

  TileImageLoader* Device::tile_image_loader(){
    return tile_image_loader_;
  }

  GameScene* Device::game_scene(){
    return game_scene_;
  }

}
