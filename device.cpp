
#include <QMainWindow>

#include <device.h>
#include <gameScene.h>
#include <gameView.h>
#include <tileImageLoader.h>
#include <mapBuilder.h>
#include <mapChanger.h>
#include <miniMapView.h>
#include <gameState.h>
#include <dateBox.h>
#include <infoBox.h>

namespace Sem {

  Device::Device(QMainWindow* main_window) :
      QObject(main_window) {
    main_window_ = main_window;
  }

  void Device::init() {
    game_scene_ = new GameScene(this, main_window_);
    game_scene_->init();

    tile_image_loader_ = new TileImageLoader(this);
    tile_image_loader_->init();
    //tile_image_loader_->loadTest();

    map_builder_ = new MapBuilder(this);
    map_builder_->init(); // loads config, builds map
    //map_builder_->buildMap();

    game_view_ = new GameView(this, game_scene_);
    game_view_->init();
    main_window_->setCentralWidget(game_view_);

    createMapChanger();

    game_state_ = new GameState(this);

    //createMiniMap();
    createDateBox();
    createInfoBox();
  }

  Device::~Device(){
    delete map_builder_;
    delete tile_image_loader_;
  }

  void Device::createMapChanger(){
    QDockWidget* dock = new QDockWidget(tr("Map Changer"), main_window_);
    dock->setFloating(1);
    map_changer_ = new MapChanger(this, dock);
    map_changer_->init();
    dock->setWidget(map_changer_);
    dock->setAllowedAreas(Qt::NoDockWidgetArea);
    main_window_->addDockWidget(Qt::LeftDockWidgetArea, dock);
  }

  void Device::createMiniMap(){
    QDockWidget* dock = new QDockWidget(tr("Mini Map"), main_window_);
    dock->setFloating(0);
    mini_map_view_ = new MiniMapView(this, game_scene_);
    mini_map_view_->init();
    dock->setWidget(mini_map_view_);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    main_window_->addDockWidget(Qt::RightDockWidgetArea, dock);
  }

  void Device::createDateBox(){
    QDockWidget* dock = new QDockWidget(tr("Game Progress"), main_window_);
    dock->setFloating(0);
    date_box_ = new DateBox(this);
    date_box_->init();
    dock->setWidget(date_box_);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    main_window_->addDockWidget(Qt::RightDockWidgetArea, dock);
  }

  void Device::createInfoBox(){
    QDockWidget* dock = new QDockWidget(tr("Info"), main_window_);
    dock->setFloating(0);
    info_box_ = new InfoBox(this);
    info_box_->init();
    dock->setWidget(info_box_);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    main_window_->addDockWidget(Qt::RightDockWidgetArea, dock);
  }

  TileImageLoader* Device::tile_image_loader(){
    return tile_image_loader_;
  }

  GameScene* Device::game_scene(){
    return game_scene_;
  }

  MapChanger* Device::map_changer(){
    return map_changer_;
  }

  GameState* Device::game_state(){
    return game_state_;
  }

  InfoBox* Device::info_box(){
    return info_box_;
  }

}
