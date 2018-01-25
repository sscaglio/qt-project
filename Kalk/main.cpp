#include "mainwindow.h"
#include <QApplication>

#include<iostream>

#include "polinomiodouble.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    PolinomioDouble x1 = PolinomioDouble();
    x1.testOperation();

    w.show();
    return a.exec();
}
