#-------------------------------------------------
#
# Project created by QtCreator 2018-01-11T16:49:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kalk
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dividebyzero_error.cpp

HEADERS  += mainwindow.h \
    boundchecker.h \
    dividebyzero_error.h \
    matrice.h \
    complesso.h

FORMS    += mainwindow.ui
