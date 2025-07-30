#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListView;
class QStringListModel;
class QWidget;
class QVBoxLayout;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget *central = nullptr;
    QVBoxLayout *layout = nullptr;
    QListView *listView = nullptr;
    QStringListModel *model = nullptr;
};

#endif // MAINWINDOW_H
