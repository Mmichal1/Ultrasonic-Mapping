#ifndef MAP_H
#define MAP_H

#include <cmath>
#include <math.h>
#include <vector>
#include <iterator>
#include <array>
#include "obstaclepoint.h"
#include "devicepoint.h"
#include "poselabel.h"

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QCoreApplication>
#include <QStringList>
#include <QTransform>

//!  Klasa widgetu mapy
/*!
 * W tej klasie bazując na widgecie rysowany jest układ współrzędnych.
 * Przechowywane są też informację o zmapowanych punktach, aktualnej pozycji
 * urządzenia oraz o poprzednich pozycjach urządzenia
 */
class Map : public QWidget {
    Q_OBJECT

public:
    //!  Konstruktor klasy
    /*!
     * W konstruktorze definiowane są wszystkie obiekty typu QPixmap
     *
     * \param parent Wskaźnik na widget rodzica (domyślnie nullptr).
     */
    explicit Map(QWidget *parent = nullptr);

    //! Publiczna metoda
    /*!
     * Metoda zwracająca tablicę zawierające informacje o współrzędnych
     * i orientacji urządzenia
     *
     * \return pose Tablica współrzędnych oraz orientacji
     */
    std::array<int, 3> getDevicePose();

private slots:
    //! Prywatny slot
    /*!
     * Slot reagujący na wciśnięcie przycisku 'Reset'. Po wciśnięciu przycisku wszystkie wektory są czyszczone i tym samym
     * usuwane są zmapowane punkty a aktualna pozycja i orientacja urządzenia są ustawiane jako punkt odniesienia
     */
    void onResetButtonClicked();

    //! Prywatny slot
    /*!
     * Slot reagujący na wysłany sygnał zawierający referencju do ciągu znaków. Ten ciąg znaków jest przetwarzany
     * a odpowiednie wartości, czyli współrzędne oraz orientacja są wyświetlane w polu tekstowym
     *
     * \param text Stała referencja do obiektu przechowującego przesyłany tekst
     */
    void handleSentString(const QString& text);

    //! Prywatny slot
    /*!
     * Slot reagujący na wysłany sygnał zawierający referencju do ciągu znaków przechowujące informacje otrzymane
     * z portu szeregowego
     *
     * \param list Stała referencja do obiektu przechowującego listę zawierającą przesyłany teskt podzielony względem spacji.
     */
    void handleSentStringFromSerial(const QStringList& list);

private:
    QPixmap *devPosPixmap;    /*!< Wskaźnik na pixmap aktualnej pozycji obiektu */
    QPixmap *devPosPrevPixmap; /*!< Wskaźnik na pixmap poprzedniej pozycji obiektu */
    QPixmap *pointPixmap;  /*!< Wskaźnik na pixmap aktualnej pozycji punktu */
    QPixmap *pointPrevPixmap; /*!< Wskaźnik na pixmap aktualnej pozycji obiektu */
    DevicePoint *currDevPose; /*!< Wskaźnik na punkt przechowujący dane o urządzeniu */
    std::vector<DevicePoint> prevDevPose; /*!< Wektor poprzednich pozycji urządzenia */
    std::vector<ObstaclePoint> currPoints; /*!< Wektor aktualnych pozycji zmapowanych punktów */
    std::vector<ObstaclePoint> prevPoints; /*!< Wektor poprzednich pozycji zmapowanych punktów */

    //! Prywatna metoda nadpisująca funkcję paintEvent
    /*!
     * Za pomocą tej metody rysowany jest układ współrzędnych oraz punkty na mapie
     *
     * \param event Wskaźnik na obiekt zawierający informację o występującym zdarzeniu
     */
    void paintEvent(QPaintEvent *event) override;

    //! Prywatna metoda
    /*!
     * Za pomocą tej metody rysowany jest układ współrzędnych
     *
     * \param painter Referencja do obiektu typu QPainter umożliwiającego rysowanie
     * \param mapWidth Szerokość widgetu w którym rysowana jest mapa
     * \param mapHeight Wysokość widgetu w którym rysowana jest mapa
     */
    void drawGrid(QPainter& painter, int mapWidth, int mapHeight);

    //! Prywatna metoda
    /*!
     * Za pomocą tej metody rysowane są punkty na mapie
     *
     * \param painter Referencja do obiektu typu QPainter umożliwiającego rysowanie
     */
    void drawPoints(QPainter& painter);

    //! Prywatna metoda
    /*!
     * Za pomocą tej metody rysowany jest obszar jaki obejmują czujniki
     *
     * \param painter Referencja do obiektu typu QPainter umożliwiającego rysowanie
     */
    void drawDetectionArea(QPainter& painter);

    //! Prywatna metoda
    /*!
     * Za pomocą tej metody transformowane są współrzędne.
     * Transformacja współrzędnych jest potrzebna aby obiekt był rysowany w żądanej pozycji.
     * Domyślnie obiekt jest rysowany względem swojego lewego górnego rogu. W celu
     * rysowania go w odpowiedniej pozycji, współrzędne są przesuwane tak,
     * aby środek obiektu znajdował się w rządanym punkcie
     *
     * \param goalPosition Tablica rządanych współrzędnych
     * \param pixmapWidth Szerokość obrazka przechowywanego w obiekcie QPixmap
     * \param pixmapWidth Wysokość obrazka przechowywanego w obiekcie QPixmap
     * \return position Odpowiednio transformowane współrzędne
    */
    std::array<int, 2> transormCoordinates(std::array<int, 2> goalPosition, int pixmapWidth, int pixmapHeight);

    //! Prywatna metoda
    /*!
     * Na podstawie pozycji urządzenia oraz danych otrzymanych poprzez port seryjny, czyli id czujnika a tym samym kąt odchylenia
     * oraz zmierzonej odległości od przeszkody
     *
     * \param data id czujnika oraz zmierzona odległość
     */
    void addPoints(std::array<int, 2> data);
};

#endif // MAP_H
