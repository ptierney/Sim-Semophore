
#include <QtGui>

#include <newTowerDialog.h>
#include <device.h>
#include <tileImageLoader.h>
#include <tower.h>

namespace Sem {

  NewTowerDialog::NewTowerDialog(Device* d,
                                 Tower* tower,
                                 QImage tower_image,
                                 QWidget* parent) :
    QDialog(parent) {
    d_ = d;
    tower_ = tower;
    main_image_ = QPixmap::fromImage(tower_image);
  }

  void NewTowerDialog::init(QWidget* parent){
    QHBoxLayout* layout_h = new QHBoxLayout();
    QVBoxLayout* layout_lv = new QVBoxLayout();
    QVBoxLayout* layout_rv = new QVBoxLayout();
    tower_image_ = new QLabel();
    date_created_ = new QLabel();
    tower_created_ = new QLabel();

    tower_image_->setPixmap(main_image_);
    layout_lv->addWidget(tower_image_);

    tower_created_->setText(tower_->name() + tr(" expands the French Nation!"));
    date_created_->setText(tr("Erected ") + tower_->date_created().toString("MMMM d, yyyy."));

    layout_rv->addWidget(tower_created_);
    layout_rv->addWidget(date_created_);

    QPushButton* push = new QPushButton(tr("Tres Bien!"));
    connect(push, SIGNAL(released()),
            parent, SLOT(close()));
    push->setMaximumWidth(100);
    push->setMinimumHeight(80);

    layout_rv->addWidget(push);
    layout_rv->addSpacing(50);

    layout_h->addLayout(layout_lv);
    layout_h->addLayout(layout_rv);

    setLayout(layout_h);
  }
}
