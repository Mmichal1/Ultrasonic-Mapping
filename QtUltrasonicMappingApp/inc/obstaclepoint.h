#ifndef OBSTACLEPOINT_H
#define OBSTACLEPOINT_H

#include <array>

#include <QWidget>
#include <QLabel>
#include <QPixmap>

//!  Klasa zmapowanego punktu przeszkody
/*!
 * Klasa zawierająca informacje o współrzędnych zmapowanego punktu przeszkody
 * oraz pixmap determinujący rodzaj punktu (pobrany z aktualnej pozycji urządzenia
 * czy z jednej z poprzednich)
 */
class ObstaclePoint{
public:

    //! Konstruktor klasy
    /*!
     * Przy wywołaniu konstruktora przypisywane są współrzędne
     * urządzenia oraz pixmap
     *
     * \param pixmap Pixmap zawierający obrazek przedstawiający aktualną lub poprzednią pozycję zmapowanego punktu.
     * \param position Tablica zawierająca informacje o współrzędnych puntku urządzenia.
     */
    ObstaclePoint(const QPixmap& pixmap, std::array<int, 2> position);

    //! Publiczna metoda
    /*!
     * Metoda zwracająca tablicę zawierającą informacje o współrzędnych
     *
     * \return position Tablica współrzędnych punktu
    */
    std::array<int, 2> getPos();

    //! Publiczna metoda
    /*!
     * Metoda zwracająca Pixmap zawierający obrazek przedstawiający zmapowany punkt
     *
     * \return pixmap Pixmap zawierający obraze
     */
    const QPixmap& getPixmap();

    //! Publiczna metoda
    /*!
     * Metoda ustawiająca nowy Pixmap
     *
     * \param newPixmap Pixmap, który ma zostać przypisany
     */
    void setPixmap(const QPixmap& newPixmap);

    //! Publiczna metoda
    /*!
     * Metoda ustawiająca nową pozycję
     *
     * \param newPosition Tablica liczb całkowitych, które mają zostać przypisane
     * jako nowe współrzędne punktu
     */
    void setPos(std::array<int, 2> newPosition);

private:
    //! Prywatny obiekt
    /*!
     * Instancja obiektu typu QPixmap. Przechowuje obrazek przedstawiający aktualną
     * lub poprzednią pozycję urządzenia
     */
    QPixmap pixmap;

    //! Prywatna tablica
    /*!
     * Tablica przechowująca tablicę liczb całkowitych. Pierwsze dwa pola oznaczają
     * współrzędne X i Y, ostatnie pole oznacza orientację urządzenia jako kąt
     * odchylenia od osi OX
     */
    std::array<int, 2> position;
};


#endif // OBSTACLEPOINT_H
