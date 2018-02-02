#ifndef GUITEMPLATEHELPER
#define GUITEMPLATEHELPER

#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QMessageBox>
#include<QPushButton>
#include<QGridLayout>
#include<QString>
#include<QValidator>


template<typename T,typename U>
class GUITemplateHelper{

public:
    static void unaryOperatorIntHelper(T*,QString);
    static void unaryOperatorDoubleHelper(T*,QString);
    static void additiveOperatorHelper(T*,QString);
    static void multiplicativeOperatorHelper(T*,QString);
    static void equalOperatorHelper(T*);
    static void correctValueInsertedHelper(T*,QValidator*,QLineEdit*,QDialog*);

    static void correctValueInsertedHelperMatrix(T*,QValidator*,QLineEdit*,QDialog*);
    static void unaryOperatorIntHelperMatrix(T*,QString);
    static void unaryOperatorDoubleHelperMatrix(T*,QString);
    static void additiveOperatorHelperMatrix(T*,QString);
    static void multiplicativeOperatorHelperMatrix(T*,QString);
    static void equalOperatorHelperMatrix(T*);

    static void updateMatrixDimensionHelper(T*,unsigned int,unsigned int);
};




template<typename T,typename U>
void
GUITemplateHelper<T,U>::unaryOperatorIntHelper(T * specificGui,
                                               QString passedOperation){
    QString operandoParse = specificGui->display->text();
    U operando = U::parse(operandoParse);

    U res = U();

    if(passedOperation == QString("factorial")){
        res = operando.factorial();
    }

    QString textualRes = U::convertToQString(res);
    specificGui->display->setText(textualRes);
    specificGui->waitingForOperand = true;
}

template<typename T,typename U>
void
GUITemplateHelper<T,U>::unaryOperatorDoubleHelper(T * specificGui,
                                                  QString passedOperation){
    QString operandoParse = specificGui->display->text();
    U operando = U::parse(operandoParse);

    U res = U();

    if(passedOperation == QString("sqrt")){
        res = operando.squareRoot();
    }

    QString textualRes = U::convertToQString(res);
    specificGui->display->setText(textualRes);
    specificGui->waitingForOperand = true;
}

#include<QDebug>

template<typename T,typename U>
void
GUITemplateHelper<T,U>::additiveOperatorHelper(T* specificGui, QString passedOperation){

    qDebug() << "error";
    qDebug() << specificGui->display->text();
    qDebug() << "error";
    U operand = U::parse(specificGui->display->text());

    if (!specificGui->pendingMultiplicativeOperator.isEmpty()) {
        if (!specificGui->calculate(operand,specificGui->pendingMultiplicativeOperator)) {
            return;
        }
        specificGui->display->setText(U::convertToQString(specificGui->factorSoFar));
        operand = specificGui->factorSoFar;
        specificGui->factorSoFar = U();
        specificGui->pendingMultiplicativeOperator.clear();
    }

    if (!specificGui->pendingAdditiveOperator.isEmpty()) {
        if (!specificGui->calculate(operand, specificGui->pendingAdditiveOperator)) {
            return;
        }
        specificGui->display->setText(U::convertToQString(specificGui->sumSoFar));
    } else {
        specificGui->sumSoFar = operand;
    }

    specificGui->pendingAdditiveOperator = passedOperation;
    specificGui->waitingForOperand = true;
}

template<typename T,typename U>
void
GUITemplateHelper<T,U>::multiplicativeOperatorHelper(T * specificGui, QString passedOperand){
    U operand = U::parse(specificGui->display->text());

    if (!specificGui->pendingMultiplicativeOperator.isEmpty()) {
        if (!specificGui->calculate(operand, specificGui->pendingMultiplicativeOperator)) {
            return;
        }
        specificGui->display->setText(U::convertToQString(specificGui->factorSoFar));
    } else {
        specificGui->factorSoFar = operand;
    }

    specificGui->pendingMultiplicativeOperator = passedOperand;
    specificGui->waitingForOperand = true;

}


template<typename T,typename U>
void
GUITemplateHelper<T,U>::equalOperatorHelper(T * specificGui){
    U operand = U::parse(specificGui->display->text());

    if (!specificGui->pendingMultiplicativeOperator.isEmpty()) {
        if (!specificGui->calculate(operand,specificGui->pendingMultiplicativeOperator)) {
            return;
        }
        operand = specificGui->factorSoFar;
        specificGui->factorSoFar = U();
        specificGui->pendingMultiplicativeOperator.clear();
    }
    if (!specificGui->pendingAdditiveOperator.isEmpty()) {
        if (!specificGui->calculate(operand,specificGui->pendingAdditiveOperator)) {
            return;
        }
        specificGui->pendingAdditiveOperator.clear();
    } else {
        specificGui->sumSoFar = operand;
    }

    specificGui->display->setText(U::convertToQString(specificGui->sumSoFar));
    specificGui->sumSoFar = U();
    specificGui->waitingForOperand = true;
}


template<typename T,typename U>
void
GUITemplateHelper<T,U>::correctValueInsertedHelper(T * specificGui, QValidator * validator,QLineEdit *line,QDialog *insertType){

    if(insertType->exec() == QDialog::Accepted){
        QString text = line->text();
        int pos = 0;
        if(validator->validate(text,pos) == QValidator::Acceptable){
            U toDisplay = U::parse(text);
            specificGui->display->setText(U::convertToQString(toDisplay));
            specificGui->waitingForOperand = true;
        }
        else{
            QMessageBox msg(insertType);
            msg.setText("input non valido");
            msg.exec();
        }
    }
}


