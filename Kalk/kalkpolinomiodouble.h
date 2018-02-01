#ifndef KALKPOLINOMIODOUBLE_H
#define KALKPOLINOMIODOUBLE_H

#include "cleaner.h"
#include "kalkbutton.h"
#include "polinomiodouble.h"
#include "abstractkalk.h"

#include <QWidget>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QRegExpValidator>
#include<QValidator>
#include<QPushButton>

#include <QDebug>

class KalkPolinomioDouble : public AbstractKalk
{
    Q_OBJECT
public:
    explicit KalkPolinomioDouble(QWidget *parent = 0);
    virtual void setUpLayout(QGridLayout *);
     bool calculate(const PolinomioDouble&, const QString &);

public slots:
    void insertTypeClicked();
    void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void backspaceClicked();
    void clear();
    void clearAll();


private:
    KalkButton *createKalkButton(const QString &text, const char *member);


    PolinomioDouble sumInMemory;
    PolinomioDouble sumSoFar;
    PolinomioDouble factorSoFar;

};

#endif // KALKPOLINOMIODOUBLE_H
