#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void resetView();

private:
    QGraphicsScene *scene = nullptr;
    QGraphicsView  *view  = nullptr;
    QPushButton    *resetButton = nullptr;

    void setupScene();
    void setupView();
    void addGrid(double step = 20.0);
};

#endif // MAINWINDOW_H
