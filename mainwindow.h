// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <LCDStopWatch.h>
#include <QList>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  QList<LCDStopwatch*> stopWatches;
};

#endif // MAINWINDOW_H
