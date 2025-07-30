#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QStyle>

class QTreeView;
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
    QTreeView *treeView = nullptr;
    QStandardItemModel *model = nullptr;

    void populateModel();      // заповнення моделі даними
    void setupViewBehavior();  // налаштування представлення
    QIcon themedIcon(const QString &name, QStyle::StandardPixmap fallback) const; // іконка з резервом
};

#endif // MAINWINDOW_H
