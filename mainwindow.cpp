// mainwindow.cpp

#include "mainwindow.h"
#include "LCDStopWatch.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  // Set up your main window here
  setWindowTitle("StopWatches");

  // Set layout
  QVBoxLayout* layout = new QVBoxLayout();

  for (size_t i = 0; i < 3; i++)
  {
    LCDStopwatch* stopWatch = new LCDStopwatch(this);
    stopWatches.append(stopWatch);
    layout->addWidget(stopWatch);
  }

  // Set layout in QWidget
  QWidget* window = new QWidget(this);
  window->setLayout(layout);

  // Set QWidget as the central layout of the main window
  setCentralWidget(window);
}

MainWindow::~MainWindow()
{
  // Clean up resources, if any
  for (LCDStopwatch* stopwatch : stopWatches)
  {
    layout()->removeWidget(stopwatch);
    delete stopwatch;
  }
  stopWatches.clear();
}
