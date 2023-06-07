#include "mainwindow.h"

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

void changeTranslation(const QString& translationFile)
{
    // Remove the previously installed translator
    qApp->removeTranslator(&translator);

    // Load and install the new translation file
    translator.load(translationFile);
    qApp->installTranslator(&translator);
}