//operazioni per matrici

template<typename T,typename U>
void
GUITemplateHelper<T,U>::correctValueInsertedHelperMatrix(T * specificGui, QValidator * validator, QLineEdit * line, QDialog *insertType){
    if(insertType->exec() == QDialog::Accepted){
        QString text = line->text();
        int pos = 0;
        if(validator->validate(text,pos) == QValidator::Acceptable){
            U toDisplay = U::parse(text,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);
            specificGui->display->setText(U::convertToQString(toDisplay,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale));
            specificGui->waitingForOperand = true;
        }
        else{
            QMessageBox msg(insertType);
            msg.setText("input non valido");
            msg.exec();
        }
    }
}

template<typename T,typename U>
void
GUITemplateHelper<T,U>::additiveOperatorHelperMatrix(T * specificGui, QString passedOperation){

    U operand = U::parse(specificGui->display->text(),specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);

    if (!(specificGui->pendingMultiplicativeOperator.isEmpty())) {
        if (!(specificGui->calculate(operand,specificGui->pendingMultiplicativeOperator))) {
            return;
        }
        specificGui->display->setText(U::convertToQString(specificGui->factorSoFar,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale));
        operand = specificGui->factorSoFar;
        specificGui->factorSoFar = U(specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);
        specificGui->pendingMultiplicativeOperator.clear();
    }

    if (!(specificGui->pendingAdditiveOperator.isEmpty())) {
        if (!(specificGui->calculate(operand, specificGui->pendingAdditiveOperator))) {
            return;
        }
        specificGui->display->setText(U::convertToQString(specificGui->sumSoFar,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale));
    } else {
        specificGui->sumSoFar = operand;
    }

    specificGui->pendingAdditiveOperator = passedOperation;
    specificGui->waitingForOperand = true;
}


template<typename T,typename U>
void
GUITemplateHelper<T,U>::equalOperatorHelperMatrix(T *specificGui){
    U operand = U::parse(specificGui->display->text(),specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);

    if (!specificGui->pendingMultiplicativeOperator.isEmpty()) {
        if (!specificGui->calculate(operand, specificGui->pendingMultiplicativeOperator)) {
            return;
        }
        operand = specificGui->factorSoFar;
        specificGui->factorSoFar = U(specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);
        specificGui->pendingMultiplicativeOperator.clear();
    }
    if (!specificGui->pendingAdditiveOperator.isEmpty()) {
        if (!specificGui->calculate(operand, specificGui->pendingAdditiveOperator)) {
            return;
        }
        specificGui->pendingAdditiveOperator.clear();
    } else {
        specificGui->sumSoFar = operand;
    }

    specificGui->display->setText(U::convertToQString(specificGui->sumSoFar,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale));
    specificGui->sumSoFar = U(specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);
    specificGui->waitingForOperand = true;

}

template<typename T,typename U>
void
GUITemplateHelper<T,U>::multiplicativeOperatorHelperMatrix(T * specificGui, QString passedOperation){
    U operand = U::parse(specificGui->display->text(),specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);

    if (!specificGui->pendingMultiplicativeOperator.isEmpty()) {
        if (!specificGui->calculate(operand, specificGui->pendingMultiplicativeOperator)) {
            return;
        }
        specificGui->display->setText(U::convertToQString(specificGui->factorSoFar,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale));
    } else {
        specificGui->factorSoFar = operand;
    }

    specificGui->pendingMultiplicativeOperator = passedOperation;
    specificGui->waitingForOperand = true;
}

template<typename T,typename U>
void
GUITemplateHelper<T,U>::unaryOperatorIntHelperMatrix(T * specificGui, QString passedOperation){
    QString operandoMatriceParse = specificGui->display->text();
    U operandoMatrice = U::parse(operandoMatriceParse,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);

    U res = U(specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);

    if(passedOperation == QString("factorial")){
        res = operandoMatrice.factorial();
    }

    QString textualRes = U::convertToQString(res,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);
    specificGui->display->setText(textualRes);
    specificGui->waitingForOperand = true;

}

template<typename T,typename U>
void
GUITemplateHelper<T,U>::unaryOperatorDoubleHelperMatrix(T * specificGui, QString passedOperation){
    QString operandoMatriceParse = specificGui->display->text();
    U operandoMatrice = U::parse(operandoMatriceParse,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);

    U res = U(specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);

    if(passedOperation == QString("sqrt")){
        res = operandoMatrice.squareRoot();
    }

    QString textualRes = U::convertToQString(res,specificGui->righeMatriceAttuale,specificGui->colonneMatriceAttuale);
    specificGui->display->setText(textualRes);
    specificGui->waitingForOperand = true;

}

template<typename T,typename U>
void
GUITemplateHelper<T,U>::updateMatrixDimensionHelper(T *specificGui,unsigned int r,unsigned int c){
    specificGui->clearAll();
    specificGui->sumSoFar = U(r,c);
    specificGui->factorSoFar = U(r,c);
}

#endif // GUITEMPLATEHELPER

