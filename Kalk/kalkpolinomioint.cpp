#include "kalkpolinomioint.h"

KalkPolinomioInt::KalkPolinomioInt(QWidget *parent) : AbstractKalk(parent)
{
    sumSoFar = PolinomioInt();
    factorSoFar = PolinomioInt();
    waitingForOperand = true;

    setUpDisplay();

    QGridLayout *mainLayout = new QGridLayout;
    setUpLayout(mainLayout);
    setWindowTitle(tr("KalkPolinomioInt"));
}

void
KalkPolinomioInt::setUpLayout(QGridLayout *mainLayout){


    KalkButton *insertPolynomialKalkButton = createKalkButton(tr("insert Polynomial"),SLOT(insertTypeClicked()));

    KalkButton *backspaceKalkButton = createKalkButton(tr("Canc"), SLOT(backspaceClicked()));
    KalkButton *clearKalkButton = createKalkButton(tr("Canc Operando"), SLOT(clear()));
    KalkButton *clearAllKalkButton = createKalkButton(tr("Reset Kalk"), SLOT(clearAll()));

    KalkButton *timesKalkButton = createKalkButton(tr("*"), SLOT(multiplicativeOperatorClicked()));
    KalkButton *minusKalkButton = createKalkButton(tr("-"), SLOT(additiveOperatorClicked()));
    KalkButton *plusKalkButton = createKalkButton(tr("+"), SLOT(additiveOperatorClicked()));

    KalkButton *factorialKalkButton = createKalkButton(tr("factorial"), SLOT(unaryOperatorClicked()));
    KalkButton *equalKalkButton = createKalkButton(tr("="), SLOT(equalClicked()));

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceKalkButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearKalkButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllKalkButton, 1, 4, 1, 2);

    mainLayout->addWidget(insertPolynomialKalkButton,2,0,1,-1);

    mainLayout->addWidget(factorialKalkButton, 3, 4);
    mainLayout->addWidget(timesKalkButton, 3, 2);
    mainLayout->addWidget(minusKalkButton, 3, 1);
    mainLayout->addWidget(plusKalkButton, 3, 0);


    mainLayout->addWidget(equalKalkButton, 4, 0);
    setLayout(mainLayout);

}

void
KalkPolinomioInt::insertTypeClicked(){

    QDialog *insertPolynomial = new QDialog(this);
    QLabel * helperText = new QLabel("inserisci polinomio");
    QLineEdit * line = new QLineEdit(this);
    line->setPlaceholderText("1,1");
    QPushButton *ok = new QPushButton(insertPolynomial);
    ok->setText("ok");
    connect(ok,SIGNAL(clicked()),insertPolynomial,SLOT(accept()));

    QPushButton *cancel = new QPushButton(insertPolynomial);
    cancel->setText("cancel");
    connect(cancel,SIGNAL(clicked()),insertPolynomial,SLOT(reject()));
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(helperText);
    grid->addWidget(line);
    grid->addWidget(ok);
    grid->addWidget(cancel);
    insertPolynomial->setLayout(grid);
    if(insertPolynomial->exec() == QDialog::Accepted){
        QString text = line->text();
        display->setText(text);
        waitingForOperand = true;
    };

}

void KalkPolinomioInt::unaryOperatorClicked()
{
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    QString operandoComplessoParse = display->text();
    PolinomioInt operandoComplesso = PolinomioInt::parse(operandoComplessoParse);

    PolinomioInt res = PolinomioInt();

    if(clickedOperator == tr("factorial")){
        res = operandoComplesso.factorial();
    }

    QString textualRes = PolinomioInt::convertToQString(res);
    display->setText(textualRes);
    waitingForOperand = true;
}

void KalkPolinomioInt::additiveOperatorClicked()
{
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    PolinomioInt operand = PolinomioInt::parse(display->text());

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        display->setText(PolinomioInt::convertToQString(factorSoFar));
        operand = factorSoFar;
        factorSoFar = PolinomioInt();
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            return;
        }
        display->setText(PolinomioInt::convertToQString(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}

void KalkPolinomioInt::multiplicativeOperatorClicked()
{

    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    PolinomioInt operand = PolinomioInt::parse(display->text());

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        display->setText(PolinomioInt::convertToQString(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void KalkPolinomioInt::equalClicked()
{
    PolinomioInt operand = PolinomioInt::parse(display->text());

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        operand = factorSoFar;
        factorSoFar = PolinomioInt();
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(PolinomioInt::convertToQString(sumSoFar));
    sumSoFar = PolinomioInt();
    waitingForOperand = true;
}


void KalkPolinomioInt::backspaceClicked()
{
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void KalkPolinomioInt::clear()
{
    display->setText("0");
    waitingForOperand = true;
}

void KalkPolinomioInt::clearAll()
{
    sumSoFar = PolinomioInt();
    factorSoFar = PolinomioInt();
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

KalkButton* KalkPolinomioInt::createKalkButton(const QString &text, const char *member)
{
    KalkButton *button = new KalkButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


bool KalkPolinomioInt::calculate(const PolinomioInt& rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar = sumSoFar + rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar = sumSoFar - rightOperand;
    } else if (pendingOperator == tr("*")) {
        factorSoFar = factorSoFar * rightOperand;
    }
    return true;
}
