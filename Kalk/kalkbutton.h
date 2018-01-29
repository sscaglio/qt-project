#ifndef KALKBUTTON_H
#define KALKBUTTON_H

#include<QToolButton>

class KalkButton : public QToolButton
{
    Q_OBJECT

public:
    explicit KalkButton(const QString &, QWidget * = 0);

    QSize sizeHint() const;
};

#endif // KALKBUTTON_H
