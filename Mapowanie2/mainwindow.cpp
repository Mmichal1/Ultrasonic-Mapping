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
    connect(this, SIGNAL(sendStringFromSerial(QStringList)),
            ui->mapWidget, SLOT(handleSentStringFromSerial(QStringList)));
    connect(ui->connectButton, SIGNAL(clicked()),
            this, SLOT(onConnectButtonClicked()));

    QMetaObject::connectSlotsByName(this);

    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    refreshPortList();

    connectToPort(ui->serialComboBox->currentText());

    printPoseToLabel();

//    timer.setSingleShot(true);  // Only fires once
//    timer.setInterval(5000);
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
    //    qDebug("host");
    //    qDebug() << crcHost;

    //    if (crcDevice == crcHost) {

    //        qDebug("works");
    //    }

    //    qDebug("error");

    QByteArray data = serial.readAll();
    QString string = QString(data);

    if (string == "49\r\n") {
        bar->showMessage(tr("Connection successfull"), 2000);
        qDebug() << string;
    }


    string.chop(1);  // Cut last char as it's a new line character
    ui->serialPortLabel->setText(string);

    QStringList list = string.split(" ");
//    QString crcDevice = list.last();
//    quint16 crcDevice = list.last().toUShort();
    list.removeLast();
//    quint16 crcHost = qChecksum(list.join("").toUtf8().constData(), 10);

    qDebug("device");
    qDebug() << list.length();

    if (list.length() == 6) {
        emit sendStringFromSerial(list);
    }
}

void MainWindow::connectToPort(const QString &portName) {

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
        if (serial.open(QIODevice::ReadWrite)) {
            qDebug("Serial port opened successfully");
            bar->showMessage(tr("Serial port opened successfully"), 2000);
        } else {
            qDebug("Error opening the serial port");
            QByteArray ba = serial.errorString().toLocal8Bit();
            bar->showMessage(tr(ba.data()), 2000);
        }
    } else {
        QByteArray ba = serial.errorString().toLocal8Bit();
        qDebug("Error opening the serial port");
        bar->showMessage(tr(ba.data()), 2000);
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error) {

    if (error == QSerialPort::ResourceError) {
        qDebug("error");
    }
}

void MainWindow::refreshPortList() {

    sendDataToSerial("0");
    ui->serialComboBox->clear();


    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        ui->serialComboBox->addItem(portInfo.portName());
    }
}

void MainWindow::showWelcomeWindow() {

    welcomeWindow->setModal(true);
    welcomeWindow->exec();
}

void MainWindow::onConnectButtonClicked() {

    sendDataToSerial("1");
}

void MainWindow::performActionOnExit() {

    qDebug() << "Performing action on application exit...";
    sendDataToSerial("0");
}

void MainWindow::sendDataToSerial(const QByteArray &message) {

    qint64 bytesWritten = serial.write(message);

    if (bytesWritten == -1) {
        qDebug() << "Failed to write to serial port:" << serial.errorString();
        QByteArray ba = serial.errorString().toLocal8Bit();
        bar->showMessage(tr(ba.data()), 2000);
    } else {
        qDebug() << "Message sent:" << message;
    }
}

