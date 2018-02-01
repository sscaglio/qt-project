#include "kalkmatriceint.h"

KalkMatriceInt::KalkMatriceInt(QWidget *parent,const unsigned int r,const unsigned int c) :
    AbstractKalk(parent)
{
    sumSoFar = MatriceInt(r,c);
    factorSoFar = MatriceInt(r,c);

    righeMatriceAttuale = r;
    colonneMatriceAttuale = c;

    setUpDisplay();

    QGridLayout *mainLayout = new QGridLayout;
    setUpLayout(mainLayout);

    setWindowTitle(tr("KalkMatriceInt"));
}

void
KalkMatriceInt::setUpLayout(QGridLayout * mainLayout){
    KalkButton *insertComplexKalkButton = createKalkButton(tr("insert matrix"),SLOT(insertTypeClicked()));

    KalkButton *backspaceKalkButton = createKalkButton(tr("Canc"), SLOT(backspaceClicked()));
    KalkButton *clearKalkButton = createKalkButton(tr("Canc Operando"), SLOT(clear()));
    KalkButton *clearAllKalkButton = createKalkButton(tr("Reset Kalk"), SLOT(clearAll()));

    KalkButton *timesKalkButton = createKalkButton(tr("*"), SLOT(multiplicativeOperatorClicked()));
    KalkButton *minusKalkButton = createKalkButton(tr("-"), SLOT(additiveOperatorClicked()));
    KalkButton *plusKalkButton = createKalkButton(tr("+"), SLOT(additiveOperatorClicked()));

    KalkButton *factorialKalkButton = createKalkButton(tr("sqrt"), SLOT(unaryOperatorClicked()));
    KalkButton *equalKalkButton = createKalkButton(tr("="), SLOT(equalClicked()));

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceKalkButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearKalkButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllKalkButton, 1, 4, 1, 2);

    mainLayout->addWidget(insertComplexKalkButton,2,0,1,-1);

    mainLayout->addWidget(factorialKalkButton, 3, 4);
    mainLayout->addWidget(timesKalkButton, 3, 2);
    mainLayout->addWidget(minusKalkButton, 3, 1);
    mainLayout->addWidget(plusKalkButton, 3, 0);
    mainLayout->addWidget(equalKalkButton, 4, 0);
    setLayout(mainLayout);
}

void
KalkMatriceInt::insertTypeClicked(){
    QDialog *insertMatrix = new QDialog(this);
    QLabel * helperText = new QLabel("inserisci matrice");
    QLineEdit * line = new QLineEdit(this);

    QRegExp rx("(-?\\d{1,4})(,\\d{1,4})*");
    QValidator *validator = new QRegExpValidator(rx,insertMatrix);
    line->setValidator(validator);

    line->setPlaceholderText("1,1");
    QPushButton *ok = new QPushButton(insertMatrix);
    ok->setText("ok");
    connect(ok,SIGNAL(clicked()),insertMatrix,SLOT(accept()));

    QPushButton *cancel = new QPushButton(insertMatrix);
    cancel->setText("cancel");
    connect(cancel,SIGNAL(clicked()),insertMatrix,SLOT(reject()));
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(helperText);
    grid->addWidget(line);
    grid->addWidget(ok);
    grid->addWidget(cancel);
    insertMatrix->setLayout(grid);
    if(insertMatrix->exec() == QDialog::Accepted){
        QString text = line->text();
        if(text.isEmpty()){
            return;
        }
        display->setText(text);
        waitingForOperand = true;
    };
}

