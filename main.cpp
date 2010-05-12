#include <QtGui/QApplication>
#include <QSplashScreen>
#include "semaphoreWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("media/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    SemaphoreWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
