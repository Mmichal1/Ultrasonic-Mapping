#ifndef POSETEXTEDIT_H
#define POSETEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>
#include <QRegularExpression>

//!  Klasa pola edycji tekstu
/*!
 * Klasa pól tekstowych służącyh do wpisania nowych współrzędnych oraz orientacji urządzenia
 */
class PoseTextEdit : public QTextEdit {
    Q_OBJECT
public:
    //!  Konstruktor klasy
    /*!
     * \param parent Wskaźnik na widget rodzica (domyślnie nullptr).
     */
    explicit PoseTextEdit(QWidget *parent = nullptr);

protected:
    //! Metoda nadpisująca funkcję keyPressEvent
    /*!
     * Za pomocą tej metody określane są znaki akceptowalne przez pole tekstowe oraz
     * długość wpisanego wyrażenia
     *
     * \param event Wskaźnik na obiekt zawierający informację o tym, jakie zdarzenie wystąpiło.
    */
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // POSETEXTEDIT_H
