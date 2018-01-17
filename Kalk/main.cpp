#include "mainwindow.h"
#include <QApplication>

// libreria limiti (sia per float che per interi)
#include<limits>
#include<iostream>

#include"boundchecker.h"
#include "matrice.h"

using std::numeric_limits;
using std::cout;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
