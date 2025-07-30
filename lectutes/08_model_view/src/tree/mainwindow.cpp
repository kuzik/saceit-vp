#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QIcon>
#include <QStyle>
#include <QWidget>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    central(new QWidget(this)),
    layout(new QVBoxLayout(central)),
    treeView(new QTreeView(central)),
    model(new QStandardItemModel(this))
{
    // Заголовки стовпців
    model->setHorizontalHeaderLabels(
        QStringList() << tr("Категорія/Елемент") << tr("Опис") << tr("Кількість")
        );

    populateModel();
    treeView->setModel(model);
    setupViewBehavior();

    layout->addWidget(treeView);
    central->setLayout(layout);
    setCentralWidget(central);

    setWindowTitle(tr("QTreeView Демонстрація"));
}

MainWindow::~MainWindow() = default;

QIcon MainWindow::themedIcon(const QString &name, QStyle::StandardPixmap fallback) const {
    // Повертає іконку з теми; якщо її немає (Windows/macOS) — стандартну іконку стилю
    QIcon ic = QIcon::fromTheme(name);
    if (ic.isNull()) {
        ic = style()->standardIcon(fallback);
    }
    return ic;
}

void MainWindow::populateModel() {
    QStandardItem *rootItem = model->invisibleRootItem();

    // Рівень 1: категорії
    QStandardItem *fruitsItem = new QStandardItem(themedIcon("folder", QStyle::SP_DirIcon), tr("Фрукти"));
    fruitsItem->setEditable(false);
    rootItem->appendRow(QList<QStandardItem*>() << fruitsItem
                                                 << new QStandardItem(QString())   // "Опис" для категорії порожній
                                                 << new QStandardItem(QString())); // "Кількість" для категорії порожня

    QStandardItem *vegetablesItem = new QStandardItem(themedIcon("folder", QStyle::SP_DirIcon), tr("Овочі"));
    vegetablesItem->setEditable(false);
    rootItem->appendRow(QList<QStandardItem*>() << vegetablesItem
                                                 << new QStandardItem(QString())
                                                 << new QStandardItem(QString()));

    // Діти "Фрукти"
    fruitsItem->appendRow(QList<QStandardItem*>()
                          << new QStandardItem(themedIcon("text-plain", QStyle::SP_FileIcon), tr("Яблуко"))
                          << new QStandardItem(tr("Червоне, солодке"))
                          << new QStandardItem(QStringLiteral("150"))
                          );

    fruitsItem->appendRow(QList<QStandardItem*>()
                          << new QStandardItem(themedIcon("text-plain", QStyle::SP_FileIcon), tr("Банан"))
                          << new QStandardItem(tr("Жовтий, довгий"))
                          << new QStandardItem(QStringLiteral("200"))
                          );

    // Діти "Овочі"
    vegetablesItem->appendRow(QList<QStandardItem*>()
                              << new QStandardItem(themedIcon("text-plain", QStyle::SP_FileIcon), tr("Морква"))
                              << new QStandardItem(tr("Помаранчева, хрустка"))
                              << new QStandardItem(QStringLiteral("80"))
                              );

    vegetablesItem->appendRow(QList<QStandardItem*>()
                              << new QStandardItem(themedIcon("text-plain", QStyle::SP_FileIcon), tr("Помідор"))
                              << new QStandardItem(tr("Червоний, соковитий"))
                              << new QStandardItem(QStringLiteral("120"))
                              );
}

void MainWindow::setupViewBehavior() {
    treeView->setAlternatingRowColors(true);
    treeView->setEditTriggers(QAbstractItemView::DoubleClicked);
    treeView->setIndentation(20);
    treeView->expandAll();

// Заголовки/стовпці
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    treeView->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    treeView->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
#else
    treeView->header()->setResizeMode(0, QHeaderView::ResizeToContents);
    treeView->header()->setResizeMode(1, QHeaderView::Stretch);
    treeView->header()->setResizeMode(2, QHeaderView::ResizeToContents);
#endif
    treeView->header()->setStretchLastSection(true);

    // Опціонально: одноразове підлаштування ширини колонки 0
    treeView->resizeColumnToContents(0);
}
