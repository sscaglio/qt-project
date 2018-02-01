#include "kalkpolinomiodouble.h"

KalkPolinomioDouble::KalkPolinomioDouble(QWidget *parent) : AbstractKalk(parent)
{
    sumSoFar = PolinomioDouble();
    factorSoFar = PolinomioDouble();
    waitingForOperand = true;

    setUpDisplay();

    QGridLayout *mainLayout = new QGridLayout;
    setUpLayout(mainLayout);

    setWindowTitle(tr("KalkPolinomioDouble"));
}

void
KalkPolinomioDouble::setUpLayout(QGridLayout *mainLayout){

    KalkButton *insertPolynomialKalkButton = createKalkButton(tr("insert Polynomial"),SLOT(insertTypeClicked()));

    KalkButton *backspaceKalkButton = createKalkButton(tr("Canc"), SLOT(backspaceClicked()));
    KalkButton *clearKalkButton = createKalkButton(tr("Canc Operando"), SLOT(clear()));
    KalkButton *clearAllKalkButton = createKalkButton(tr("Reset Kalk"), SLOT(clearAll()));

    KalkButton *timesKalkButton = createKalkButton(tr("*"), SLOT(multiplicativeOperatorClicked()));
    KalkButton *minusKalkButton = createKalkButton(tr("-"), SLOT(additiveOperatorClicked()));
    KalkButton *plusKalkButton = createKalkButton(tr("+"), SLOT(additiveOperatorClicked()));

    KalkButton *squareRootKalkButton = createKalkButton(tr("sqrt"), SLOT(unaryOperatorClicked()));
    KalkButton *equalKalkButton = createKalkButton(tr("="), SLOT(equalClicked()));
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceKalkButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearKalkButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllKalkButton, 1, 4, 1, 2);

    mainLayout->addWidget(insertPolynomialKalkButton,2,0,1,-1);

    mainLayout->addWidget(squareRootKalkButton, 3, 4);
    mainLayout->addWidget(timesKalkButton, 3, 2);
    mainLayout->addWidget(minusKalkButton, 3, 1);
    mainLayout->addWidget(plusKalkButton, 3, 0);


    mainLayout->addWidget(equalKalkButton, 4, 0);
    setLayout(mainLayout);
}

void
KalkPolinomioDouble::insertTypeClicked(){

    QDialog *insertPolynomial = new QDialog(this);
    QLabel * helperText = new QLabel("inserisci polinomio,monomi separati da virgola");
    QLineEdit * line = new QLineEdit(this);
    QRegExp rx("-?\\d{1,4}\\.\\d{1,4}x\\^\\d{1,4}(,-?\\d{1,4}\\.\\d{1,4}x\\^\\d{1,4})*(,-?\\d{1,4}\\.\\d{1,4}){0,1}");
    QValidator *validator = new QRegExpValidator(rx,insertPolynomial);
    line->setValidator(validator);
    line->setPlaceholderText("1.1x^2,1.1x^1,1.1");
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
    GUITemplateHelper<KalkPolinomioDouble,PolinomioDouble>::correctValueInsertedHelper(this,validator,line,insertPolynomial);

}

void KalkPolinomioDouble::unaryOperatorClicked()
{
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    try{
        GUITemplateHelper<KalkPolinomioDouble,PolinomioDouble>::unaryOperatorDoubleHelper(this,clickedOperator);
    }catch(std::exception &e){
        displayErrorMessage(this,e);
    }
}

void KalkPolinomioDouble::additiveOperatorClicked()
{
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkPolinomioDouble,PolinomioDouble>::additiveOperatorHelper(this,clickedOperator);
}

void KalkPolinomioDouble::multiplicativeOperatorClicked()
{

    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkPolinomioDouble,PolinomioDouble>::multiplicativeOperatorHelper(this,clickedOperator);
}

void KalkPolinomioDouble::equalClicked()
{
    GUITemplateHelper<KalkPolinomioDouble,PolinomioDouble>::equalOperatorHelper(this);
}


void KalkPolinomioDouble::backspaceClicked()
{
    waitingForOperand = cleaner::cleanerBackspace(display);
}

void KalkPolinomioDouble::clear()
{
    waitingForOperand = cleaner::cleanerClear(display);
}

void KalkPolinomioDouble::clearAll()
{
    waitingForOperand = cleaner::cleanerCleanAll(display,pendingAdditiveOperator,pendingMultiplicativeOperator);
    sumSoFar = PolinomioDouble();
    factorSoFar = PolinomioDouble();
}

KalkButton* KalkPolinomioDouble::createKalkButton(const QString &text, const char *member)
{
    KalkButton *button = new KalkButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


bool KalkPolinomioDouble::calculate(const PolinomioDouble& rightOperand, const QString &pendingOperator)
{
    try{
        if (pendingOperator == tr("+")) {
            sumSoFar = sumSoFar + rightOperand;
        } else if (pendingOperator == tr("-")) {
            sumSoFar = sumSoFar - rightOperand;
        } else if (pendingOperator == tr("*")) {
            factorSoFar = factorSoFar * rightOperand;
        }
        return true;
    }catch(std::exception &e){
        displayErrorMessage(this,e);
    }
    return false;
}
