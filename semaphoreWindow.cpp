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

void SemaphoreWindow::createActions(){
  build_semaphore_ = new QAction(tr("Build Semaphore..."), this);
  connect(build_semaphore_, SIGNAL(triggered()),
          this, SLOT(buildSemaphore()));

}

void SemaphoreWindow::createMenus() {
  build_menu_ = menuBar()->addMenu(tr("Build"));
  build_menu_->addAction(build_semaphore_);
}
