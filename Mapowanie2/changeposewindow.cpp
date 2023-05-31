#include "changeposewindow.h"

#include "ui_changeposewindow.h"

ChangePoseWindow::ChangePoseWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::ChangePoseWindow) {
    ui->setupUi(this);

    connect(ui->buttonCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->buttonOk, SIGNAL(clicked(bool)), this,
            SLOT(onOkButtonClicked()));
    connect(ui->buttonOk, SIGNAL(clicked(bool)), this, SLOT(close()));

    setWindowTitle(tr("Change pose"));

    setTabOrder(ui->textEditX, ui->textEditY);
}

ChangePoseWindow::~ChangePoseWindow() { delete ui; }

void ChangePoseWindow::onOkButtonClicked() {
    QString text = ui->textEditX->toPlainText() + " " +
                   ui->textEditY->toPlainText() + " " +
                   ui->textEditDeg->toPlainText();

    ui->textEditX->clear();
    ui->textEditY->clear();
    ui->textEditDeg->clear();

    emit textEntered(text);
}
