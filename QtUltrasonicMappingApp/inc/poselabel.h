#ifndef POSELABEL_H
#define POSELABEL_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

//!  Klasa widgetu zawierającego label wyświetlający pozycje urządzenia
/*!
  Klasa wyświetla odpowiednio sformatowany tekst w polu tekstowym
*/
class PoseLabel : public QWidget {
    Q_OBJECT
public:
    //! Konstruktor klasy
    /*!
      W konstruktorze wywoływany jest layout, dodawane jest pole tekstowe do layoutu
    */
    explicit PoseLabel(QWidget *parent = nullptr);

    //! Metoda ustawiająca tekst wyświetlany przez label
    /*!
      \param text stała referenca do obiektu typu QString
    */
    void setLabelText(const QString& text);
private:

    //! Prywatna zmienna
    /*!
      Zmienna przechowująca wskaźnik do obiektu typu label
    */
    QLabel *label;
};

#endif // POSELABEL_H
