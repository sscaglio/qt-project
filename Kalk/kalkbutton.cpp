#include "kalkbutton.h"

KalkButton::KalkButton(const QString& testoBottone,QWidget * parent)
    :QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding ,QSizePolicy::Preferred);
    setText(testoBottone);
}

QSize
KalkButton::sizeHint()const{
    QSize dimBottone = QToolButton::sizeHint();
    dimBottone.rheight() += 30;
    dimBottone.rwidth() = qMax(dimBottone.rheight(),dimBottone.rwidth());
    return dimBottone;
}
