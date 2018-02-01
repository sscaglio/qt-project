#ifndef KALKCOMPLESSODOUBLE_H
#define KALKCOMPLESSODOUBLE_H


#include "abstractkalk.h"
#include "cleaner.h"
#include "kalkbutton.h"
#include "complessodouble.h"

#include <QWidget>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>

#include <QDebug>

class KalkComplessoDouble : public AbstractKalk
{
public:
    KalkComplessoDouble(QWidget *parent = 0);
    virtual void setUpLayout(QGridLayout *);
public slots:

    virtual void insertTypeClicked();
    virtual void unaryOperatorClicked();
    virtual void additiveOperatorClicked();
    virtual void multiplicativeOperatorClicked();
    virtual void equalClicked();
    virtual void backspaceClicked();
    virtual void clear();
    virtual void clearAll();

private:
    bool calculate(const ComplessoDouble&, const QString &);

    ComplessoDouble sumInMemory;
    ComplessoDouble sumSoFar;
    ComplessoDouble factorSoFar;
};


#endif // KALKCOMPLESSODOUBLE_H
