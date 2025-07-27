#include "MyEventFilter.h"
#include <qcoreevent.h>

MyEventFilter::MyEventFilter(QObject *parent) : QObject(parent) {}

bool MyEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    // Фільтруємо події натискання клавіш
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        qDebug() << "Фільтр перехопив натискання клавіші на об'єкті" << watched->objectName()
                 << ": " << keyEvent->text() << " (Key Code: " << keyEvent->key() << ")";

        // Приклад: Блокуємо натискання клавіші 'X' для будь-якого віджета, за яким спостерігаємо
        if (keyEvent->key() == Qt::Key_X) {
            qDebug() << "Заблоковано натискання клавіші 'X' для " << watched->objectName() << "!";
            return true; // Подія оброблена, не передаємо її далі
        }
        // Приклад: Якщо натиснуто Ctrl+S, виводимо повідомлення і блокуємо
        if (keyEvent->key() == Qt::Key_S && (keyEvent->modifiers() & Qt::ControlModifier)) {
            qDebug() << "Глобальна гаряча клавіша Ctrl+S спрацювала для " << watched->objectName() << "!";
            return true; // Блокуємо подальшу обробку
        }
    }
    // Фільтруємо події подвійного кліку миші
    else if (event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        qDebug() << "Фільтр перехопив подвійний клік на об'єкті" << watched->objectName()
                 << " в позиції: (" << mouseEvent->pos().x() << ", " << mouseEvent->pos().y() << ")";
        // Можна, наприклад, відкрити нове вікно або виконати іншу дію
        // return true; // Якщо хочемо повністю перехопити подвійний клік
    }

    // Передаємо подію далі для стандартної обробки, якщо вона не була оброблена фільтром
    return QObject::eventFilter(watched, event);
}
