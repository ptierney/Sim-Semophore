#include <QtGui/QApplication>
#include "semaphoreWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SemaphoreWindow w;
    w.show();
    return a.exec();
}
