#ifndef KALKMATRICEINT_H
#define KALKMATRICEINT_H

#include "matriceint.h"

#include "abstractkalk.h"
#include "cleaner.h"
#include "kalkbutton.h"

#include <QWidget>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>

class KalkMatriceInt : public AbstractKalk
{
    Q_OBJECT
public:
    explicit KalkMatriceInt(QWidget *parent = 0,const unsigned int = 2,const unsigned int = 2);
     bool calculate(const MatriceInt&, const QString &);
     virtual void setUpLayout(QGridLayout *);

public slots:
    virtual void insertTypeClicked();
    virtual void unaryOperatorClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void setMatrixDimension();
private:

    unsigned int righeMatriceAttuale;
    unsigned int colonneMatriceAttuale;

    void updateMatrixDimension(unsigned int ,unsigned int);

    MatriceInt sumSoFar;
    MatriceInt factorSoFar;

};


/*
 *
 * #include "abstractkalk.h"
#include "cleaner.h"
#include "kalkbutton.h"

#include <QWidget>
#include<QLineEdit>
#include<QDialog>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>


class KalkComplessoInt : public AbstractKalk
{
    Q_OBJECT
public:
    KalkComplessoInt(QWidget *parent = 0);
    virtual void setUpLayout(QGridLayout *);
public slots:

    virtual void insertComplexClicked();
    virtual void unaryOperatorClicked();
    virtual void additiveOperatorClicked();
    virtual void multiplicativeOperatorClicked();
    virtual void equalClicked();
    virtual void backspaceClicked();
    virtual void clear();
    virtual void clearAll();

private:
    bool calculate(const ComplessoInt&, const QString &);

    ComplessoInt sumInMemory;
    ComplessoInt sumSoFar;
    ComplessoInt factorSoFar;
};
 *
 **/

#endif // KALKMATRICEINT_H
