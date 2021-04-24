#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl
QT      += openglwidgets
LIBS    += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengl1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp \
    triangle.cpp \
    vertex.cpp

HEADERS  += mainwindow.h \
    oglwidget.h \
    triangle.h \
    vertex.h

FORMS    += mainwindow.ui

DISTFILES += \
    tetra.obj
