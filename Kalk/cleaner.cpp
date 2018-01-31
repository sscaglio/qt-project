#include "cleaner.h"

bool
cleaner::cleanerBackspace(QLineEdit * display){
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
    }
    display->setText(text);
    return true;
}

bool
cleaner::cleanerClear(QLineEdit * display){
    display->setText("0");
    return true;
}


bool
cleaner::cleanerCleanAll(QLineEdit * display,QString pendingAdditiveOperator,QString pendingMultiplicativeOperator){
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    return true;
}
