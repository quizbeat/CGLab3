#-------------------------------------------------
#
# Project created by QtCreator 2014-09-23T00:05:43
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FirstQtWidgetApp
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    glview.cpp

HEADERS  += widget.h \
    glview.h

FORMS    += widget.ui
