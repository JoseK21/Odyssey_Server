#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T23:50:24
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Odyssey_Server
TEMPLATE = app


SOURCES += main.cpp\
         odyssey_s.cpp \
    quicksort.cpp \
    radixsort.cpp \
    bubblesort.cpp \
    binarysearchtree.cpp \
    btree.cpp \
    avltree.cpp

HEADERS  += odyssey_s.h

FORMS    += odyssey_s.ui

RESOURCES += \
    imagen.qrc

QMAKE_CXXFLAGS += -std=gnu++14
