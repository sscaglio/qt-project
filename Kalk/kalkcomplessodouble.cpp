#include "kalkcomplessodouble.h"

KalkComplessoDouble::KalkComplessoDouble(QWidget *parent)
    : QWidget(parent)
{
    sumSoFar = ComplessoDouble();
    factorSoFar = ComplessoDouble();
    waitingForOperand = true;

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    KalkButton *insertComplexKalkButton = createKalkButton(tr("insert complex"),SLOT(insertComplexClicked()));

    KalkButton *backspaceKalkButton = createKalkButton(tr("Canc"), SLOT(backspaceClicked()));
    KalkButton *clearKalkButton = createKalkButton(tr("Canc Operando"), SLOT(clear()));
    KalkButton *clearAllKalkButton = createKalkButton(tr("Reset Kalk"), SLOT(clearAll()));

    KalkButton *divisionKalkButton = createKalkButton(tr("/"), SLOT(multiplicativeOperatorClicked()));
    KalkButton *timesKalkButton = createKalkButton(tr("*"), SLOT(multiplicativeOperatorClicked()));
    KalkButton *minusKalkButton = createKalkButton(tr("-"), SLOT(additiveOperatorClicked()));
    KalkButton *plusKalkButton = createKalkButton(tr("+"), SLOT(additiveOperatorClicked()));

    KalkButton *factorialKalkButton = createKalkButton(tr("sqrt"), SLOT(unaryOperatorClicked()));
    KalkButton *equalKalkButton = createKalkButton(tr("="), SLOT(equalClicked()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceKalkButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearKalkButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllKalkButton, 1, 4, 1, 2);

    mainLayout->addWidget(insertComplexKalkButton,2,0,1,-1);

    mainLayout->addWidget(factorialKalkButton, 3, 4);
    mainLayout->addWidget(divisionKalkButton, 3, 3);
    mainLayout->addWidget(timesKalkButton, 3, 2);
    mainLayout->addWidget(minusKalkButton, 3, 1);
    mainLayout->addWidget(plusKalkButton, 3, 0);


    mainLayout->addWidget(equalKalkButton, 4, 0);
    setLayout(mainLayout);

    setWindowTitle(tr("KalkComplessoDouble"));
}


void
KalkComplessoDouble::insertComplexClicked(){

    QDialog *insertComplex = new QDialog(this);
    QLabel * helperText = new QLabel("inserisci complesso");
    QLineEdit * line = new QLineEdit(this);
    line->setPlaceholderText("1,1");
    QPushButton *ok = new QPushButton(insertComplex);
    ok->setText("ok");
    connect(ok,SIGNAL(clicked()),insertComplex,SLOT(accept()));

    QPushButton *cancel = new QPushButton(insertComplex);
    cancel->setText("cancel");
    connect(cancel,SIGNAL(clicked()),insertComplex,SLOT(reject()));
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(helperText);
    grid->addWidget(line);
    grid->addWidget(ok);
    grid->addWidget(cancel);
    insertComplex->setLayout(grid);
    if(insertComplex->exec() == QDialog::Accepted){
        QString text = line->text();
        ComplessoDouble toDisplay = ComplessoDouble::parse(text);
        display->setText(ComplessoDouble::convertToQString(toDisplay));
        waitingForOperand = true;
    };

}

void KalkComplessoDouble::unaryOperatorClicked()
{
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    QString operandoComplessoParse = display->text();
    ComplessoDouble operandoComplesso = ComplessoDouble::parse(operandoComplessoParse);

    ComplessoDouble res = ComplessoDouble();

    if(clickedOperator == tr("sqrt")){
        res = operandoComplesso.squareRoot();
    }

    QString textualRes = ComplessoDouble::convertToQString(res);
    display->setText(textualRes);
    waitingForOperand = true;
}

void KalkComplessoDouble::additiveOperatorClicked()
{
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    ComplessoDouble operand = ComplessoDouble::parse(display->text());

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        display->setText(ComplessoDouble::convertToQString(factorSoFar));
        operand = factorSoFar;
        factorSoFar = ComplessoDouble(0,0);
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            return;
        }
        display->setText(ComplessoDouble::convertToQString(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}

void KalkComplessoDouble::multiplicativeOperatorClicked()
{

    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    ComplessoDouble operand = ComplessoDouble::parse(display->text());

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        display->setText(ComplessoDouble::convertToQString(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void KalkComplessoDouble::equalClicked()
{
    ComplessoDouble operand = ComplessoDouble::parse(display->text());

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        operand = factorSoFar;
        factorSoFar = ComplessoDouble(0,0);
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

    display->setText(ComplessoDouble::convertToQString(sumSoFar));
    sumSoFar = ComplessoDouble(0,0);
    waitingForOperand = true;
}


void KalkComplessoDouble::backspaceClicked()
{
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void KalkComplessoDouble::clear()
{
    display->setText("0");
    waitingForOperand = true;
}

void KalkComplessoDouble::clearAll()
{
    sumSoFar = ComplessoDouble();
    factorSoFar = ComplessoDouble();
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

KalkButton* KalkComplessoDouble::createKalkButton(const QString &text, const char *member)
{
    KalkButton *button = new KalkButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


bool KalkComplessoDouble::calculate(const ComplessoDouble& rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar = sumSoFar + rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar = sumSoFar - rightOperand;
    } else if (pendingOperator == tr("*")) {
        factorSoFar = factorSoFar * rightOperand;
    } else if (pendingOperator == tr("/")) {
        factorSoFar = factorSoFar / rightOperand;
    }
    return true;
}
