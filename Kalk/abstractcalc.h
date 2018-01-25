#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H

#include <QWidget>

class AbstractCalc : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractCalc(QWidget *parent = 0);

    virtual void setupSpecificOperation() = 0;

signals:

public slots:
};

#endif // ABSTRACTCALC_H
