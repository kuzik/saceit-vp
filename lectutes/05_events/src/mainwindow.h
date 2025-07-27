#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include "MyTimerWidget.h"
#include "MyEventFilter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    MyTimerWidget *timerWidget;

    MyEventFilter *eventFilter_ = nullptr;   // 🔹 поле фільтра
};
#endif // MAINWINDOW_H
