#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

    // add two new graphs and set their look:
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(2)->setPen(QPen(Qt::green)); // line color red for second graph

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plotWidget->xAxis2->setVisible(true);
    ui->plotWidget->xAxis2->setTickLabels(false);
    ui->plotWidget->yAxis2->setVisible(true);
    ui->plotWidget->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->plotWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:

    // Note: we could have also just called ui->plotWidget->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->plotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::addPointsToPlot(int timeFromStart, int sensorData0, int sensorData1, int sensorData2) {

    ui->plotWidget->graph(0)->addData((double)timeFromStart, (double)sensorData0);
    ui->plotWidget->graph(1)->addData((double)timeFromStart, (double)sensorData1);
    ui->plotWidget->graph(2)->addData((double)timeFromStart, (double)sensorData2);



    if (timeFromStart > 50) {
        ui->plotWidget->graph(0)->rescaleAxes(true);
        ui->plotWidget->graph(1)->rescaleAxes(true);
        ui->plotWidget->graph(2)->rescaleAxes(true);
    } else {
        ui->plotWidget->graph(0)->rescaleValueAxis(true);
        ui->plotWidget->graph(1)->rescaleValueAxis(true);
        ui->plotWidget->graph(2)->rescaleValueAxis(true);
    }

    ui->plotWidget->replot();
}
