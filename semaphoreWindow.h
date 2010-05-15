#ifndef SEMAPHOREWINDOW_H
#define SEMAPHOREWINDOW_H

#include <QMainWindow>

#include <device.h>

namespace Ui {
    class SemaphoreWindow;
}

class SemaphoreWindow : public QMainWindow {
    Q_OBJECT
public:
    SemaphoreWindow(QWidget *parent = 0);
    ~SemaphoreWindow();

  public slots:
    void buildSemaphore();
    void cancelBuilding();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SemaphoreWindow *ui;
    Sem::Device* d_;

    QMenu* build_menu_;
    QAction* build_semaphore_;
    QAction* cancel_building_;

    void createMenus();
    void createActions();

};

#endif // SEMAPHOREWINDOW_H
