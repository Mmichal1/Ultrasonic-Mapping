#include "../inc/plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::PlotWindow) {
    ui->setupUi(this);

    ui->plotWidget->addGraph();
    ui->plotWidget->graph(0)->setPen(QPen(Qt::blue));
    ui->plotWidget->graph(0)->setName(tr("Sensor 1, -45°"));
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(1)->setPen(QPen(Qt::red));
    ui->plotWidget->graph(1)->setName(tr("Sensor 2, 0°"));
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(2)->setPen(QPen(Qt::green));
    ui->plotWidget->graph(2)->setName(tr("Sensor 3, 45°"));

    ui->plotWidget->yAxis->setRange(0, 200);
    ui->plotWidget->xAxis2->setVisible(true);
    ui->plotWidget->xAxis2->setTickLabels(false);
    ui->plotWidget->yAxis2->setVisible(true);
    ui->plotWidget->yAxis2->setTickLabels(false);
    ui->plotWidget->xAxis->setLabel("t [s]");
    ui->plotWidget->yAxis->setLabel("d [cm]");
    ui->plotWidget->legend->setVisible(true);
    ui->plotWidget->legend->setFont(QFont("Helvetica", 9));
    ui->plotWidget->legend->setSelectableParts(QCPLegend::spItems);

    connect(ui->plotWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->yAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearData()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    ui->plotWidget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);

    ui->closeButton->setText(tr("Close"));
    ui->clearButton->setText(tr("Clear"));
}

PlotWindow::~PlotWindow() {
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
    ui->plotWidget->graph(0)->data()->clear();
    ui->plotWidget->graph(1)->data()->clear();
    ui->plotWidget->graph(2)->data()->clear();
    ui->plotWidget->replot();
}

void PlotWindow::selectionChanged() {
    for (int i=0; i<ui->plotWidget->graphCount(); ++i) {
        QCPGraph *graph = ui->plotWidget->graph(i);
        QCPPlottableLegendItem *item = ui->plotWidget->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected()) {
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }
}

void PlotWindow::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        return;
    }
    QDialog::changeEvent(event);
}
