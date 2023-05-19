#ifndef DEVICEPOINT_H
#define DEVICEPOINT_H

#include <array>

#include <QWidget>
#include <QLabel>
#include <QPixmap>

//!  Klasa urządzenia jako punktu na mapie
/*!
  Klasa zawierająca informacje o współrzędnych, w których urządzenie się znajduje,
  jego orientacji oraz pixmap determinujący czy pozycja jest aktualna.
*/
class DevicePoint {
public:
    //! Konstruktor klasy
    /*!
      Przy wywołaniu konstruktora przypisywane są współrzędne
      urządzenia oraz pixmap
    */
    DevicePoint(const QPixmap& pixmap, std::array<int, 3> pose);

    //! Metoda pobierająca tablice zawierające informacje o współrzędnych
    //! i orientacji
    /*!
      \return Tablica współrzędnych oraz orientacji
    */
    std::array<int, 3> getPose();

    //! Metoda pobierająca pixmap
    /*!
      \return Pixmap
    */
    const QPixmap& getPixmap();

    //! Metoda ustawiająca tablice współrzędnych
    /*!
      \param newPose tablica liczb całkowitych
    */
    void setPose(std::array<int, 3> newPose);

    //! Metoda ustawiająca pixmap
    /*!
      \param newPixmap stała referencję do obiektu typu QPixmap
    */
    void setPixmap(const QPixmap& newPixmap);

private:
    //! Prywatna zmienna
    /*!
      Zmienna przechowująca obiekt typu QPixmap
    */
    QPixmap pixmap;

    //! Prywatna zmienna
    /*!
      Zmienna przechowująca tablicę liczb całkowitych. Pierwsze dwa pola oznaczają
      współrzędne X i Y, ostatnie pole oznacza orientację urządzenia jako kąt
      odchylenia od osi OX
    */
    std::array<int, 3> pose;
};

#endif // DEVICEPOINT_H
