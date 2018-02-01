#ifndef CLEANER_H
#define CLEANER_H

#include<QLineEdit>
#include<QString>

class cleaner
{
public:
    static bool cleanerBackspace(QLineEdit *);
    static bool cleanerClear(QLineEdit *);
    static bool cleanerCleanAll(QLineEdit *,QString&,QString&);
};

#endif // CLEANER_H
