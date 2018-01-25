#ifndef KALKCOMPLESSOINT_H
#define KALKCOMPLESSOINT_H

#include "kalkbutton.h"
#include "complessoint.h"

#include <QWidget>
#include<QLineEdit>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>

#include <QDebug>

class KalkComplessoInt : public QWidget
{
    Q_OBJECT

public:
    KalkComplessoInt(QWidget *parent = 0);

private slots:

    void insertComplexClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void backspaceClicked();
    void clear();
    void clearAll();

private:
    KalkButton *createKalkButton(const QString &text, const char *member);
    bool calculate(const ComplessoInt&, const QString &);

    ComplessoInt sumInMemory;
    ComplessoInt sumSoFar;
    ComplessoInt factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;
};

#endif // KALKCOMPLESSOINT_H
