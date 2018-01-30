#ifndef KALKPOLINOMIOINT_H
#define KALKPOLINOMIOINT_H

#include "kalkbutton.h"
#include "polinomioint.h"

#include <QWidget>

#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>

#include <QDebug>

class KalkPolinomioInt : public QWidget
{
    Q_OBJECT

public:
    KalkPolinomioInt(QWidget *parent = 0);

private slots:

    void insertPolynomialClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void backspaceClicked();
    void clear();
    void clearAll();

private:
    KalkButton *createKalkButton(const QString &text, const char *member);
    bool calculate(const PolinomioInt&, const QString &);

    PolinomioInt sumInMemory;
    PolinomioInt sumSoFar;
    PolinomioInt factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;
};

#endif // KALKPOLINOMIOINT_H
