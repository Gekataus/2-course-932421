#pragma once

#include <QWidget>
#include "BinaryTree.h"
#include <QMap>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget* parent = nullptr);
    void setTree(BinaryTree* tree);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void calculatePositions(BinaryTree::TreeNode* node, int& x, int y, int level);
    int getNodeWidth(BinaryTree::TreeNode* node);
    BinaryTree* m_tree;

    struct NodePos {
        int x;
        int y;
        BinaryTree::TreeNode* node;
    };

    QMap<BinaryTree::TreeNode*, NodePos> m_positions;

    const int NODE_RADIUS = 22;
    const int LEVEL_HEIGHT = 70;
    const int NODE_SPACING = 35;
};