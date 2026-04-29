#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <vector>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Binary Search Tree - Optimal Tree");
    setMinimumSize(1000, 700);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_canvasWidget = new CanvasWidget(this);
    scrollArea->setWidget(m_canvasWidget);
    mainLayout->addWidget(scrollArea);

    // Данные для оптимального дерева
    std::vector<int> keys = { 10, 20, 30, 40 };
    std::vector<int> p = { 2, 1, 1, 5 };      // частоты ключей
    std::vector<int> q = { 1, 10, 1, 1, 10 }; // частоты ловушек

    // Построение оптимального дерева
    m_tree = BinarySearchTree::buildOptimalBST(keys, p, q);
    m_canvasWidget->setTree(&m_tree);
}

MainWindow::~MainWindow()
{
}