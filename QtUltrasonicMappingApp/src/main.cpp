#include "../inc/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

QTranslator translator;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    QObject::connect(&app, &QCoreApplication::aboutToQuit, &mainWindow, &MainWindow::performActionOnExit);

    mainWindow.show();
    mainWindow.showWelcomeWindow();
    return app.exec();
}
