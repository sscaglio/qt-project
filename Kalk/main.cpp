#include "mainwindow.h"
#include <QApplication>

#include<iostream>

#include "complessoint.h"
#include "complexviewcalculator.h"
#include "matriceint.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow x;
    x.show();
    return a.exec();
}
