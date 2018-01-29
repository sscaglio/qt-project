#ifndef KALKMATRICEINT_H
#define KALKMATRICEINT_H

#include "kalkbutton.h"
#include "matriceint.h"

#include <QWidget>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

class KalkMatriceInt : public QWidget
{
    Q_OBJECT
public:
    explicit KalkMatriceInt(QWidget *parent = 0,const unsigned int = 2,const unsigned int = 2);

signals:

private slots:
    void insertMatrixClicked();
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
    bool calculate(const MatriceInt&, const QString &);

    void updateMatrixDimension(unsigned int ,unsigned int);
    MatriceInt sumSoFar;
    MatriceInt factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;

};

#endif // KALKMATRICEINT_H
