#include "mainwindow.h"
#include <QApplication>

#include "polinomio.h"
#include<iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Polinomio<int>p2 = Polinomio<int>();

    p2.testSum();

    return a.exec();
}
