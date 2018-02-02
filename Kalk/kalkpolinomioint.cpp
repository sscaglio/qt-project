#include "kalkpolinomioint.h"

KalkPolinomioInt::KalkPolinomioInt(QWidget *parent) : AbstractKalk(parent)
{
    sumSoFar = PolinomioInt();
    factorSoFar = PolinomioInt();
    waitingForOperand = true;

    connect(this,SIGNAL(reducePolinomial()),this,SLOT(reduceAll()));
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
    QLabel * helperText = new QLabel("inserisci polinomio, monomi separati da virgola");
    QLineEdit * line = new QLineEdit(this);
    QRegExp rx("-?\\d{1,4}x\\^\\d{1,4}(,-?\\d{0,4}x\\^\\d{1,4})*(,-?\\d{1,4}){0,1}");
    QValidator *validator = new QRegExpValidator(rx,insertPolynomial);
    line->setValidator(validator);
    line->setPlaceholderText("1x^2,1x^1,1");
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
    GUITemplateHelper<KalkPolinomioInt,PolinomioInt>::correctValueInsertedHelper(this,validator,line,insertPolynomial);
    emit reducePolinomial();
}

void KalkPolinomioInt::unaryOperatorClicked()
{
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    try{
        GUITemplateHelper<KalkPolinomioInt,PolinomioInt>::unaryOperatorIntHelper(this,clickedOperator);
        emit reducePolinomial();
    }catch(std::exception &e){
        displayErrorMessage(this,e);
    }
}

void KalkPolinomioInt::additiveOperatorClicked()
{
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkPolinomioInt,PolinomioInt>::additiveOperatorHelper(this,clickedOperator);
}

void KalkPolinomioInt::multiplicativeOperatorClicked()
{

    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkPolinomioInt,PolinomioInt>::multiplicativeOperatorHelper(this,clickedOperator);
}

void KalkPolinomioInt::equalClicked()
{
    GUITemplateHelper<KalkPolinomioInt,PolinomioInt>::equalOperatorHelper(this);
    emit reducePolinomial();
}


void KalkPolinomioInt::backspaceClicked()
{
    waitingForOperand = cleaner::cleanerBackspace(display);
}

void KalkPolinomioInt::clear()
{
    waitingForOperand = cleaner::cleanerClear(display);
}

void KalkPolinomioInt::clearAll()
{
    waitingForOperand = cleaner::cleanerCleanAll(display,pendingAdditiveOperator,pendingMultiplicativeOperator);
    sumSoFar = PolinomioInt();
    factorSoFar = PolinomioInt();

}

KalkButton* KalkPolinomioInt::createKalkButton(const QString &text, const char *member)
{
    KalkButton *button = new KalkButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


bool KalkPolinomioInt::calculate(const PolinomioInt& rightOperand, const QString &pendingOperator)
{
    try{
        if (pendingOperator == tr("+")) {
            sumSoFar = sumSoFar + rightOperand;
        } else if (pendingOperator == tr("-")) {
            sumSoFar = sumSoFar - rightOperand;
        } else if (pendingOperator == tr("*")) {
            factorSoFar = factorSoFar * rightOperand;
        }
        emit reducePolinomial();
        return true;
    }
    catch(std::exception &e){
        displayErrorMessage(this,e);
    }
    return false;
}

void
KalkPolinomioInt::reduceAll(){
    try{
        if(!sumSoFar.polinomioNullo()){
            PolynomialArithmeticExecutor<PolinomioInt,int>::reduxEqual(sumSoFar);
        }
        if(!factorSoFar.polinomioNullo()){
            PolynomialArithmeticExecutor<PolinomioInt,int>::reduxEqual(factorSoFar);
        }
        if(display->text() != "0"){
            PolinomioInt par =PolinomioInt::parse(display->text());
            PolynomialArithmeticExecutor<PolinomioInt,int>::reduxEqual(par);
            QString Poltext = PolinomioInt::convertToQString(par);
            display->setText(Poltext);
        }
    }catch(std::exception &e){
        displayErrorMessage(this,e);
    }
}
