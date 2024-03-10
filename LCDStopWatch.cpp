// lcdstopwatch.cpp

#include "LCDStopWatch.h"
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>

LCDStopwatch::LCDStopwatch(QWidget* parent)
  : QWidget(parent)
{
  lcdHour = new QLCDNumber(2, this);
  lcdMinute = new QLCDNumber(2, this);
  lcdSecond = new QLCDNumber(2, this);

  lcdHour->setSegmentStyle(QLCDNumber::Filled);
  lcdMinute->setSegmentStyle(QLCDNumber::Filled);
  lcdSecond->setSegmentStyle(QLCDNumber::Filled);

  lcdHour->setDigitCount(2);
  lcdMinute->setDigitCount(2);
  lcdSecond->setDigitCount(2);

  startButton = new QPushButton("Start", this);
  stopButton = new QPushButton("Stop", this);
  resetButton = new QPushButton("Reset", this);

  connect(startButton, SIGNAL(clicked()), this, SLOT(startStopwatch()));
  connect(stopButton, SIGNAL(clicked()), this, SLOT(stopStopwatch()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(resetStopwatch()));

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateStopwatch()));

  label = new QLabel("Label", this);
  label->setStyleSheet("QLabel { background-color : white; }");
  label->setAutoFillBackground(true);
  label->setAlignment(Qt::AlignCenter);
  label->setMargin(5);
  label->setCursor(Qt::PointingHandCursor);

  lineEdit = new QLineEdit(this);
  lineEdit->setHidden(true);
  lineEdit->setAlignment(Qt::AlignCenter);
  connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(labelEdited()));

  QVBoxLayout* buttonLayout = new QVBoxLayout;
  buttonLayout->addWidget(startButton);
  buttonLayout->addWidget(stopButton);
  buttonLayout->addWidget(resetButton);
  buttonLayout->addStretch();

  QHBoxLayout* lcdLayout = new QHBoxLayout;
  lcdLayout->addWidget(lcdHour);
  lcdLayout->addWidget(lcdMinute);
  lcdLayout->addWidget(lcdSecond);

  QVBoxLayout* labelLayout = new QVBoxLayout;
  labelLayout->addWidget(label);
  labelLayout->addWidget(lineEdit);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addLayout(labelLayout);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addSpacing(20);
  mainLayout->addLayout(lcdLayout);
  mainLayout->setContentsMargins(20, 20, 20, 20);
  setLayout(mainLayout);

  running = false;
  resetStopwatch();
}

LCDStopwatch::~LCDStopwatch()
{
  delete lcdHour;
  delete lcdMinute;
  delete lcdSecond;
  delete startButton;
  delete stopButton;
  delete resetButton;

  delete label;
  delete lineEdit;

  delete timer;
}

void LCDStopwatch::startStopwatch()
{
  if (!running)
  {
    startTime = QDateTime::currentMSecsSinceEpoch() - elapsedTime;
    timer->start(1000);
    running = true;
  }
}

void LCDStopwatch::stopStopwatch()
{
  if (running)
  {
    timer->stop();
    running = false;
    elapsedTime = QDateTime::currentMSecsSinceEpoch() - startTime;
    startButton->setText("Resume");
  }
}

void LCDStopwatch::resetStopwatch()
{
  stopStopwatch();
  elapsedTime = 0;
  lcdHour->display(QString("%1").arg(0, 2, 10, QChar('0')));
  lcdMinute->display(QString("%1").arg(0, 2, 10, QChar('0')));
  lcdSecond->display(QString("%1").arg(0, 2, 10, QChar('0')));
  if (!running)
  {
    startButton->setText("Start");
  }
}

void LCDStopwatch::updateStopwatch()
{
  if (running)
  {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed = currentTime - startTime;
    int hours = elapsed / (1000 * 60 * 60);
    int minutes = (elapsed % (1000 * 60 * 60)) / (1000 * 60);
    int seconds = ((elapsed % (1000 * 60 * 60)) % (1000 * 60)) / 1000;
    lcdHour->display(QString("%1").arg(hours, 2, 10, QChar('0')));
    lcdMinute->display(QString("%1").arg(minutes, 2, 10, QChar('0')));
    lcdSecond->display(QString("%1").arg(seconds, 2, 10, QChar('0')));
  }
}

void LCDStopwatch::labelEdited()
{
  lineEdit->setHidden(true);
  label->setText(lineEdit->text());
  label->setHidden(false);
}
void LCDStopwatch::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
  {
    lineEdit->setText(label->text());
    label->setHidden(true);
    lineEdit->setHidden(false);
    lineEdit->setFocus();
    lineEdit->selectAll();
  }
}
