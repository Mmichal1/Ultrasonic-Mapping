#ifndef MAP_H
#define MAP_H

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
  W tej klasie bazując na widgecie rysowany jest układ współrzędnych.
  Przechowywane są też informację o zmapowanych punktach, aktualnej pozycji
  urządzenia oraz o poprzednich pozycjach urządzenia
*/
class Map : public QWidget {
    Q_OBJECT

public:
    //! Konstruktor klasy
    /*!
      W konstruktorze definiowane są wszystkie obiekty typu QPixmap
    */
    explicit Map(QWidget *parent = nullptr);
    //! Metoda pobierająca tablice zawierające informacje o współrzędnych
    //! i orientacji urządzenia
    /*!
      \return Tablica współrzędnych oraz orientacji
    */
    std::array<int, 3> getDevicePose();

private:
    QPixmap *dev_pos_pixmap;    /*!< Wskaźnik na pixmap aktualnej pozycji obiektu */
    QPixmap *point_pixmap;  /*!< Wskaźnik na pixmap aktualnej pozycji punktu */
    QPixmap *dev_pos_prev_pixmap; /*!< Wskaźnik na pixmap poprzedniej pozycji obiektu */
    QPixmap *point_prev_pixmap; /*!< Wskaźnik na pixmap aktualnej pozycji obiektu */
    DevicePoint *curr_dev_pose; /*!< Wskaźnik na punkt przechowujący dane o urządzeniu */
    std::vector<DevicePoint> prev_dev_pose; /*!< Wektor poprzednich pozycji urządzenia */
    std::vector<ObstaclePoint> curr_points; /*!< Wektor aktualnych pozycji zmapowanych punktów */
    std::vector<ObstaclePoint> prev_points; /*!< Wektor poprzednich pozycji zmapowanych punktów */

    //! Metoda nadpisująca funkcję paintEvent
    /*!
      Za pomocą tej metody rysowany jest układ współrzędnych oraz punkty na mapie
      \param event wskaźnik na obiekt typu QPaintEvent
    */
    void paintEvent(QPaintEvent *event);

    //! Metoda rysująca układ współrzędnych
    /*!
      Za pomocą tej metody rysowany jest układ współrzędnych
      \param painter referencja do obiektu typu QPainter umożliwiającego rysowanie
      \param mapWidth szerokość widgetu w którym rysowana jest mapa
      \param mapHeight wysokość widgetu w którym rysowana jest mapa
    */
    void drawGrid(QPainter& painter, int mapWidth, int mapHeight);

    //! Metoda rysująca punkty
    /*!
      Za pomocą tej metody rysowane są punkty na mapie
      \param painter referencja do obiektu typu QPainter umożliwiającego rysowanie
    */
    void drawPoints(QPainter& painter);

    //! Metoda transformująca współrzędne punktów
    /*!
      Transformacja współrzędnych jest potrzebna aby obiek był rysowany w żądanej pozycji
      \param goalPosition tablica rządanych współrzędnych
      \param pixmapWidth szerokość pixmapy
      \param pixmapWidth wysokość pixmapy
    */
    std::array<int, 2> transormCoordinates(std::array<int, 2> goalPosition, int pixmapWidth, int pixmapHeight);

public slots:
    //! Prywatny slot
    /*!
      Slot reagujący na wciśnięcie przycisku 'Reset'. Po wciśnięciu przycisku wszystkie wektory są czyszczone i tym samym
      usuwane są zmapowane punkty a aktualna pozycja i orientacja urządzenia są ustawiane jako punkt odniesienia
    */
    void onResetButtonClicked();

    //! Prywatny slot
    /*!
      Slot reagujący na wysłany sygnał zawierający referencju do ciągu znaków. Ten ciąg znaków jest przetwarzany
      a odpowiednie wartości, czyli współrzędne oraz orientacja są wyświetlane w polu tekstowym
    */
    void handleSentString(const QString& text);
};

#endif // MAP_H
