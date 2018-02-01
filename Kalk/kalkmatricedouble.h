#ifndef KALKMATRICEDOUBLE_H
#define KALKMATRICEDOUBLE_H

#include "kalkbutton.h"
#include "matricedouble.h"
#include "abstractkalk.h"

#include <QWidget>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

class KalkMatriceDouble : public AbstractKalk
{
    Q_OBJECT
public:
    explicit KalkMatriceDouble(QWidget *parent = 0,const unsigned int = 2,const unsigned int = 2);
    virtual void setUpLayout(QGridLayout *);

public slots:
    void insertTypeClicked();
    void unaryOperatorClicked();
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

    KalkButton *createKalkButton(const QString &text, const char *member);
    bool calculate(const MatriceDouble&, const QString &);

    void updateMatrixDimension(unsigned int ,unsigned int);
    MatriceDouble sumSoFar;
    MatriceDouble factorSoFar;

};

#endif // KALKMATRICEDOUBLE_H
