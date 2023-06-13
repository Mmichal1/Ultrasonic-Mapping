#ifndef POSETEXTEDIT_H
#define POSETEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>
#include <QRegularExpression>

//!  Klasa pola edycji tekstu
/*!
  Klasa pól tekstowych służącyh do wpisania nowych współrzędnych oraz orientacji urządzenia
*/
class PoseTextEdit : public QTextEdit {
    Q_OBJECT
public:
    //! Konstruktor klasy
    explicit PoseTextEdit(QWidget *parent = nullptr);

protected:
    //! Metoda nadpisująca funkcję keyPressEvent
    /*!
      Za pomocą tej metody określane są znaki akceptowalne przez pole tekstowe oraz
      długość wpisanego wyrażenia
      \param event wskaźnik na obiekt typu QKeyEvent
    */
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // POSETEXTEDIT_H
