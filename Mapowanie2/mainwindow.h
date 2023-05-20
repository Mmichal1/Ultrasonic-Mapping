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
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QStatusBar>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//!  Klasa głównego okna
/*!
  W oknie głównym wyświetlane są wszystkie dostępne widget i przyciski
*/
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    //! Konstruktor klasy
    /*!
      W konstruktorze definiowane są potrzebne obiekty oraz łączene są wszystkie potrzebne sygnały
      ze slotami.
    */
    MainWindow(QWidget *parent = nullptr);
    //! Domyślny destruktor
    ~MainWindow();

public slots:
    //! Publiczny slot
    /*!
      Slot reagujący na wciśnięcie przycisku. Po wciśnięciu przycisku
      współrzędne i orientacja urządzenia są wyświetlane w polu tekstowym
    */
    void onButtonClicked();

    //! Publiczny slot
    /*!
      Slot reagujący na wciśnięcie przycisku 'Change Pose'. Po wciśnięciu przycisku
      wyświetlane jest okno dialogowe umożliwiające zmianę pozycji oraz orientację urządzenia.
    */
    void onChangePoseButtonClicked();

private slots:
    //! Prywatny slot
    /*!
      Slot reagujący próbę połączenia z wybranym portem szeregowym
      \param portName stała referencja do obiektu typu QString, przechowuje nazwę wybranego portu szeregowego
    */
    void connectToPort(const QString &portName);

    //! Prywatny slot
    /*!
      Slot, którego wywołanie powoduje wczytanie danych z portu szeregowego
    */
    void readSerialData();

    //! Prywatny slot
    /*!
      Slot obsługujący błąd związany z otwarciem portu szeregowego lub utratą połączenia
      \param error występujący błąd
    */
    void handleError(QSerialPort::SerialPortError error);

    //! Prywatny slot
    /*!
      Slot, którego wywołanie powoduje odświeżenie listy dostępnych portów szeregowych
    */
    void refreshPortList();

signals:
    //! Sygnał
    /*!
      Sygnały przesyłający wczytane dane z portu szeregowego
    */
    void sendStringFromSerial(const QString& message);

private:
    //! Prywatny obiekt
    /*!
      Instacja obiektu Ui.
    */
    //!
    Ui::MainWindow *ui;

    //! Prywatna metoda
    /*!
      Metoda wyświetlająca współrzędne oraz orientacją w polu tekstowym.
    */
    void printPoseToLabel();

    //! Prywatny obiekt
    /*!
      Wskaźnik na obiekt okna dialogowego zmiany pozycji
    */
    //!
    ChangePoseWindow *changePoseWindow;

    //! Prywatny obiekt
    /*!
      Obiekt przechowujący dane o porcie szeregowym
    */
    //!
    QSerialPort serial;

    //! Prywatny obiekt
    /*!
      Wskaźnik na obiekt paska stanu
    */
    //!
    QStatusBar *bar;
};
#endif // MAINWINDOW_H
