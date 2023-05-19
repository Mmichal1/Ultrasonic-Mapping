#include "changeposewindow.h"
#include "ui_changeposewindow.h"

ChangePoseWindow::ChangePoseWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::ChangePoseWindow) {
    ui->setupUi(this);

    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(onOkButtonClicked()));
}

ChangePoseWindow::~ChangePoseWindow() {
    delete ui;
}

void ChangePoseWindow::onOkButtonClicked() {
    QString text = ui->textEditX->toPlainText() + " " +
                ui->textEditY->toPlainText() + " " +
                ui->textEditDeg->toPlainText();

    emit textEntered(text);
    close();
}
