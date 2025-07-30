#include "mainwindow.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    central(new QWidget(this)),
    layout(new QVBoxLayout(central)),
    tableView(new QTableView(central)),
    model(new QStandardItemModel(0, 3, this)) // 0 рядків, 3 стовпці
{
    // Заголовки стовпців
    model->setHeaderData(0, Qt::Horizontal, tr("Ім'я"));
    model->setHeaderData(1, Qt::Horizontal, tr("Вік"));
    model->setHeaderData(2, Qt::Horizontal, tr("Місто"));

    populateModel();
    tableView->setModel(model);
    setupViewBehavior();

    layout->addWidget(tableView);
    central->setLayout(layout);
    setCentralWidget(central);

    setWindowTitle(tr("QTableView Демонстрація"));
}

MainWindow::~MainWindow() = default;

void MainWindow::populateModel() {
    // Додаємо дані (приклад)
    QList<QStandardItem*> row1;
    row1 << new QStandardItem(QStringLiteral("Іван"))
         << new QStandardItem(QStringLiteral("30"))
         << new QStandardItem(QStringLiteral("Київ"));
    model->appendRow(row1);

    QList<QStandardItem*> row2;
    row2 << new QStandardItem(QStringLiteral("Марія"))
         << new QStandardItem(QStringLiteral("25"))
         << new QStandardItem(QStringLiteral("Львів"));
    model->appendRow(row2);

    QList<QStandardItem*> row3;
    row3 << new QStandardItem(QStringLiteral("Петро"))
         << new QStandardItem(QStringLiteral("40"))
         << new QStandardItem(QStringLiteral("Одеса"));
    model->appendRow(row3);

    QList<QStandardItem*> row4;
    row4 << new QStandardItem(QStringLiteral("Олена"))
         << new QStandardItem(QStringLiteral("35"))
         << new QStandardItem(QStringLiteral("Харків"));
    model->appendRow(row4);
}

void MainWindow::setupViewBehavior() {
    tableView->setSortingEnabled(true);                                  // сортування по заголовку
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked);         // редагування по дабл-кліку
    tableView->setAlternatingRowColors(true);                             // чергування кольорів
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);       // виділення рядками
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);      // одиночний вибір

// Розтягування/розміри стовпців
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);
#else
    tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);
#endif

    tableView->verticalHeader()->setVisible(false);                       // приховати номери рядків
    tableView->resizeColumnsToContents();                                 // підлаштувати ширину
}
