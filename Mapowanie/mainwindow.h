/**@file mainwindow.cpp */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "changeposwindow.h"
#include "posewidget.h"

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>


/*!
    Klasa okna głównego
 */
class MainWindow : public QMainWindow
{
   Q_OBJECT
   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   public slots:
    void whenChangePos();           /*!< Sygnal wysyłany w celu otwarcia nowego okna */
   private:
    QPushButton *buttonConnection; /*!< Przycisk wyświetlający stan połączenia */
    QPushButton *buttonRetry;      /*!< Przycisk ponownego połączenia */
    QPushButton *buttonChangePos;  /*!< Przycisk otwierający okno zmiany pozycji */
    QPushButton *buttonReset;      /*!< Przycisk czyszczący okno wizualizacji i ustawiający pozycji domyślną */
    PoseWidget *poseWidget;

    ChangePosWindow *posWindow;


};
#endif // MAINWINDOW_H
