#ifndef SEMAPHOREWINDOW_H
#define SEMAPHOREWINDOW_H

#include <QMainWindow>

#include <device.h>
#include <gameState.h>

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
    void changeGlobally();

    void zoom1();
    void zoom2();
    void zoom3();
    void zoom4();

    void speed1();
    void speed2();
    void speed3();
    void speed4();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SemaphoreWindow *ui;
    Sem::Device* d_;

    QMenu* build_menu_;
    QMenu* management_menu_;
    QMenu* speed_menu_;
    QMenu* zoom_menu_;
    QAction* build_semaphore_;
    QAction* cancel_building_;
    QAction* change_global_settings_;
    QAction* zoom_1_;
    QAction* zoom_2_;
    QAction* zoom_3_;
    QAction* zoom_4_;
    QAction* speed_1_;
    QAction* speed_2_;
    QAction* speed_3_;
    QAction* speed_4_;

    void createMenus();
    void createActions();

    void setZoom(Sem::GameState::Zoom);
    void setSpeed(Sem::GameState::GameSpeed);

};

#endif // SEMAPHOREWINDOW_H
