#include "mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QGraphicsProxyWidget>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QPushButton>
#include <QPainter>   // for Antialiasing render hint

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene, this)),
    resetButton(new QPushButton(tr("Скинути масштаб"), this))
{
    setupScene();
    setupView();

    // Button on the scene via proxy
    auto *proxy = scene->addWidget(resetButton);
    proxy->setPos(150, 150);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetView);

    setCentralWidget(view);
    setWindowTitle(tr("Приклад використання Qt Graphics View Framework"));
    resize(800, 600);
}

MainWindow::~MainWindow() = default;

void MainWindow::setupScene() {
    // Scene rect & background
    scene->setSceneRect(-300, -200, 600, 400);
    scene->setBackgroundBrush(QBrush(QColor(230, 230, 230)));

    // Grid
    addGrid(20.0);

    // Items
    auto *rect = new QGraphicsRectItem(0, 0, 100, 100);
    rect->setPos(-180, -130);
    rect->setBrush(QBrush(Qt::cyan));
    rect->setPen(QPen(Qt::black, 2));

    auto *ellipse = new QGraphicsEllipseItem(0, 0, 80, 80);
    ellipse->setPos(50, -50);
    ellipse->setBrush(QBrush(Qt::magenta));
    ellipse->setPen(QPen(Qt::darkMagenta, 2));

    auto *text = new QGraphicsTextItem(QStringLiteral("Переміщуваний об'єкт"));
    text->setPos(-70, 50);
    text->setDefaultTextColor(Qt::darkGreen);
    QFont font(QStringLiteral("Arial"), 14, QFont::Bold);
    text->setFont(font);
    text->setFlag(QGraphicsItem::ItemIsMovable);
    text->setFlag(QGraphicsItem::ItemIsSelectable);
    text->setFlag(QGraphicsItem::ItemIsFocusable);

    // Group (movable)
    auto *group = new QGraphicsItemGroup();
    group->addToGroup(rect);
    group->addToGroup(ellipse);
    group->setFlag(QGraphicsItem::ItemIsMovable);

    // Add to scene
    scene->addItem(group);
    scene->addItem(text);
}

void MainWindow::setupView() {
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void MainWindow::addGrid(double step) {
    if (step <= 0.0)
        return;

    QPen gridPen(Qt::gray);
    gridPen.setStyle(Qt::DotLine);
    gridPen.setCosmetic(true); // keeps line width constant when zooming

    const QRectF r = scene->sceneRect();
    const qreal left   = r.left();
    const qreal right  = r.right();
    const qreal top    = r.top();
    const qreal bottom = r.bottom();

    // How many steps fit horizontally/vertically
    const int cols = static_cast<int>(std::ceil((right  - left)  / step));
    const int rows = static_cast<int>(std::ceil((bottom - top)   / step));

    // Vertical grid lines (x = left + i*step)
    for (int i = 0; i <= cols; ++i) {
        const qreal x = left + static_cast<qreal>(i) * step;
        scene->addLine(x, top, x, bottom, gridPen);
    }

    // Horizontal grid lines (y = top + j*step)
    for (int j = 0; j <= rows; ++j) {
        const qreal y = top + static_cast<qreal>(j) * step;
        scene->addLine(left, y, right, y, gridPen);
    }
}

void MainWindow::resetView() {
    if (view)
        view->resetTransform();
}
