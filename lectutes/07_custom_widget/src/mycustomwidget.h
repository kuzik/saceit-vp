// mycustomwidget.h
#ifndef MYCUSTOMWIDGET_H
#define MYCUSTOMWIDGET_H

#include <QWidget> // Базовий клас для нашого віджета
#include <QPainter> // Для малювання
#include <QMouseEvent> // Для обробки подій миші
#include <QKeyEvent>   // Для обробки подій клавіатури
#include <QDebug>      // Для налагодження

class MyCustomWidget : public QWidget // Успадковуємося від QWidget
{
    Q_OBJECT // Обов'язковий макрос для мета-об'єктної системи Qt

public:
    explicit MyCustomWidget(QWidget *parent = nullptr); // Конструктор

    // Власні властивості віджета (докладніше нижче)
    Q_PROPERTY(QColor widgetColor READ widgetColor WRITE setWidgetColor NOTIFY widgetColorChanged)

    QColor widgetColor() const { return m_widgetColor; }
    void setWidgetColor(const QColor &color);

signals:
    void widgetColorChanged(const QColor &color); // Сигнал про зміну кольору

protected:
    // Перевизначені обробники подій
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    // Перевизначення для підказок розміру
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    QColor m_widgetColor; // Внутрішня змінна для зберігання кольору
    QPoint m_lastMousePos; // Для відстеження позиції миші
};

#endif // MYCUSTOMWIDGET_H
