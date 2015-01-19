#-------------------------------------------------
#
# Project created by QtCreator 2015-01-19T14:23:00
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = camunits-log-viewer-qt
TEMPLATE = app


SOURCES += main.cpp\
        displaywidget.cpp \
    glscreen.cpp

HEADERS  += displaywidget.h \
    glscreen.h

FORMS    += displaywidget.ui
