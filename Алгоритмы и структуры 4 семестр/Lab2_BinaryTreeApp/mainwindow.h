#pragma once

#include <QMainWindow>
#include "BinaryTree.h"
#include "canvaswidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void createRandomTree();

    BinaryTree m_tree;
    CanvasWidget* m_canvasWidget;
};