#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include<QGroupBox>
#include<QPushButton>
#include<QVBoxLayout>
#include<QDialog>
#include<iostream>

#include "abstractcalc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void showComplexIntMode();
    void showComplexRealMode();
    void showMatrixIntMode();
    void showMatrixRealMode();
    void showPolynomialIntMode();
    void showPolynomialRealMode();
};

#endif // MAINWINDOW_H
