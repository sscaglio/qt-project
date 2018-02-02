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

    KalkButton *factorialKalkButton = createKalkButton(tr("factorial"), SLOT(unaryOperatorClicked()));
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
KalkMatriceInt::insertTypeClicked(){
    QDialog *insertMatrix = new QDialog(this);
    QLabel * helperText = new QLabel("inserisci matrice, valori elementi matrice separati da virgola");
    QLineEdit * line = new QLineEdit(this);

    unsigned int eltTotali = righeMatriceAttuale * colonneMatriceAttuale - 1;
    QString regexp = QString(QString("(-?\\d{1,4}){1}(,-?\\d{1,4})") + QString("{") + QRegExp::escape(QString::number(eltTotali)) + QString("}"));
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
    GUITemplateHelper<KalkMatriceInt,MatriceInt>::correctValueInsertedHelperMatrix(this,validator,line,insertMatrix);
}

void
KalkMatriceInt::setMatrixDimension(){
    QDialog *insertMatrixDimension = new QDialog(this);
    QLabel *helperText = new QLabel("inserisci dimensione matrice");
    QLabel * dimAttuali = new QLabel("dim attuali:" + QString::number(righeMatriceAttuale) + "x" + QString::number(colonneMatriceAttuale));
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
    grid->addWidget(dimAttuali);
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
    };
}

void
KalkMatriceInt::unaryOperatorClicked(){
    if(display->text() == "0"){
        return ;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    try{
        GUITemplateHelper<KalkMatriceInt,MatriceInt>::unaryOperatorIntHelperMatrix(this,clickedOperator);
    }
    catch(std::exception &e){
        displayErrorMessage(this,e);
    }
}


void
KalkMatriceInt::additiveOperatorClicked(){
    if(display->text() == "0"){
        return;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkMatriceInt,MatriceInt>::additiveOperatorHelperMatrix(this,clickedOperator);
}


void
KalkMatriceInt::multiplicativeOperatorClicked(){
    if(display->text() == "0"){
        return;
    }
    KalkButton *clickedButton = qobject_cast<KalkButton *>(sender());
    QString clickedOperator = clickedButton->text();
    GUITemplateHelper<KalkMatriceInt,MatriceInt>::multiplicativeOperatorHelperMatrix(this,clickedOperator);
}

void
KalkMatriceInt::equalClicked(){
    if(display->text() == "0"){
        return;
    }
    GUITemplateHelper<KalkMatriceInt,MatriceInt>::equalOperatorHelperMatrix(this);
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
    try{
        if (pendingOperator == tr("+")) {
            sumSoFar = sumSoFar + rht;
        } else if (pendingOperator == tr("-")) {
            sumSoFar = sumSoFar - rht;
        } else if (pendingOperator == tr("*")) {
            factorSoFar = factorSoFar * rht;
        }
        return true;
    }catch(std::exception &e){
        displayErrorMessage(this,e);
    }
    return false;
}

void
KalkMatriceInt::updateMatrixDimension(unsigned int r, unsigned int c){
  GUITemplateHelper<KalkMatriceInt,MatriceInt>::updateMatrixDimensionHelper(this,r,c);
}
