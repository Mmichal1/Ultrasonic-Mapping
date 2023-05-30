#include "welcomedialog.h"
#include "ui_welcomedialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog)
{
    ui->setupUi(this);
//    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

WelcomeDialog::~WelcomeDialog()
{
    delete ui;
}
