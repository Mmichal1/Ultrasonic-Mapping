#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    changePoseWindow = new ChangePoseWindow(this);

    welcomeWindow = new WelcomeDialog(this);

    bar = new QStatusBar(this);
    bar->setMaximumHeight(17);
    ui->statusBarLayout->addWidget(bar);

    connect(ui->resetButton, SIGNAL(clicked()),
            ui->mapWidget, SLOT(onResetButtonClicked()));
    connect(ui->resetButton, SIGNAL(clicked()),
            this, SLOT(onButtonClicked()));
    connect(ui->changePoseButton, SIGNAL(clicked()),
            this, SLOT(onChangePoseButtonClicked()));
    connect(changePoseWindow, SIGNAL(textEntered(QString)),
            ui->mapWidget, SLOT(handleSentString(QString)));
    connect(changePoseWindow, SIGNAL(textEntered(QString)), this,
            SLOT(onButtonClicked()));
    connect(&serial, &QSerialPort::readyRead,
            this, &MainWindow::readSerialData);
    connect(ui->serialComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::connectToPort);
    connect(&serial, SIGNAL(error(QSerialPort::SerialPortError)),
            this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(ui->refreshButton, SIGNAL(clicked()),
            this, SLOT(refreshPortList()));
    connect(this, SIGNAL(sendStringFromSerial(QString)), ui->mapWidget, SLOT(handleSentStringFromSerial(QString)));

    QMetaObject::connectSlotsByName(this);

    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    refreshPortList();

    connectToPort(ui->serialComboBox->currentText());

    printPoseToLabel();
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

void MainWindow::readSerialData()
{
    QByteArray data = serial.readAll();
    QString string = QString(data);
    string.chop(1);  // Cut last char as it's a new line character
    ui->serialPortLabel->setText(string);
//    qDebug("error");
    emit sendStringFromSerial(string);
}

void MainWindow::connectToPort(const QString &portName)
{
    if (serial.isOpen()) {
        serial.close();
    }

    // Check if the selected port is still available
    bool portExists = false;
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        if (portInfo.portName() == portName) {
            portExists = true;
            break;
        }
    }

    if (portExists) {
        serial.setPortName(portName);
        if (serial.open(QIODevice::ReadOnly)) {
            qDebug("Serial port opened successfully");
            bar->showMessage(tr("Serial port opened successfully"), 2000);
        } else {
            qDebug("Error opening the serial port");
            bar->showMessage(tr("Error opening the serial port"), 2000);
        }
    } else {
        qDebug("Error opening the serial port");
        bar->showMessage(tr("Error opening the serial port"), 2000);
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        qDebug("error");
    }
}

void MainWindow::refreshPortList()
{
    ui->serialComboBox->clear();

    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        ui->serialComboBox->addItem(portInfo.portName());
    }
}

void MainWindow::showWelcomeDialog() {
    welcomeWindow->setModal(true);
    welcomeWindow->exec();
}
