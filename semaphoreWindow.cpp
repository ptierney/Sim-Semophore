#include "semaphoreWindow.h"
#include "ui_semaphoreWindow.h"

SemaphoreWindow::SemaphoreWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SemaphoreWindow)
{
    ui->setupUi(this);

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
