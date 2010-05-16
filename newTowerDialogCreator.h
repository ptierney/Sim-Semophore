#ifndef NEWTOWERDIALOGCREATOR_H
#define NEWTOWERDIALOGCREATOR_H

#include <newTowerDialog.h>

namespace Sem {
  class Device;
  class Tower;

  class NewTowerDialogCreator : public QObject {
    Q_OBJECT

  public:
    NewTowerDialogCreator(Device*);
    void init();

    void create(Tower*);

  private:
    Device* d_;

    std::vector<QImage> city_images_;
    std::vector<QImage> wild_images_;

    int image_height_;
  };


}

#endif // NEWTOWERDIALOGCREATOR_H
