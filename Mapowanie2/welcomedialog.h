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
    //!
    Ui::WelcomeDialog *ui;

};

#endif // WELCOMEDIALOG_H
