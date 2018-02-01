#ifndef KALKPOLINOMIOINT_H
#define KALKPOLINOMIOINT_H


#include "abstractkalk.h"
#include "cleaner.h"
#include "kalkbutton.h"
#include "guitemplatehelper.h"
#include "polinomioint.h"

#include <QWidget>

#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QRegExpValidator>
#include<QValidator>
#include<QPushButton>

#include <QDebug>

class KalkPolinomioInt : public AbstractKalk
{
    Q_OBJECT

    friend class GUITemplateHelper<KalkPolinomioInt,PolinomioInt>;
public:
    KalkPolinomioInt(QWidget *parent = 0);
    virtual void setUpLayout(QGridLayout *);
    bool calculate(const PolinomioInt&, const QString &);

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


    PolinomioInt sumInMemory;
    PolinomioInt sumSoFar;
    PolinomioInt factorSoFar;
};

#endif // KALKPOLINOMIOINT_H
