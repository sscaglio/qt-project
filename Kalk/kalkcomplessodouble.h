#ifndef KALKCOMPLESSODOUBLE_H
#define KALKCOMPLESSODOUBLE_H

#include "kalkbutton.h"
#include "complessodouble.h"

#include <QWidget>
#include<QLineEdit>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>

#include <QDebug>

class KalkComplessoDouble : public QWidget
{
    Q_OBJECT

public:
    KalkComplessoDouble(QWidget *parent = 0);

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
    bool calculate(const ComplessoDouble&, const QString &);

    ComplessoDouble sumInMemory;
    ComplessoDouble sumSoFar;
    ComplessoDouble factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;
};


#endif // KALKCOMPLESSODOUBLE_H
