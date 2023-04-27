/**@file changeposwindow.h */

#ifndef CHANGEPOSWINDOW_H
#define CHANGEPOSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "posewidget.h"

/*!
    Klasa okna zmiany pozycji urządzenia
 */
class ChangePosWindow : public QWidget
{
    Q_OBJECT
   public:
    explicit ChangePosWindow(QWidget *parent = nullptr);

   private:
    QPushButton *buttonOk;      /*!< Przycisk Ok */
    QPushButton *buttonCancel;  /*!< Przycisk Cancel */
    QLabel *label;              /*!< Pole tekstowe */
    PoseWidget *poseWidget;
};

#endif // CHANGEPOSWINDOW_H
