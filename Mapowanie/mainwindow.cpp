/**@file mainwindow.h */

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1000, 600);

    buttonConnection = new QPushButton("Connection: ", this);
    buttonConnection->setGeometry(10, 500, 150, 40);

    buttonRetry = new QPushButton("Retry", this);
    buttonRetry->setGeometry(10, 550, 150, 40);

    buttonChangePos = new QPushButton("Change Position", this);
    buttonChangePos->setGeometry(840, 500, 150, 40);

    buttonReset = new QPushButton("Reset", this);
    buttonReset->setGeometry(840, 550, 150, 40);

    connect(buttonChangePos, SIGNAL (clicked()), this, SLOT (whenChangePos()));

    posWindow = new ChangePosWindow;
    posWindow->setWindowTitle("Change Position");

    poseWidget = new PoseWidget(this);

    poseWidget->setGeometry(623, 490, 158, 107);
}

MainWindow::~MainWindow()
{
}

void MainWindow::whenChangePos()
{
    posWindow->show();
}
