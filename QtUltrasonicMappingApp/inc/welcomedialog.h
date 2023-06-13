#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>

namespace Ui {
class WelcomeDialog;
}

//!  Klasa okna powitalnego
class WelcomeDialog : public QDialog {
    Q_OBJECT

public:
    //! Konstruktor klasy
    explicit WelcomeDialog(QWidget *parent = nullptr);

    //! Destruktor klasy
    ~WelcomeDialog();

private:
    //! Prywatny obiekt
    /*!
      Instacja obiektu Ui.
    */
    Ui::WelcomeDialog *ui;

    //! Metoda wirtualna nadpisująca changeEvent
    /*!
      Za pomocą tej metody tłumaczony jest interfejs użytkownika wtedy, kiedy wykryte zotanie
      wydarzenie zmiany języka
      \param event wskaźnik na obiekt typu QEvent
    */
    virtual void changeEvent(QEvent *event) override;
};

#endif // WELCOMEDIALOG_H
