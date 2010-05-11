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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SemaphoreWindow *ui;
    Sem::Device* d_;
};

#endif // SEMAPHOREWINDOW_H
