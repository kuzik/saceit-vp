#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator> // Needed for QTranslator (though managed by QApplication)
#include <QEvent> // Required for QEvent in changeEvent declaration

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ukrainianButton_clicked();
    void on_englishButton_clicked();

private:
    Ui::MainWindow *ui; // Pointer to the UI object generated by Qt Designer

    // Removed QTranslator members here.
    // We will manage translators via QApplication::installTranslator.

    void changeLanguage(const QString &languageCode);
    void updateUiTexts(); // Helper function to update texts not in .ui file

protected:
    // Override QWidget's changeEvent to handle language changes
  //  void changeEvent(QEvent *event) override;
};
#endif // MAINWINDOW_H
