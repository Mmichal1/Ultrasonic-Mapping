#ifndef DEVICEPOINT_H
#define DEVICEPOINT_H

#include <array>

#include <QWidget>
#include <QLabel>
#include <QPixmap>

//!  Klasa urządzenia jako punktu na mapie
/*!
 * Klasa zawierająca informacje o współrzędnych, w których urządzenie się znajduje,
 * jego orientacji oraz pixmap determinujący czy pozycja jest aktualna.
 */
class DevicePoint {
public:
    //! Konstruktor klasy
    /*!
     * Przy wywołaniu konstruktora przypisywane są współrzędne
     * urządzenia oraz pixmap
     *
     * \param pixmap Pixmap zawierający obrazek przedstawiający aktualną lub poprzednią pozycję urządzenia
     * \param pose Tablica zawierająca informacje o współrzędnych i orientacji urządzenia.
     */
    DevicePoint(const QPixmap& pixmap, std::array<int, 3> pose);

    //! Publiczna metoda
    /*!
     * Metoda zwracająca tablicę zawierającą informacje o współrzędnych i orientacji urządzenia
     *
     * \return pose Tablica współrzędnych i orientacji
     */
    std::array<int, 3> getPose();

    //! Publiczna metoda
    /*!
     * Metoda zwracajacą Pixmap zawierający obrazek przedstawiający urządzenie
     *
     * \return pixmap Pixmap zawierający obraze
     */
    const QPixmap& getPixmap();

    //! Publiczna metoda
    /*!
     * Metoda ustawiająca nową pozycję oraz orientację urządzenia
     *
     * \param newPose Tablica liczb całkowitych, które mają zostać przypisane jako nowe współrzędne urządzenia
     */
    void setPose(std::array<int, 3> newPose);

    //! Publiczna metoda
    /*!
     * Metoda ustawiająca nowy Pixmap
     *
     * \param newPixmap Pixmap, który ma zostać przypisany
     */
    void setPixmap(const QPixmap& newPixmap);

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
    std::array<int, 3> pose;
};

#endif // DEVICEPOINT_H
