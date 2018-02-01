#ifndef KALKCOMPLESSODOUBLE_H
#define KALKCOMPLESSODOUBLE_H


#include "abstractkalk.h"
#include "cleaner.h"
#include "kalkbutton.h"
#include "complessodouble.h"
#include "guitemplatehelper.h"

#include <QWidget>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QValidator>
#include<QRegExpValidator>
#include<QPushButton>


class KalkComplessoDouble : public AbstractKalk
{
    friend class GUITemplateHelper<KalkComplessoDouble,ComplessoDouble>;
public:
    KalkComplessoDouble(QWidget *parent = 0);
    virtual void setUpLayout(QGridLayout *);
    bool calculate(const ComplessoDouble&, const QString &);
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


    ComplessoDouble sumInMemory;
    ComplessoDouble sumSoFar;
    ComplessoDouble factorSoFar;
};


#endif // KALKCOMPLESSODOUBLE_H
