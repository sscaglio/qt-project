#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    QWidget * buttonBox = new QWidget(this);

    QPushButton *complexIntButton = new QPushButton(tr("complessi interi"));
    connect(complexIntButton,SIGNAL(clicked()),this,SLOT(showComplexIntMode()));

    QPushButton *complexRealButton = new QPushButton(tr("complessi reali"));
    connect(complexRealButton,SIGNAL(clicked()),this,SLOT(showComplexRealMode()));

    QPushButton *matrixIntButton = new QPushButton(tr("matrici intere"));
    connect(matrixIntButton,SIGNAL(clicked()),this,SLOT(showMatrixIntMode()));

    QPushButton *matrixRealButton = new QPushButton(tr("matrici reali"));
    connect(matrixRealButton,SIGNAL(clicked()),this,SLOT(showMatrixRealMode()));

    QPushButton *polynomialIntButton = new QPushButton(tr("polinomi interi"));
    connect(polynomialIntButton,SIGNAL(clicked()),this,SLOT(showPolynomialIntMode()));

    QPushButton *polynomialRealButton = new QPushButton(tr("polinomi reali"));
    connect(polynomialRealButton,SIGNAL(clicked()),this,SLOT(showPolynomialRealMode()));

    QVBoxLayout *vbox = new QVBoxLayout(buttonBox);
    vbox->addWidget(complexIntButton);
    vbox->addWidget(complexRealButton);
    vbox->addWidget(matrixIntButton);
    vbox->addWidget(matrixRealButton);
    vbox->addWidget(polynomialIntButton);
    vbox->addWidget(polynomialRealButton);
    buttonBox->setLayout(vbox);
    setCentralWidget(buttonBox);
}

void
MainWindow::showComplexIntMode(){
    QWidget *prova = new QWidget();
    prova->show();
}

void
MainWindow::showComplexRealMode(){
    QWidget *prova = new QWidget();
    prova->show();
}

void
MainWindow::showMatrixIntMode(){
    QWidget *prova = new QWidget();
    prova->show();
}

void
MainWindow::showMatrixRealMode(){
    QWidget *prova = new QWidget();
    prova->show();
}

void
MainWindow::showPolynomialIntMode(){
    QWidget *prova = new QWidget();
    prova->show();
}
void
MainWindow::showPolynomialRealMode(){
    QWidget *prova = new QWidget();
    prova->show();
}
