#include "mainwindow.h"
#include <QApplication>

#include "monomio.h"
#include<iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Monomio<int> t1 = Monomio<int>(1,1);
    Monomio<int> t2 = Monomio<int>(1,1);

    (t1 + t2).printAll();
    (t1 - t2).printAll();
    (t1 * t2).printAll();
    (t1 / t2).printAll();


    return a.exec();
}