void
KalkMatriceInt::setMatrixDimension(){
    QDialog *insertMatrixDimension = new QDialog(this);
    QLabel *helperText = new QLabel("inserisci dimensione matrice");
    QLineEdit * line = new QLineEdit(this);
    line->setPlaceholderText("3,3");
    QPushButton *ok = new QPushButton(insertMatrixDimension);
    ok->setText("ok");
    connect(ok,SIGNAL(clicked()),insertMatrixDimension,SLOT(accept()));

    QPushButton *cancel = new QPushButton(insertMatrixDimension);
    cancel->setText("cancel");
    connect(cancel,SIGNAL(clicked()),insertMatrixDimension,SLOT(reject()));
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(helperText);
    grid->addWidget(line);
    grid->addWidget(ok);
    grid->addWidget(cancel);
    insertMatrixDimension->setLayout(grid);
    if(insertMatrixDimension->exec() == QDialog::Accepted){
        QString text = line->text();
        QStringList parsedText = text.split(",",QString::SkipEmptyParts);
        clearAll();
        righeMatriceAttuale = parsedText.at(0).toUInt();
        colonneMatriceAttuale = parsedText.at(1).toUInt();
        waitingForOperand = true;
    };
}

void
KalkMatriceInt::unaryOperatorClicked(){
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    QString operandoMatriceParse = display->text();
    MatriceInt operandoMatrice = MatriceInt::parse(operandoMatriceParse,righeMatriceAttuale,colonneMatriceAttuale);

    MatriceInt res = MatriceInt(righeMatriceAttuale,colonneMatriceAttuale);

    if(clickedOperator == tr("factorial")){
        res = operandoMatrice.factorial();
    }

    QString textualRes = MatriceInt::convertToQString(res,righeMatriceAttuale,colonneMatriceAttuale);
    display->setText(textualRes);
    waitingForOperand = true;

}


void
KalkMatriceInt::additiveOperatorClicked(){
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    MatriceInt operand = MatriceInt::parse(display->text(),righeMatriceAttuale,colonneMatriceAttuale);

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        display->setText(MatriceInt::convertToQString(factorSoFar,righeMatriceAttuale,colonneMatriceAttuale));
        operand = factorSoFar;
        factorSoFar = MatriceInt(righeMatriceAttuale,colonneMatriceAttuale);
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            return;
        }
        display->setText(MatriceInt::convertToQString(sumSoFar,righeMatriceAttuale,colonneMatriceAttuale));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}


void
KalkMatriceInt::multiplicativeOperatorClicked(){
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    MatriceInt operand = MatriceInt::parse(display->text(),righeMatriceAttuale,colonneMatriceAttuale);

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        display->setText(MatriceInt::convertToQString(factorSoFar,righeMatriceAttuale,colonneMatriceAttuale));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void
KalkMatriceInt::equalClicked(){
    MatriceInt operand = MatriceInt::parse(display->text(),righeMatriceAttuale,colonneMatriceAttuale);

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            return;
        }
        operand = factorSoFar;
        factorSoFar = MatriceInt(righeMatriceAttuale,colonneMatriceAttuale);
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

    display->setText(MatriceInt::convertToQString(sumSoFar,righeMatriceAttuale,colonneMatriceAttuale));
    sumSoFar = MatriceInt(righeMatriceAttuale,colonneMatriceAttuale);
    waitingForOperand = true;
}

void
KalkMatriceInt::backspaceClicked(){
  waitingForOperand = cleaner::cleanerBackspace(display);
}

void
KalkMatriceInt::clear(){
    waitingForOperand = cleaner::cleanerClear(display);
}

void
KalkMatriceInt::clearAll(){

    waitingForOperand = cleaner::cleanerCleanAll(display,pendingAdditiveOperator,pendingMultiplicativeOperator);
    sumSoFar = MatriceInt(righeMatriceAttuale,colonneMatriceAttuale);
    factorSoFar = MatriceInt(righeMatriceAttuale,colonneMatriceAttuale);
}


bool
KalkMatriceInt::calculate(const MatriceInt & rht, const QString & pendingOperator){
    if (pendingOperator == tr("+")) {
        sumSoFar = sumSoFar + rht;
    } else if (pendingOperator == tr("-")) {
        sumSoFar = sumSoFar - rht;
    } else if (pendingOperator == tr("*")) {
        factorSoFar = factorSoFar * rht;
    }
    return true;
}

void
KalkMatriceInt::updateMatrixDimension(unsigned int r, unsigned int c){
    clearAll();
    sumSoFar = MatriceInt(r,c);
    factorSoFar = MatriceInt(r,c);
}
