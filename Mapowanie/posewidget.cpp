/**@file posewidget.cpp */

#include "posewidget.h"
#include "ui_posewidget.h"

PoseWidget::PoseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PoseWidget)
{
    ui->setupUi(this);
}

PoseWidget::~PoseWidget()
{
    delete ui;
}
