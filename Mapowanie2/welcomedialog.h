#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class WelcomeDialog;
}

class WelcomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeDialog(QWidget *parent = nullptr);
    ~WelcomeDialog();

private:
    Ui::WelcomeDialog *ui;

};

#endif // WELCOMEDIALOG_H
