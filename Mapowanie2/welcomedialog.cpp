#include "welcomedialog.h"
#include "ui_welcomedialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::WelcomeDialog) {

    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    setWindowTitle(tr("Welcome"));
}

WelcomeDialog::~WelcomeDialog() {
    delete ui;
}
