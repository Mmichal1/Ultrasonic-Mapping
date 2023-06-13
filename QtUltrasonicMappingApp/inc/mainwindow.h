#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "map.h"
#include "changeposewindow.h"
#include "welcomedialog.h"
#include "plotwindow.h"
#include "crc16.h"

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
#include <QSignalMapper>
#include <QByteArray>
#include <QThread>
#include <QTranslator>

#define POLYNOMIAL_9 0x0161

typedef unsigned char byte;

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

    //! Destruktor
    ~MainWindow();

    //! Publiczna metoda
    /*!
      Publiczna metoda wyświetlająca okno powitalne
    */
    void showWelcomeWindow();

public slots:
    //! Publiczny slot
    /*!
      Slot wywoływany podczas zamykania programu
    */
    void performActionOnExit();

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
      Zmienna inkrementowana przy callbacku timera, liczy czas od początku działania lub resetu
    */
    void handleError(QSerialPort::SerialPortError error);

    //! Prywatny slot
    /*!
      Slot, którego wywołanie powoduje odświeżenie listy dostępnych portów szeregowych
    */
    void refreshPortList();

    //! Prywatny slot
    /*!
      Slot, którego wywołanie powoduje wysłanie wiadomości na port seryjny w celu próby połączenia
    */
    void onConnectButtonClicked();

    //! Prywatny slot
    /*!
      Slot reagujący na wciśnięcie przycisku. Po wciśnięciu przycisku
      współrzędne i orientacja urządzenia są wyświetlane w polu tekstowym
    */
    void onButtonClicked();

    //! Prywatny slot
    /*!
      Slot reagujący na wciśnięcie przycisku zmiany pozycji. Po wciśnięciu przycisku
      wyświetlane jest okno dialogowe umożliwiające zmianę pozycji oraz orientację urządzenia.
    */
    void onChangePoseButtonClicked();

    //! Prywatny slot
    /*!
      Slot reagujący na wciśnięcie przycisku wyświetlenia wykresu. Po wciśnięciu przycisku
      wyświetlane jest okno dialogowe w którym rysowany jest wykres wskazań czujników.
    */
    void onGraphButtonClicked();

    //! Prywatny slot
    /*!
      Slot reagujący na wciśnięcie przycisku odświeżenia. Po wciśnięciu przycisku
      zamykany jest port szeregowy i aktualizowana jest lista dostępnych portów
    */
    void onRefreshButtonClicked();
\
    //! Prywatny slot
    /*!
      Slot reagujący na wciśnięcie przycisku wyczyszczenia pobranego z klasy wyświetlającej wykres.
      Po wciśnięciu przycisku resetowany jest timer oraz licznik zliczający czas.
    */
    void onClearButtonClicked();

    //! Prywatny slot
    /*!
      Slot reagujący na wciśnięcie przycisku stop/start pobranego z klasy wyświetlającej wykres.
      Po wciśnięciu przycisku timer jest zatrzymywany lub restartowany.
    */
    void onStopStartButtonClicked();

    //! Prywatny slot
    /*!
      Callback timera wysyłający dane dopisywane do wykresu
    */
    void timerCallback();

    //! Prywatny slot
    /*!
      Slot reagujący na wybór pozycji z listy dostępnych języków. Wybrany język jest załadowywany do translatora
      a następnie do instancji aplikacji. Po wybraniu nowej pozycji translator jest usuwany z aplikacji i proces jest powtarzany
      z nowym językiem
    */
    void languageSelection(const QString& selectedText);

signals:
    //! Sygnał
    /*!
      Sygnały przesyłający wczytane dane z portu szeregowego
    */
    void sendStringFromSerial(const QStringList& message);

private:
    //! Prywatny obiekt
    /*!
      Instacja obiektu Ui.
    */
    Ui::MainWindow *ui;

    //! Prywatny obiekt
    /*!
      Obiekt przechowujący dane o porcie szeregowym
    */
    QSerialPort serial;

    //! Prywatny obiekt
    /*!
      Wskaźnik na obiekt paska stanu
    */
    QStatusBar *bar;

    //! Prywatny obiekt
    /*!
      Wskaźnik na obiekt okna dialogowego zmiany pozycji
    */
    ChangePoseWindow *changePoseWindow;

    //! Prywatny obiekt
    /*!
      Wskaźnik na obiekt okna powitalnego
    */
    WelcomeDialog *welcomeWindow;

    //! Prywatny obiekt
    /*!
      Wskaźnik na obiekt okna wyświetlającego wykres
    */
    PlotWindow *plotWindow;

    //! Prywatny obiekt
    /*!
      Wskaźnik na pixmap wyświetlający rodzaj połączenia
    */
    QPixmap *connectionOkPixmap;

    //! Prywatny obiekt
    /*!
      Wskaźnik na pixmap wyświetlający rodzaj połączenia
    */
    QPixmap *connectionBadPixmap;

    //! Prywatny obiekt
    /*!
      Instacja obiektu timera
    */
    QTimer timer;

    //! Prywatny obiekt
    /*!
      Wskaźnik na obiekt przycisku stop/start w klasie wyświetlającej okno z wykresem
    */
    QPushButton *stopStartButton;

    //! Prywatna zmienna
    /*!
      Zmienna inkrementowana przy callbacku timera, liczy czas od początku działania lub resetu
    */
    int timeFromStart;

    //! Prywatna tablica
    /*!
      Wskaźnik na tablicę przechowujący najnowsze dane otrzymane z czujników
    */
    std::array<int, 3>* sensorDataBuffer;

    CRC16 *crc;

    //! Prywatna metoda
    /*!
      Metoda wyświetlająca współrzędne oraz orientacją w polu tekstowym.
    */
    void printPoseToLabel();

    //! Prywatna metoda
    /*!
      Metoda za pomocą której wysyłana jest wiadomość na port seryjny
    */
    void sendDataToSerial(const QByteArray &message);

    //! Metoda wirtualna nadpisująca changeEvent
    /*!
      Za pomocą tej metody tłumaczony jest interfejs użytkownika wtedy, kiedy wykryte zotanie
      wydarzenie zmiany języka
      \param event wskaźnik na obiekt typu QEvent
    */
    virtual void changeEvent(QEvent *event) override;

    //! Prywatna metoda
    /*!
      Metoda konwertująca obiekt typu QString i zwracająca wskaźnik na bezznakową
      liczbę całkowitą 8-bitową
      \param str wskaźnik na obiekt typu QString
    */
    const uint8_t* convertQStringToUint8(const QString& str);
};
#endif // MAINWINDOW_H
