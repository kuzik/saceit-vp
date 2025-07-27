#include "MyTimerWidget.h"

MyTimerWidget::MyTimerWidget(QWidget *parent) : QWidget(parent)
{
    timeLabel = new QLabel("Час: ", this);
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setStyleSheet("font-size: 24px; color: blue;");

    toggleButton = new QPushButton("Зупинити таймер", this);
    timerRunning = true;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(timeLabel);
    layout->addWidget(toggleButton);
    setLayout(layout);

    timer = new QTimer(this); // 'this' встановлює батьківський об'єкт, забезпечуючи автоматичне видалення
    // Підключаємо сигнал timeout() таймера до нашого слота updateTime()
    connect(timer, &QTimer::timeout, this, &MyTimerWidget::updateTime);
    // Підключаємо сигнал натискання кнопки до слота toggleTimer()
    connect(toggleButton, &QPushButton::clicked, this, &MyTimerWidget::toggleTimer);

    // Встановлюємо інтервал таймера на 1000 мс (1 секунда)
    timer->setInterval(1000);
    // Запускаємо таймер
    timer->start();

    // Оновлюємо час одразу при створенні віджета, щоб він не був порожнім
    updateTime();
}

MyTimerWidget::~MyTimerWidget()
{
    // Таймер буде автоматично видалений, оскільки його батьківським об'єктом є MyTimerWidget
    // Якщо б timer не мав батьківського об'єкта, тут потрібно було б: delete timer;
}

void MyTimerWidget::updateTime()
{
    timeLabel->setText("Час: " + QDateTime::currentDateTime().toString("hh:mm:ss"));
}

void MyTimerWidget::toggleTimer()
{
    if (timerRunning) {
        timer->stop();
        toggleButton->setText("Запустити таймер");
        timerRunning = false;
        qDebug() << "Таймер зупинено.";
    } else {
        timer->start();
        toggleButton->setText("Зупинити таймер");
        timerRunning = true;
        qDebug() << "Таймер запущено.";
    }
}
