#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTableView;
class QStandardItemModel;
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
    QTableView *tableView = nullptr;
    QStandardItemModel *model = nullptr;

    void populateModel();      // заповнення даними
    void setupViewBehavior();  // налаштування представлення
};

#endif // MAINWINDOW_H
