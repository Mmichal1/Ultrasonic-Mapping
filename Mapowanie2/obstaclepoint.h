#ifndef OBSTACLEPOINT_H
#define OBSTACLEPOINT_H

#include <array>

#include <QWidget>
#include <QLabel>
#include <QPixmap>

//!  Klasa zmapowanego punktu przeszkody
/*!
  Klasa zawierająca informacje o współrzędnych zmapowanego punktu przeszkody
  oraz pixmap determinujący rodzaj punktu (pobrany z aktualnej pozycji urządzenia
  czy z jednej z poprzednich)
*/
class ObstaclePoint{
public:

    //! Konstruktor klasy
    /*!
      Przy wywołaniu konstruktora przypisywane są współrzędne
      punktu oraz pixmap
    */
    ObstaclePoint(const QPixmap& pixmap, std::array<int, 2> position);

    //! Metoda pobierająca tablice zawierające informacje o współrzędnych
    /*!
      \return Tablica współrzędnych
    */
    std::array<int, 2> getPos();

    //! Metoda pobierająca pixmap
    /*!
      \return Pixmap
    */
    const QPixmap& getPixmap();

    //! Metoda ustawiająca pixmap
    /*!
      \param newPixmap stała referencja do obiektu typu QPixmap
    */
    void setPixmap(const QPixmap& newPixmap);

    //! Metoda ustawiająca tablice współrzędnych
    /*!
      \param newPose tablica liczb całkowitych
    */
    void setPos(std::array<int, 2> newPosition);

private:
    //! Prywatna zmienna
    /*!
      Zmienna przechowująca obiekt typu QPixmap
    */
    QPixmap pixmap;

    //! Prywatna zmienna
    /*!
      Zmienna przechowująca tablicę liczb całkowitych. Pierwsze pole oznacza
      współrzędną X a drugie wsp. Y
    */
    std::array<int, 2> position;
};


#endif // OBSTACLEPOINT_H
