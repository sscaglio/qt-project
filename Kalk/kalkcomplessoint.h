#ifndef KALKCOMPLESSOINT_H
#define KALKCOMPLESSOINT_H

#include "abstractkalk.h"
#include "cleaner.h"
#include "kalkbutton.h"
#include "complessoint.h"
#include "guitemplatehelper.h"

#include <QWidget>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QRegExpValidator>
#include<QValidator>
#include<QPushButton>


class KalkComplessoInt : public AbstractKalk
{
    Q_OBJECT

    friend class GUITemplateHelper<KalkComplessoInt,ComplessoInt>;
public:
    KalkComplessoInt(QWidget *parent = 0);
    virtual void setUpLayout(QGridLayout *);
    bool calculate(const ComplessoInt&, const QString &);
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


    ComplessoInt sumSoFar;
    ComplessoInt factorSoFar;
};

#endif // KALKCOMPLESSOINT_H
