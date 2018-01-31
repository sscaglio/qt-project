#include "abstractkalk.h"

AbstractKalk::AbstractKalk(QWidget *parent) :
    QWidget(parent),pendingAdditiveOperator(QString()),
    pendingMultiplicativeOperator(QString()),waitingForOperand(true)
{}

KalkButton*
AbstractKalk::createKalkButton(const QString &text, const char *member)
{
    KalkButton *button = new KalkButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void
AbstractKalk::setUpDisplay(){
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(30);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

}
