#ifndef LCDSTOPWATCH_H
#define LCDSTOPWATCH_H

#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

class LCDStopwatch : public QWidget
{
  Q_OBJECT

public:
  explicit LCDStopwatch(QWidget* parent = nullptr);
  ~LCDStopwatch();

protected:
  void mousePressEvent(QMouseEvent* event) override;

private slots:
  void startStopwatch();
  void stopStopwatch();
  void resetStopwatch();
  void updateStopwatch();
  void labelEdited();

private:
  QLCDNumber* lcdHour;
  QLCDNumber* lcdMinute;
  QLCDNumber* lcdSecond;
  QPushButton* startButton;
  QPushButton* stopButton;
  QPushButton* resetButton;
  QLineEdit* lineEdit;
  QLabel* label;
  QTimer* timer;
  qint64 startTime;
  qint64 elapsedTime;
  bool running;
};

#endif // LCDSTOPWATCH_H
