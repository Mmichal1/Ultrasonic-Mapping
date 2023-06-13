#include "welcomedialog.h"
#include "ui_welcomedialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::WelcomeDialog) {

    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    ui->languageComboBox->addItem("EN");
    ui->languageComboBox->addItem("PL");
}

WelcomeDialog::~WelcomeDialog() {
    delete ui;
}

void WelcomeDialog::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        return;
    }
    QDialog::changeEvent(event);
}
