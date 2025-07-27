#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyEventFilter.h"
#include <QApplication>

void something () {

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFocusPolicy(Qt::StrongFocus);
    ui->setupUi(this);

    timerWidget = new MyTimerWidget(this);
    ui->verticalLayout->addWidget(timerWidget);

    eventFilter_ = new MyEventFilter(this);
    qApp->installEventFilter(eventFilter_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QString buttonName;
    if (event->button() == Qt::LeftButton) {
        buttonName = "Ліва";
    } else if (event->button() == Qt::RightButton) {
        buttonName = "Права";
    } else {
        buttonName = "Інша";
    }

    ui->label->setText(QString("%1 кнопка натиснута в: (%2, %3) | Глобальні: (%4, %5)")
                             .arg(buttonName)
                             .arg(event->pos().x()).arg(event->pos().y())
                             .arg(event->globalPosition().x()).arg(event->globalPosition().y()));
    qDebug() << "Mouse Press Event: " << ui->label->text();

    // Якщо ми хочемо, щоб подія також поширювалася на батьківський віджет,
    // ми повинні викликати базовий клас або event->ignore().
    // Якщо не хочемо, то event->accept() (за замовчуванням для обробників).
    QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    ui->label->setText(QString("Кнопка миші відпущена в: (%1, %2)").arg(event->pos().x()).arg(event->pos().y()));
    qDebug() << "Mouse Release Event: " << ui->label->text();
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Ця подія буде спрацьовувати лише якщо setMouseTracking(true) або кнопка миші натиснута
    ui->label->setText(QString("Миша переміщена до: (%1, %2)").arg(event->pos().x()).arg(event->pos().y()));
    // qDebug() << "Mouse Move Event: " << statusLabel->text(); // Занадто багато виводу
    QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    ui->label->setText(QString("Подвійний клік Лівою кнопкою в: (%1, %2)").arg(event->pos().x()).arg(event->pos().y()));
    qDebug() << "Mouse Double Click Event: " << ui->label->text();
    QWidget::mouseDoubleClickEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString keyInfo;

    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        keyInfo = "Натиснуто Enter!";
    } else if (event->key() == Qt::Key_Space) {
        keyInfo = "Натиснуто пробіл!";
    } else {
        keyInfo = "Натиснуто клавішу: " + event->text()
            + " (Код клавіші: " + QString::number(event->key()) + ")";
    }

    if (event->modifiers() & Qt::ControlModifier) {
        keyInfo += " + Ctrl";
    }
    if (event->modifiers() & Qt::ShiftModifier) {
        keyInfo += " + Shift";
    }
    if (event->modifiers() & Qt::AltModifier) {
        keyInfo += " + Alt";
    }

    ui->label_2->setText(keyInfo);
    qDebug() << keyInfo;

    QMainWindow::keyPressEvent(event);
}

