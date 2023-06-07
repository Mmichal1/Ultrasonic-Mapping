#include "welcomedialog.h"
#include "ui_welcomedialog.h"

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::WelcomeDialog) {

    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    setWindowTitle(tr("Welcome"));
    ui->label->setText(tr("Welcome"));
    ui->languageLabel->setText(tr("Choose language"));
    ui->languageComboBox->addItem("PL");
    ui->languageComboBox->addItem("EN");
}

WelcomeDialog::~WelcomeDialog() {
    delete ui;
}
