#include "kalkmatricedouble.h"

KalkMatriceDouble::KalkMatriceDouble(QWidget *parent,const unsigned int r,const unsigned int c)
    : AbstractKalk(parent)
{
    sumSoFar = MatriceDouble(r,c);
    factorSoFar = MatriceDouble(r,c);

    righeMatriceAttuale = r;
    colonneMatriceAttuale = c;

    waitingForOperand = true;

    setUpDisplay();

    QGridLayout * mainLayout = new QGridLayout;
    setUpLayout(mainLayout);
    setWindowTitle(tr("KalkMatriceDouble"));
}

void
KalkMatriceDouble::setUpLayout(QGridLayout * mainLayout){

    KalkButton *insertComplexKalkButton = createKalkButton(tr("insert matrix"),SLOT(insertTypeClicked()));

    KalkButton *backspaceKalkButton = createKalkButton(tr("Canc"), SLOT(backspaceClicked()));
    KalkButton *clearKalkButton = createKalkButton(tr("Canc Operando"), SLOT(clear()));
    KalkButton *clearAllKalkButton = createKalkButton(tr("Reset Kalk"), SLOT(clearAll()));

    KalkButton *timesKalkButton = createKalkButton(tr("*"), SLOT(multiplicativeOperatorClicked()));
    KalkButton *minusKalkButton = createKalkButton(tr("-"), SLOT(additiveOperatorClicked()));
    KalkButton *plusKalkButton = createKalkButton(tr("+"), SLOT(additiveOperatorClicked()));

    KalkButton *factorialKalkButton = createKalkButton(tr("sqrt"), SLOT(unaryOperatorClicked()));
    KalkButton *equalKalkButton = createKalkButton(tr("="), SLOT(equalClicked()));
    KalkButton *setMatrixDimensionButton = createKalkButton(tr("update dim"),SLOT(setMatrixDimension()));
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
    mainLayout->addWidget(setMatrixDimensionButton,4,1);
    setLayout(mainLayout);
}


void
KalkMatriceDouble::insertTypeClicked(){
    QDialog *insertMatrix = new QDialog(this);
    QLabel * helperText = new QLabel("inserisci matrice, elementi separati da virgola");
    QLineEdit * line = new QLineEdit(this);

    unsigned int eltTotali = righeMatriceAttuale * colonneMatriceAttuale - 1;
    QString regexp = QString(QString("(-?\\d{1,4}\\.\\d{1,4}){1}(,-?\\d{1,4}\\.\\d{1,4})") + QString("{") + QRegExp::escape(QString::number(eltTotali)) + QString("}"));
    QRegExp rx(regexp);
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
    GUITemplateHelper<KalkMatriceDouble,MatriceDouble>::correctValueInsertedHelperMatrix(this,validator,line,insertMatrix);
}

void
KalkMatriceDouble::setMatrixDimension(){
    QDialog *insertMatrixDimension = new QDialog(this);
    QLabel *helperText = new QLabel("inserisci dimensione matrice");
    QLineEdit * line = new QLineEdit(this);
    line->setPlaceholderText("3,3");
    QString rgxp("[1-9],[1-9]");
    QRegExp regexp(rgxp);
    QValidator *validator = new QRegExpValidator(regexp,insertMatrixDimension);
    line->setValidator(validator);
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
    int pos = 0;
    if(insertMatrixDimension->exec() == QDialog::Accepted){
        QString text = line->text();
        if(validator->validate(text,pos) == QValidator::Acceptable){
            QStringList parsedText = text.split(",",QString::SkipEmptyParts);
            clearAll();
            righeMatriceAttuale = parsedText.at(0).toUInt();
            colonneMatriceAttuale = parsedText.at(1).toUInt();
        }
        else{
            QMessageBox msg(insertMatrixDimension);
            msg.setText("input non valido");
            msg.exec();
        }
        waitingForOperand = true;
    }
}

void
KalkMatriceDouble::unaryOperatorClicked(){
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    try{
        GUITemplateHelper<KalkMatriceDouble,MatriceDouble>::unaryOperatorDoubleHelperMatrix(this,clickedOperator);
    }catch(std::exception &e){
        displayErrorMessage(this,e);
    }
}


void
KalkMatriceDouble::additiveOperatorClicked(){
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkMatriceDouble,MatriceDouble>::additiveOperatorHelperMatrix(this,clickedOperator);
}


void
KalkMatriceDouble::multiplicativeOperatorClicked(){
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkMatriceDouble,MatriceDouble>::multiplicativeOperatorHelperMatrix(this,clickedOperator);
}

void
KalkMatriceDouble::equalClicked(){
    GUITemplateHelper<KalkMatriceDouble,MatriceDouble>::equalOperatorHelperMatrix(this);
}

void
KalkMatriceDouble::backspaceClicked(){
    waitingForOperand = cleaner::cleanerBackspace(display);
}

void
KalkMatriceDouble::clear(){
    waitingForOperand = cleaner::cleanerClear(display);
}

void
KalkMatriceDouble::clearAll(){
    waitingForOperand = cleaner::cleanerCleanAll(display,pendingAdditiveOperator,pendingMultiplicativeOperator);
    sumSoFar = MatriceDouble(righeMatriceAttuale,colonneMatriceAttuale);
    factorSoFar = MatriceDouble(righeMatriceAttuale,colonneMatriceAttuale);
}


KalkButton*
KalkMatriceDouble::createKalkButton(const QString &text, const char *member){
    KalkButton *button = new KalkButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

bool
KalkMatriceDouble::calculate(const MatriceDouble & rht, const QString & pendingOperator){
    try{
        if (pendingOperator == tr("+")) {
            sumSoFar = sumSoFar + rht;
        } else if (pendingOperator == tr("-")) {
            sumSoFar = sumSoFar - rht;
        } else if (pendingOperator == tr("*")) {
            factorSoFar = factorSoFar * rht;
        }
        return true;
    }catch(std::exception& e){
        displayErrorMessage(this,e);
    }
    return false;
}

void
KalkMatriceDouble::updateMatrixDimension(unsigned int r, unsigned int c){
    GUITemplateHelper<KalkMatriceDouble,MatriceDouble>::updateMatrixDimensionHelper(this,r,c);
}
