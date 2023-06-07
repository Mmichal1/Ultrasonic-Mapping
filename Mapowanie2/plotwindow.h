#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QDialog {
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

    void addPointsToPlot(int timeFromStart, int sensorData0, int sensorData1, int sensorData2);

private:
    Ui::PlotWindow *ui;

private slots:
    void selectionChanged();

public slots:
    void clearData();

};

#endif // PLOTWINDOW_H
