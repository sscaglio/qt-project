#include "kalkcomplessoint.h"

KalkComplessoInt::KalkComplessoInt(QWidget *parent)
    : AbstractKalk(parent)
{
    sumSoFar = ComplessoInt();
    factorSoFar = ComplessoInt();

    setUpDisplay();

    QGridLayout *mainLayout = new QGridLayout;
    setUpLayout(mainLayout);

    setWindowTitle(tr("KalkComplessoInt"));
}

void
KalkComplessoInt::setUpLayout(QGridLayout * mainLayout){

    KalkButton *insertComplexKalkButton = createKalkButton(tr("insert complex"),SLOT(insertTypeClicked()));

    KalkButton *backspaceKalkButton = createKalkButton(tr("Canc"), SLOT(backspaceClicked()));
    KalkButton *clearKalkButton = createKalkButton(tr("Canc Operando"), SLOT(clear()));
    KalkButton *clearAllKalkButton = createKalkButton(tr("Reset Kalk"), SLOT(clearAll()));

    KalkButton *divisionKalkButton = createKalkButton(tr("/"), SLOT(multiplicativeOperatorClicked()));
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

    mainLayout->addWidget(insertComplexKalkButton,2,0,1,-1);

    mainLayout->addWidget(factorialKalkButton, 3, 4);
    mainLayout->addWidget(divisionKalkButton, 3, 3);
    mainLayout->addWidget(timesKalkButton, 3, 2);
    mainLayout->addWidget(minusKalkButton, 3, 1);
    mainLayout->addWidget(plusKalkButton, 3, 0);
    mainLayout->addWidget(equalKalkButton, 4, 0);
    setLayout(mainLayout);
}



void
KalkComplessoInt::insertTypeClicked(){
    QLineEdit * line = new QLineEdit(this);
    QRegExp rx("-?\\d{1,4},-?\\d{0,4}");

    QDialog *insertComplex = new QDialog(this);

    QValidator *validator = new QRegExpValidator(rx,insertComplex);
    line->setValidator(validator);
    line->setPlaceholderText("1,1");


    QPushButton *ok = new QPushButton(insertComplex);
    ok->setText("ok");
    connect(ok,SIGNAL(clicked()),insertComplex,SLOT(accept()));

    QPushButton *cancel = new QPushButton(insertComplex);
    cancel->setText("cancel");
    connect(cancel,SIGNAL(clicked()),insertComplex,SLOT(reject()));
    QLabel * helperText = new QLabel("inserisci complesso, separa reale da immaginaria con virgola, parte immaginaria non richiede carattere i");
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(helperText);
    grid->addWidget(line);
    grid->addWidget(ok);
    grid->addWidget(cancel);
    insertComplex->setLayout(grid);

    GUITemplateHelper<KalkComplessoInt,ComplessoInt>::correctValueInsertedHelper(this,validator,line,insertComplex);


}

void KalkComplessoInt::unaryOperatorClicked()
{
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    try{
        GUITemplateHelper<KalkComplessoInt,ComplessoInt>::unaryOperatorIntHelper(this,clickedOperator);
    }catch(exception & e){
        displayErrorMessage(this,e);
    }
}

void KalkComplessoInt::additiveOperatorClicked()
{
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkComplessoInt,ComplessoInt>::additiveOperatorHelper(this,clickedOperator);
}

void KalkComplessoInt::multiplicativeOperatorClicked()
{
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkComplessoInt,ComplessoInt>::multiplicativeOperatorHelper(this,clickedOperator);
}

void KalkComplessoInt::equalClicked()
{
    if(display->text() == "0"){
        return ;
    }
    GUITemplateHelper<KalkComplessoInt,ComplessoInt>::equalOperatorHelper(this);
}


void KalkComplessoInt::backspaceClicked()
{
    waitingForOperand = cleaner::cleanerBackspace(display);
}

void KalkComplessoInt::clear()
{
    waitingForOperand = cleaner::cleanerClear(display);
}

void KalkComplessoInt::clearAll()
{
    waitingForOperand = cleaner::cleanerCleanAll(display,pendingAdditiveOperator,pendingMultiplicativeOperator);
    sumSoFar = ComplessoInt();
    factorSoFar = ComplessoInt();
}



bool KalkComplessoInt::calculate(const ComplessoInt& rightOperand, const QString &pendingOperator)
{
    try{
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
    }catch(std::exception &e){
        displayErrorMessage(this,e);
    }
    return false;

}
