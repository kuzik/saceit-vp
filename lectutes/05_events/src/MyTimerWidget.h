#ifndef MYTIMERWIDGET_H
#define MYTIMERWIDGET_H

// MyTimerWidget.h
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QDateTime>
#include <QPushButton>

class MyTimerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyTimerWidget(QWidget *parent = nullptr);
    ~MyTimerWidget(); // Деструктор для очищення

private slots:
    void updateTime();
    void toggleTimer();

private:
    QLabel *timeLabel;
    QTimer *timer;
    QPushButton *toggleButton;
    bool timerRunning;
};
#endif
