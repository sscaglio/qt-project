#include "mainwindow.h"
#include <QApplication>

// libreria limiti (sia per float che per interi)
#include<limits>
#include<iostream>

#include"boundchecker.h"
#include "complesso.h"

using std::numeric_limits;
using std::cout;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Complesso<int> t1 = Complesso<int>(1,4);
    Complesso<int> t2 = Complesso<int>(1,-1);

    Complesso<int> t3 = t1 * t2;
    t3.printAll();

    return a.exec();
}
