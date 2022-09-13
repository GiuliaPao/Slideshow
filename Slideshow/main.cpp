#include "mainwindow.h"
#include "myslideshow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MySlideshow s;
    MainWindow w(&s);
    w.show();
    return a.exec();
}
