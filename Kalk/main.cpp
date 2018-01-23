#include "mainwindow.h"
#include <QApplication>

#include<iostream>

#include "polinomioint.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    PolinomioInt x1 = PolinomioInt();
    x1.testOperation();

    w.show();
    return a.exec();
}
