#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>

namespace Ui {
class WelcomeDialog;
}

//!  Klasa okna powitalnego
/*!
 *  Okno powitalne wyświetlane jest zawsze po uruchomieniu aplikacji. Z poziomu
 *  tego okna możliwa jest zmiana języka.
 */
class WelcomeDialog : public QDialog {
    Q_OBJECT

public:
    //!  Konstruktor
    /*!
     * W konstruktorze załadowywane są instancje obiektów z pliku .ui do obiektu ui.
     * Wywoływane są potrzebne metody
     *
     * \param parent Wskaźnik na widget rodzica (domyślnie nullptr).
     */
    explicit WelcomeDialog(QWidget *parent = nullptr);

    //! Destruktor klasy
    ~WelcomeDialog();

private:
    //! Prywatny obiekt
    /*!
     * Instacja obiektu Ui.
     */
    Ui::WelcomeDialog *ui;

    //!  Metoda wirtualna nadpisująca changeEvent
    /*!
     * Za pomocą tej metody tłumaczony jest interfejs użytkownika wtedy, kiedy wykryte zotanie
     * wydarzenie zmiany języka
     *
     * \param event Wskaźnik na obiekt zawierający informację o tym, jakie zdarzenie wystąpiło.
     */
    virtual void changeEvent(QEvent *event) override;
};

#endif // WELCOMEDIALOG_H
