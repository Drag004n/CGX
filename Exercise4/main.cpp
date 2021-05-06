#include "mainwindow.h"
#include "oglwidget.h"
#include "vertex.h"
#include <QApplication>
#include "triangle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
