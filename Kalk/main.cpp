#include "mainwindow.h"
#include <QApplication>

#include "matriceint.h"
#include<iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MatriceInt x1 = MatriceInt(3,2);
    MatriceInt x2 = MatriceInt(3,2);

    for(int i = 0; i < 3 *2;++i){
        x1.insertValue(i);
        x2.insertValue(i);
    }

    MatriceInt x3 = MatriceInt(2,3);
    for(int i = 0 ; i < 2 * 3;++i){
        x3.insertValue(i);
    }
    (x1 + x2).printAll();
    cout << std::endl;
    (x1 - x2).printAll();
    cout << std::endl;
    (x1 * x3).printAll();
   /* x1.printAll();
    cout << std::endl;
    x1.factorial().printAll();
    cout << std::endl;
*/
    return a.exec();
}
