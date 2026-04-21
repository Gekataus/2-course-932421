#pragma once

#include <QMainWindow>
#include "BinarySearchTree.h"
#include "canvaswidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void createRandomTree();

    BinarySearchTree m_tree;
    CanvasWidget* m_canvasWidget;
};