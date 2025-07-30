#include "mainwindow.h"

#include <QListView>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    central(new QWidget(this)),
    layout(new QVBoxLayout(central)),
    listView(new QListView(central)),
    model(new QStringListModel(this)) {

    // Example data
    const QStringList items{
        QStringLiteral("Alpha"),
        QStringLiteral("Bravo"),
        QStringLiteral("Charlie"),
        QStringLiteral("Delta")
    };
    model->setStringList(items);

    listView->setModel(model);
    layout->addWidget(listView);

    central->setLayout(layout);
    setCentralWidget(central);
    setWindowTitle(QStringLiteral("ListView Demo"));
}

MainWindow::~MainWindow() = default;
