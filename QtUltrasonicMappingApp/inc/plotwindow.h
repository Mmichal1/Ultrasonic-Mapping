#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class PlotWindow;
}

//!  Klasa okna dialogowego wyświetlającego wykresy
/*!
 * W tym oknie znajduję się widget, w którym rysowane są wskazania z czujników w czasie rzeczywistym.
 * Do rysowania wykresy użyto klasy QCustomPlot. W oknie znajdują się również przyciski, które
 * zamykają okno, usuwają dane i czyszczą wykres oraz zatrzymują lub restartują timer.
 */
class PlotWindow : public QDialog {
    Q_OBJECT

public:
    //!  Konstruktor
    /*!
     * W konstruktorze załadowywane są instancje obiektów z pliku .ui do obiektu ui.
     * Wywoływane są wszystkie potrzebne metody w celu odpowiedniego skonfigurowania
     * widgetu rysującego wykres.
     *
     * \param parent Wskaźnik na widget rodzica (domyślnie nullptr).
     */
    explicit PlotWindow(QWidget *parent = nullptr);

    //! Destruktor
    ~PlotWindow();

    //! Publiczna metoda
    /*!
     * Za pomocą tej metody dodawane są nowe dane do wykresu
     *
     * \param timeFromStart Czas, jaki upłynął od rozpoczęcia mapowania
     * \param sensorData0 Odczyt z czujnika nr. 0
     * \param sensorData1 Odczyt z czujnika nr. 1
     * \param sensorData2 Odczyt z czujnika nr. 2
     */
    void addPointsToPlot(int timeFromStart, int sensorData0, int sensorData1, int sensorData2);

private:
    //! Prywatny obiekt
    /*!
     * Instacja obiektu Ui.
     */
    Ui::PlotWindow *ui;

    //!  Metoda wirtualna nadpisująca changeEvent
    /*!
     * Za pomocą tej metody tłumaczony jest interfejs użytkownika wtedy, kiedy wykryte zotanie
     * wydarzenie zmiany języka
     *
     * \param event wskaźnik na obiekt zawierający informację o tym jakie zdarzenie wystąpiło.
     */
    virtual void changeEvent(QEvent *event) override;

private slots:
    //! Prywatny slot
    /*!
     * Slot reagujący na zmianę zaznaczenia poszczególnego wykresu poprzez zaznaczenie odpowiadającej
     * pozycji w legendzie i odwrotnie
     */
    void selectionChanged();

public slots:
    //! Publiczny slot
    /*!
     * Wywołanie tego slotu powoduje usunięcie wszystkich danych z wykresu
     */
    void clearData();

};

#endif // PLOTWINDOW_H
