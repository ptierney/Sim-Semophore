#ifndef SEMAPHOREWINDOW_H
#define SEMAPHOREWINDOW_H

#include <QMainWindow>

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
};

#endif // SEMAPHOREWINDOW_H
