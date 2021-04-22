#include "mainwindow.h"
#include "oglwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OGLWidget og;
    MainWindow w;
    w.show();

    og.output();



    return a.exec();
}
