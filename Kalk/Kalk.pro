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
    dividebyzero_error.cpp \
    complessoint.cpp \
    complessodouble.cpp \
    matriceint.cpp \
    matricedouble.cpp \
    polinomioint.cpp \
    polinomiodouble.cpp \
    button.cpp \
    kalkbutton.cpp \
    kalkcomplessoint.cpp \
    kalkcomplessodouble.cpp \
    kalkmatriceint.cpp \
    kalkmatricedouble.cpp \
    kalkpolinomioint.cpp \
    kalkpolinomiodouble.cpp

HEADERS  += mainwindow.h \
    boundchecker.h \
    dividebyzero_error.h \
    matrice.h \
    complesso.h \
    monomio.h \
    polinomio.h \
    complessoint.h \
    complessoarithmeticexecutor.h \
    complessodouble.h \
    matriceint.h \
    matrixarithmeticexecutor.h \
    matricedouble.h \
    polinomioint.h \
    polynomialarithmeticexecutor.h \
    polinomiodouble.h \
    complexviewcalculator.h \
    button.h \
    kalkbutton.h \
    kalkcomplessoint.h \
    kalkcomplessodouble.h \
    kalkmatriceint.h \
    kalkmatricedouble.h \
    kalkpolinomioint.h \
    kalkpolinomiodouble.h \
    kalktemplateview.h

FORMS    += mainwindow.ui
