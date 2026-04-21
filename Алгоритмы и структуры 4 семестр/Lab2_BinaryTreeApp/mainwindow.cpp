#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <random>
#include <iostream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Binary Tree Visualizer");
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

    createRandomTree();
    m_canvasWidget->setTree(&m_tree);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createRandomTree()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 99);
    int nodeCount = 20;

    for (int i = 0; i < nodeCount; ++i)
    {
        int key = dis(gen);
        m_tree.addNode(key);
    }
}