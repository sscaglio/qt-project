#ifndef KALKMATRICEINT_H
#define KALKMATRICEINT_H

#include "matriceint.h"

#include "abstractkalk.h"
#include "cleaner.h"
#include "kalkbutton.h"
#include "guitemplatehelper.h"

#include <QWidget>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QRegExpValidator>
#include<QValidator>
#include<QPushButton>

class KalkMatriceInt : public AbstractKalk
{
    Q_OBJECT

    friend class GUITemplateHelper<KalkMatriceInt,MatriceInt>;
public:
    explicit KalkMatriceInt(QWidget *parent = 0,const unsigned int = 2,const unsigned int = 2);
     bool calculate(const MatriceInt&, const QString &);
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
    virtual void setMatrixDimension();
private:

    unsigned int righeMatriceAttuale;
    unsigned int colonneMatriceAttuale;

    void updateMatrixDimension(unsigned int ,unsigned int);

    MatriceInt sumSoFar;
    MatriceInt factorSoFar;

signals:
    void changeDimension();
};


#endif // KALKMATRICEINT_H
