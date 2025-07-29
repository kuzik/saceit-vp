#include "mycustomwidget.h"
#include <QPainter> // Обов'язково включити для QPainter

MyCustomWidget::MyCustomWidget(QWidget *parent)
    : QWidget(parent), m_widgetColor(Qt::red) // Ініціалізуємо колір
{
    // Встановлюємо політику розміру за замовчуванням
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setMouseTracking(true); // Увімкнути відстеження миші для mouseMoveEvent без натискання
    setFocusPolicy(Qt::StrongFocus); // Дозволити віджету отримувати фокус клавіатури
}

void MyCustomWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // Використовуємо, щоб уникнути попереджень про невикористаний параметр

    QPainter painter(this); // Створюємо об'єкт QPainter для малювання на цьому віджеті
    painter.setRenderHint(QPainter::Antialiasing); // Увімкнути згладжування для кращої якості

    // Малюємо фон віджета
    painter.fillRect(rect(), Qt::lightGray); // Заповнюємо весь віджет світло-сірим кольором

    // Встановлюємо колір пензля (для контуру) та пензля (для заповнення)
    painter.setPen(QPen(Qt::darkBlue, 2)); // Синій контур, товщина 2 пікселі
    painter.setBrush(m_widgetColor); // Заповнення кольором m_widgetColor

    // Малюємо коло (або овал) по центру віджета
    int radius = qMin(width(), height()) / 2 - 10; // Радіус, щоб коло не торкалося країв
    painter.drawEllipse(rect().center(), radius, radius); // Малюємо коло по центру

    // Малюємо текст
    painter.setPen(Qt::black); // Колір тексту - чорний
    painter.drawText(rect(), Qt::AlignCenter, tr("Мій власний віджет")); // Текст по центру
}

void MyCustomWidget::setWidgetColor(const QColor &color)
{
    if (m_widgetColor != color) {
        m_widgetColor = color;
        emit widgetColorChanged(m_widgetColor); // Випромінюємо сигнал про зміну кольору
        update(); // Викликаємо update() для перемальовування віджета
    }
}

void MyCustomWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_lastMousePos = event->pos(); // Зберігаємо позицію для потенційного перетягування
        qDebug() << "Натиснуто ліву кнопку в: " << event->pos();
        // Змінюємо колір при натисканні
        setWidgetColor(QColor(rand() % 256, rand() % 256, rand() % 256));
    }
    QWidget::mousePressEvent(event); // Викликаємо базовий клас для стандартної обробки
}

void MyCustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Якщо ліва кнопка натиснута, можемо реалізувати перетягування
    if (event->buttons() & Qt::LeftButton) {
        // Переміщуємо віджет
        move(pos() + (event->pos() - m_lastMousePos));
        qDebug() << "Віджет переміщено до: " << pos();
    }
    QWidget::mouseMoveEvent(event);
}

void MyCustomWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        qDebug() << "Натиснуто пробіл! Змінюємо колір на випадковий.";
        setWidgetColor(QColor(rand() % 256, rand() % 256, rand() % 256));
    }
    QWidget::keyPressEvent(event);
}

QSize MyCustomWidget::sizeHint() const
{
    // Повертаємо бажаний розмір 200x200 пікселів
    return QSize(200, 200);
}

QSize MyCustomWidget::minimumSizeHint() const
{
    // Повертаємо мінімальний розмір 50x50 пікселів
    return QSize(50, 50);
}
