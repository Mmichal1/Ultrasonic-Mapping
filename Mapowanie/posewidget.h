/**@file posewidget.h */

#ifndef POSEWIDGET_H
#define POSEWIDGET_H

#include <QWidget>

namespace Ui {
class PoseWidget;
}


/*!
    Klasa widgetu wyświetlającego pozycję oraz orientację
 */
class PoseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PoseWidget(QWidget *parent = nullptr);
    ~PoseWidget();

private:
    Ui::PoseWidget *ui;
};

#endif // POSEWIDGET_H
