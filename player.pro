#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T21:54:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = player
TEMPLATE = app


SOURCES += main.cpp\
        user_interface.cpp \
    videostream.cpp

HEADERS  += user_interface.h \
    videostream.h

FORMS    += user_interface.ui

INCLUDEPATH += "C:/Program Files/openCV/opencv/build/install/include"
LIBS += -L"C:/Program Files/openCV/opencv/build/bin" \
        -lopencv_core2412d \
        -lopencv_highgui2412d \
        -lopencv_imgproc2412d

