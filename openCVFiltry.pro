#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T20:11:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openCVFiltry
TEMPLATE = app

INCLUDEPATH += D:\\opencv\\build\\include
LIBS += -LD:\\opencv\\build\\x64\\vc14\\lib -lopencv_world310d

SOURCES += main.cpp\
        mainwindow.cpp \
    imagehandler.cpp \
    filtersettingswindow.cpp

HEADERS  += mainwindow.h \
    imagehandler.h \
    filtersettingswindow.h
