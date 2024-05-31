#ifndef POSELABEL_H
#define POSELABEL_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

//!  Klasa widgetu zawierającego label wyświetlający pozycje urządzenia
/*!
 * Klasa wyświetla odpowiednio sformatowany tekst w polu tekstowym
 */
class PoseLabel : public QWidget {
    Q_OBJECT
public:
    //!  Konstruktor
    /*!
     * W konstruktorze wywoływane są metody konfigurujące obiekt
     *
     * \param parent Wskaźnik na widget rodzica (domyślnie nullptr).
     */
    explicit PoseLabel(QWidget *parent = nullptr);

    //! Publiczna metoda
    /*!
     * Metoda ustawiająca tekst wyświetlany przez label
      \param text Obiekt zawierający tekst, który ma zostać wyświetlony
    */
    void setLabelText(const QString& text);
private:

    //! Prywatny obiekt
    /*!
     *  Wskaźnik na obiekt, w którym wyświetlana jest aktualna pozycja
     */
    QLabel *label;
};

#endif // POSELABEL_H
