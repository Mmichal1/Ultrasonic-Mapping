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
    ui->plotWidget->graph(0)->setName("Sensor 1 at -45°"); // line color blue for first graph
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    ui->plotWidget->graph(1)->setName("Sensor 2 at 0°");
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(2)->setPen(QPen(Qt::green)); // line color red for second graph
    ui->plotWidget->graph(2)->setName("Sensor 3 at 45°");

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->plotWidget->yAxis->setRange(0, 200);
    ui->plotWidget->xAxis2->setVisible(true);
    ui->plotWidget->xAxis2->setTickLabels(false);
    ui->plotWidget->yAxis2->setVisible(true);
    ui->plotWidget->yAxis2->setTickLabels(false);
    ui->plotWidget->xAxis->setLabel("t [s]");
    ui->plotWidget->yAxis->setLabel("d [cm]");
    ui->plotWidget->legend->setVisible(true);
    ui->plotWidget->legend->setFont(QFont("Helvetica", 9));
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->plotWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->yAxis2, SLOT(setRange(QCPRange)));
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearData()));
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

    ui->plotWidget->graph(0)->rescaleAxes(true);
    ui->plotWidget->graph(1)->rescaleAxes(true);
    ui->plotWidget->graph(2)->rescaleAxes(true);

    ui->plotWidget->replot();
}

void PlotWindow::clearData() {
    qDebug("click");
    ui->plotWidget->graph(0)->data()->clear();
    ui->plotWidget->graph(1)->data()->clear();
    ui->plotWidget->graph(2)->data()->clear();
    ui->plotWidget->replot();
}
