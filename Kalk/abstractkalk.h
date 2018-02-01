#ifndef ABSTRACTKALK_H
#define ABSTRACTKALK_H

#include "kalkbutton.h"

#include<QGridLayout>
#include <QLineEdit>
#include<QString>
#include <QWidget>
#include<QMessageBox>

class AbstractKalk : public QWidget
{
    Q_OBJECT

protected:

    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QLineEdit *display;

public:
    explicit AbstractKalk(QWidget *parent = 0);
    KalkButton *createKalkButton(const QString &text, const char *member);
    virtual void setUpDisplay();
    virtual void setUpLayout(QGridLayout *) = 0;
public slots:

   virtual void insertTypeClicked() = 0;
   virtual void unaryOperatorClicked() = 0;
   virtual void additiveOperatorClicked() = 0;
   virtual void multiplicativeOperatorClicked() = 0;
   virtual void equalClicked() = 0;
   virtual void backspaceClicked() = 0;
   virtual void clear() = 0;
   virtual void clearAll() = 0;

};

#endif // ABSTRACTKALK_H
