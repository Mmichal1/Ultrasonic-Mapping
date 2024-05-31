    #ifndef CHANGEPOSEWINDOW_H
#define CHANGEPOSEWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QTextEdit>

namespace Ui {
class ChangePoseWindow;
}

//!  Klasa okna dialogowego zmiany pozycji urządzenia.
/*!
 *  Okno dialogowe posiada trzy pola edycji tekstu, w które użytkownik
 *  wpisuje nowe współrzędne oraz kąt obrotu urządzenia.
 */
class ChangePoseWindow : public QDialog {
    Q_OBJECT

public:
    //!  Konstruktor
    /*!
     * W konstruktorze załadowywane są instancje obiektów z pliku .ui do obiektu ui.
     * Łączone są wysyłane sygnały z przycisków ze slotami
     *
     * \param parent Wskaźnik na widget rodzica (domyślnie nullptr).
     */
    explicit ChangePoseWindow(QWidget *parent = nullptr);

    //! Destruktor
    ~ChangePoseWindow();

private:
    //! Prywatny obiekt
    /*!
     * Instacja obiektu Ui.
     */
    Ui::ChangePoseWindow *ui;

    //!  Metoda wirtualna nadpisująca changeEvent
    /*!
     * Za pomocą tej metody tłumaczony jest interfejs użytkownika wtedy, kiedy wykryte zotanie
     * wydarzenie zmiany języka
     *
     * \param event Wskaźnik na obiekt zawierający informację o tym, jakie zdarzenie wystąpiło.
     */
    virtual void changeEvent(QEvent *event) override;


private slots:
    //! Prywatny slot
    /*!
      Slot reagujący na wciśnięcie przycisku 'Ok'. Po wciśnięciu sczytywane są wartości
      wpisane w pola edycji tekstu, wartości te łączone zą sobą w jeden ciąg znaków
      oraz emitowany jest sygnał przesyłający ciąg znaków.
    */
    void onOkButtonClicked();

signals:
    //! Sygnał
    /*!
      Sygnał wysyłający ciąg znaków sczytanych z pól tekstowych.
    */
    void textEntered(const QString& text);
};

#endif // CHANGEPOSEWINDOW_H
