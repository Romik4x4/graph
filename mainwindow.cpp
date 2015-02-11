#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include "qcustomplot.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setGeometry(400, 250, 542, 390);
  
  setupDemo(0);


}

void MainWindow::setupDemo(int demoIndex)
{
  switch (demoIndex)
  {
    case 0:  setupQuadraticDemo(ui->customPlot); break;


  }
  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();
  currentDemoIndex = demoIndex;
  ui->customPlot->replot();
}

void MainWindow::setupQuadraticDemo(QCustomPlot *customPlot)
{


  customPlot->addGraph();

  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(100); // Interval 0 means to refresh as fast as possible

}



void MainWindow::realtimeDataSlot()
{
  // calculate two new data points:

    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    // static double lastPointKey = 0;

  // if (key-lastPointKey > 0.01) // at most add point every 10 ms
  //  {

    QVector<double> x(101), y(101); // initialize with entries 0..100

    for (int i=0; i<101; ++i)
    {
      x[i] = i; // x goes from -1 to 1
      y[i] = rand() % 20+1;  // let's plot a quadratic function
    }

    // add data to lines:
    ui->customPlot->graph(0)->addData(x,y);

    // set data of dots:

    // remove data of lines that's outside visible range:
    // ui->customPlot->graph(0)->removeDataBefore(key-8);

    // rescale value (vertical) axis to fit the current data:
    ui->customPlot->graph(0)->rescaleValueAxis();

    // }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(1,20);
    ui->customPlot->replot();

}
