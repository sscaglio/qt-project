#ifndef GUITEMPLATEHELPER
#define GUITEMPLATEHELPER

#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QGridLayout>
#include<QString>


template<typename T,typename U>
class GUITemplateHelper{

public:
    static void unaryOperatorIntHelper(T*,QString);
    static void unaryOperatorDoubleHelper(T*,QString);
    static void additiveOperatorHelper(T*,QString);
    static void multiplicativeOperatorHelper(T*,QString);
    static void equalOperatorHelper(T*);

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

template<typename T,typename U>
void
GUITemplateHelper<T,U>::additiveOperatorHelper(T* specificGui, QString passedOperation){
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
#endif // GUITEMPLATEHELPER

