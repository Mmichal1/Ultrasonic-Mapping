#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"
#include "changeposewindow.h"

#include <QUiLoader>
#include <QMainWindow>
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QXmlStreamReader>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onButtonClicked();
    void onChangePoseButtonClicked();

private:
    Ui::MainWindow *ui;
    void printPoseToLabel();
    ChangePoseWindow *changePoseWindow;
};
#endif // MAINWINDOW_H
