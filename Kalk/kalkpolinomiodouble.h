#ifndef KALKPOLINOMIODOUBLE_H
#define KALKPOLINOMIODOUBLE_H

#include "kalkbutton.h"
#include "polinomiodouble.h"

#include <QWidget>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>

#include <QDebug>

class KalkPolinomioDouble : public QWidget
{
    Q_OBJECT
public:
    explicit KalkPolinomioDouble(QWidget *parent = 0);

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
    bool calculate(const PolinomioDouble&, const QString &);

    PolinomioDouble sumInMemory;
    PolinomioDouble sumSoFar;
    PolinomioDouble factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;
};

#endif // KALKPOLINOMIODOUBLE_H
