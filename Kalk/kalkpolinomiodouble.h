#ifndef KALKPOLINOMIODOUBLE_H
#define KALKPOLINOMIODOUBLE_H

#include "cleaner.h"
#include "kalkbutton.h"
#include "guitemplatehelper.h"
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

    friend class GUITemplateHelper<KalkPolinomioDouble,PolinomioDouble>;
public:
    explicit KalkPolinomioDouble(QWidget *parent = 0);
    virtual void setUpLayout(QGridLayout *);
     bool calculate(const PolinomioDouble&, const QString &);

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
    KalkButton *createKalkButton(const QString &text, const char *member);


    PolinomioDouble sumInMemory;
    PolinomioDouble sumSoFar;
    PolinomioDouble factorSoFar;

};

#endif // KALKPOLINOMIODOUBLE_H
