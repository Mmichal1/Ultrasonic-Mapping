#include "mainwindow.h"
#include "changeposewindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    ChangePoseWindow w;
//    w.setWindowTitle("Change Pose");
    w.show();
    return a.exec();
}
