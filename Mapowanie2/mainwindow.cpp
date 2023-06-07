#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);


    translator = new QTranslator();

    changePoseWindow = new ChangePoseWindow(this);
    welcomeWindow = new WelcomeDialog(this);
    plotWindow = new PlotWindow(this);
    bar = new QStatusBar(this);
    connectionOkPixmap = new QPixmap(":/connection_ok.svg");
    connectionBadPixmap = new QPixmap(":/connection_bad.svg");
    sensorDataBuffer = new std::array<int, 3>{0, 0, 0};

    QPushButton *clearButton = plotWindow->findChild<QPushButton*>("clearButton");
    QComboBox *languageComboBox = welcomeWindow->findChild<QComboBox*>("languageComboBox");
    stopStartButton = plotWindow->findChild<QPushButton*>("stopStartButton");

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
    connect(ui->refreshButton, SIGNAL(clicked()),
            this, SLOT(onRefreshButtonClicked()));
    connect(ui->graphButton, SIGNAL(clicked()),
            this, SLOT(onGraphButtonClicked()));
    connect(ui->resetButton, SIGNAL(clicked()),
            plotWindow, SLOT(clearData()));
    connect(ui->resetButton, SIGNAL(clicked()),
            this, SLOT(onClearButtonClicked()));
    connect(clearButton, SIGNAL(clicked()),
            this, SLOT(onClearButtonClicked()));
    connect(stopStartButton, SIGNAL(clicked()),
            this, SLOT(onStopStartButtonClicked()));
    connect(languageComboBox, QOverload<const QString&>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::languageSelection);


    QMetaObject::connectSlotsByName(this);

    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    connectToPort(ui->serialComboBox->currentText());
    setWindowTitle(tr("Ultrasonic Mapping"));
    refreshPortList();
    printPoseToLabel();
    bar->setMaximumHeight(17);
    ui->statusBarLayout->addWidget(bar);
    ui->connectionLabel->setPixmap(*connectionBadPixmap);
    stopStartButton->setText("Stop");
    ui->refreshButton->setText(tr("Refresh"));
    ui->connectButton->setText(tr("Connect"));
    ui->currPoseLabel->setText(tr("Current pose:"));
    ui->graphButton->setText(tr("Show Graph"));
    ui->changePoseButton->setText(tr("Change Pose"));

    timeFromStart = 0;
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, this, &MainWindow::timerCallback);
    timer.start();
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

void MainWindow::onGraphButtonClicked() {

    plotWindow->setWindowModality(Qt::NonModal);
    plotWindow->show();
}

void MainWindow::readSerialData() {

    QString string = QString(serial.readAll());

    string.chop(2);

    if (string == "49") {
        bar->showMessage(tr("Connection successful"), 5000);
        ui->connectionLabel->setPixmap(*connectionOkPixmap);
        qDebug() << string;
    }

    if (string == "48") {
        bar->showMessage(tr("Disconnected"), 2000);
        ui->connectionLabel->setPixmap(*connectionBadPixmap);
        qDebug() << string;
    }

    qDebug() << string;
//    QString crcDevice = string.right(4);
    string.chop(4);
//    QByteArray bytes = string.toUtf8();
//    quint16 crcHost = qChecksum(bytes.constData(), bytes.size());
    string.chop(1);
    QStringList list = string.split(" ");

//    if (crcDevice == crcHost) {
//        qDebug("works");
//    }

    if (list.length() == 6) {
        MainWindow::sensorDataBuffer->at(0) = list.at(1).toInt();
        MainWindow::sensorDataBuffer->at(1) = list.at(3).toInt();
        MainWindow::sensorDataBuffer->at(2) = list.at(5).toInt();
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
            ui->connectionLabel->setPixmap(*connectionBadPixmap);
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
            ui->connectionLabel->setPixmap(*connectionBadPixmap);
            QByteArray ba = serial.errorString().toLocal8Bit();
            bar->showMessage(tr(ba.data()), 2000);
        }
    } else {
        QByteArray ba = serial.errorString().toLocal8Bit();
        ui->connectionLabel->setPixmap(*connectionBadPixmap);
        qDebug("Error opening the serial port");
        bar->showMessage(tr(ba.data()), 2000);
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error) {

    if (error == QSerialPort::ResourceError) {
        qDebug("error");
        ui->connectionLabel->setPixmap(*connectionBadPixmap);
    }
}

void MainWindow::refreshPortList() {

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

void MainWindow::onRefreshButtonClicked() {

    sendDataToSerial("0");
}

void MainWindow::performActionOnExit() {

    sendDataToSerial("0");
}

void MainWindow::sendDataToSerial(const QByteArray &message) {

    qint64 bytesWritten = serial.write(message);

    if (bytesWritten == -1) {
        qDebug() << tr("Failed to write to serial port:") << serial.errorString();
        QByteArray ba = serial.errorString().toLocal8Bit();
        bar->showMessage(tr(ba.data()), 2000);
    } else {
        qDebug() << tr("Message sent:") << message;
    }
}

void MainWindow::timerCallback() {
    plotWindow->addPointsToPlot(timeFromStart, sensorDataBuffer->at(0), sensorDataBuffer->at(1), sensorDataBuffer->at(2));
    timeFromStart++;
}

void MainWindow::onClearButtonClicked() {
    timeFromStart = 0;
    sensorDataBuffer->fill(0);
}

void MainWindow::onStopStartButtonClicked() {
    if (stopStartButton->text() == "Stop") {
        stopStartButton->setText("Start");
        timer.stop();
    }
    else {
        stopStartButton->setText("Stop");
        timer.start();
    }
}

void MainWindow::languageSelection(const QString& selectedText) {
    if (selectedText == "PL") {
        qApp->removeTranslator(translator);
        if (translator->load("mapowanie_pl","/home/michal/Desktop/WDS/Mapowanie2/")) {
            qApp->installTranslator(translator);
        }
    } else if (selectedText == "EN") {
        qApp->removeTranslator(translator);
        if (translator->load("mapowanie_en","/home/michal/Desktop/WDS/Mapowanie2/")) {
            qApp->installTranslator(translator);
        }
    }
}

