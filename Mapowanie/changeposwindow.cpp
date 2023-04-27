/**@file changeposwindow.cpp */

#include "changeposwindow.h"

ChangePosWindow::ChangePosWindow(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(400, 450);

    buttonCancel = new QPushButton("Cancel", this);
    buttonCancel->setGeometry(10, 400, 150, 40);

    buttonOk = new QPushButton("Ok", this);
    buttonOk->setGeometry(240, 400, 150, 40);
    buttonOk->setEnabled(false);

    poseWidget = new PoseWidget(this);
    poseWidget->setGeometry(100, 200, 160, 110);

    label = new QLabel("Enter new pose:", this);
    label->setGeometry(100, 100, 160, 110);

    connect(buttonCancel, SIGNAL (clicked(bool)), this, SLOT (close()));
}
