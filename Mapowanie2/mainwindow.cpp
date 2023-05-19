#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    printPoseToLabel();

    changePoseWindow = new ChangePoseWindow(this);

    connect(ui->resetButton, SIGNAL(clicked()), ui->mapWidget,
            SLOT(onResetButtonClicked()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->changePoseButton, SIGNAL(clicked()), this,
            SLOT(onChangePoseButtonClicked()));
    connect(changePoseWindow, SIGNAL(textEntered(QString)), ui->mapWidget,
            SLOT(handleSentString(QString)));
    connect(changePoseWindow, SIGNAL(textEntered(QString)), this,
            SLOT(onButtonClicked()));

    QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::printPoseToLabel() {
    QString variableValue =
        "X: " + QString::number(ui->mapWidget->getDevicePose()[0]) +
        ", Y: " + QString::number(ui->mapWidget->getDevicePose()[1]) + ", " +
        QString::number(ui->mapWidget->getDevicePose()[2]) + QChar(0x00B0);
    ui->poseWidget->setLabelText(variableValue);
}

void MainWindow::onButtonClicked() { printPoseToLabel(); }

void MainWindow::onChangePoseButtonClicked() {
    changePoseWindow->setModal(true);
    changePoseWindow->exec();
}