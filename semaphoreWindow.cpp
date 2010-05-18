#include "semaphoreWindow.h"
#include "ui_semaphoreWindow.h"

#include <device.h>
#include <towerCreator.h>

SemaphoreWindow::SemaphoreWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SemaphoreWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();

    d_ = new Sem::Device(this);
    d_->init();
}

SemaphoreWindow::~SemaphoreWindow()
{
    delete d_;
    delete ui;
}

void SemaphoreWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SemaphoreWindow::buildSemaphore(){
  d_->tower_creator()->build();
}

void SemaphoreWindow::cancelBuilding(){
  d_->tower_creator()->cancelBuilding();
}

void SemaphoreWindow::cancelConnection(){
  d_->tower_creator()->cancelConnection();

}

void SemaphoreWindow::changeGlobally(){
  d_->tower_creator()->changeGlobally();
}

void SemaphoreWindow::setZoom(Sem::GameState::Zoom zoom){
  d_->game_state()->set_zoom(zoom);
}

void SemaphoreWindow::setSpeed(Sem::GameState::GameSpeed speed){
  d_->game_state()->set_game_speed(speed);
}

void SemaphoreWindow::createActions(){
  build_semaphore_ = new QAction(tr("Build semaphore..."), this);
  connect(build_semaphore_, SIGNAL(triggered()),
          this, SLOT(buildSemaphore()));

  cancel_building_ = new QAction(tr("Cancel building semaphore"), this);
  connect(cancel_building_, SIGNAL(triggered()),
          this, SLOT(cancelBuilding()));

  cancel_connection_ = new QAction(tr("Cancel creating connection"), this);
  connect(cancel_connection_, SIGNAL(triggered()),
          this, SLOT(cancelConnection()));

  change_global_settings_ = new QAction(tr("Change semaphore settings globally..."), this);
  change_global_settings_->setEnabled(false);
  connect(change_global_settings_, SIGNAL(triggered()),
          this, SLOT(changeGlobally()));

  zoom_1_ = new QAction(tr("Normal zoom"), this);
  connect(zoom_1_, SIGNAL(triggered()),
          this, SLOT(zoom1()));

  zoom_2_ = new QAction(tr("Zoom out some"), this);
  connect(zoom_2_, SIGNAL(triggered()),
          this, SLOT(zoom2()));

  zoom_3_ = new QAction(tr("Zoom out more"), this);
  connect(zoom_3_, SIGNAL(triggered()),
          this, SLOT(zoom3()));

  zoom_4_ = new QAction(tr("Zoom out most"), this);
  connect(zoom_4_, SIGNAL(triggered()),
          this, SLOT(zoom4()));

  speed_1_ = new QAction(tr("Slow speed"), this);
  connect(speed_1_, SIGNAL(triggered()),
          this, SLOT(speed1()));
  speed_2_ = new QAction(tr("Normal speed"), this);
  connect(speed_2_, SIGNAL(triggered()),
          this, SLOT(speed2()));
  speed_3_ = new QAction(tr("Fast speed"), this);
  connect(speed_3_, SIGNAL(triggered()),
          this, SLOT(speed3()));
  speed_4_ = new QAction(tr("Eleven"), this);
  connect(speed_4_, SIGNAL(triggered()),
          this, SLOT(speed4()));
}

void SemaphoreWindow::zoom1() { setZoom(Sem::GameState::NORMAL); }
void SemaphoreWindow::zoom2() { setZoom(Sem::GameState::OUT_1); }
void SemaphoreWindow::zoom3() { setZoom(Sem::GameState::OUT_2); }
void SemaphoreWindow::zoom4() { setZoom(Sem::GameState::OUT_3); }

void SemaphoreWindow::speed1() { setSpeed(Sem::GameState::SLOW); }
void SemaphoreWindow::speed2() { setSpeed(Sem::GameState::MEDIUM); }
void SemaphoreWindow::speed3() { setSpeed(Sem::GameState::FAST); }
void SemaphoreWindow::speed4() { setSpeed(Sem::GameState::ELEVEN); }

void SemaphoreWindow::createMenus() {
  build_menu_ = menuBar()->addMenu(tr("Build"));
  build_menu_->addAction(build_semaphore_);
  build_menu_->addAction(cancel_building_);
  build_menu_->addAction(cancel_connection_);
  management_menu_ = menuBar()->addMenu(tr("Management"));
  management_menu_->addAction(change_global_settings_);
  speed_menu_ = menuBar()->addMenu(tr("Set Game Speed"));
  speed_menu_->addAction(speed_1_);
  speed_menu_->addAction(speed_2_);
  speed_menu_->addAction(speed_3_);
  speed_menu_->addAction(speed_4_);
  zoom_menu_ = menuBar()->addMenu(tr("Set Zoom"));
  zoom_menu_->addAction(zoom_1_);
  zoom_menu_->addAction(zoom_2_);
  zoom_menu_->addAction(zoom_3_);
  zoom_menu_->addAction(zoom_4_);
}
