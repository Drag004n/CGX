#include "mainwindow.h"
#include "oglwidget.h"
#include "vertex.h"
#include <QApplication>
#include "triangle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Triangle triangle;

    triangle.ReadData("C:\\Users\\k-ht\\Documents\\Studium\\Computergrafik\\CGX\\OpenGL_Example\\tetra.obj");

    return a.exec();
}
