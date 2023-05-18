#ifndef RESETBUTTON_H
#define RESETBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ResetButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ResetButton(QWidget *parent = nullptr);

private:

signals:

};

#endif // RESETBUTTON_H
