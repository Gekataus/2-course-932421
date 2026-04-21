#include "canvaswidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <cmath>

CanvasWidget::CanvasWidget(QWidget* parent)
    : QWidget(parent)
    , m_tree(nullptr)
{
    setMinimumSize(1200, 800);
    setStyleSheet("background-color: white;");
}

void CanvasWidget::setTree(BinaryTree* tree)
{
    m_tree = tree;
    update();
}

int CanvasWidget::getNodeWidth(BinaryTree::TreeNode* node)
{
    if (!node) return 0;
    return 1 + getNodeWidth(node->getLeftChild()) + getNodeWidth(node->getRightChild());
}

void CanvasWidget::calculatePositions(BinaryTree::TreeNode* node, int& x, int y, int level)
{
    if (!node) return;

    // Сначала обрабатываем левое поддерево
    int leftWidth = getNodeWidth(node->getLeftChild());
    int rightWidth = getNodeWidth(node->getRightChild());

    // Позиция текущего узла - между левым и правым поддеревьями
    int leftPos = x;
    int rightPos = x + leftWidth * NODE_SPACING;

    if (node->getLeftChild())
    {
        calculatePositions(node->getLeftChild(), leftPos, y + LEVEL_HEIGHT, level + 1);
    }

    if (node->getRightChild())
    {
        calculatePositions(node->getRightChild(), rightPos, y + LEVEL_HEIGHT, level + 1);
    }

    // Центр текущего узла
    int centerX = (leftPos + rightPos) / 2;
    if (!node->getLeftChild() && !node->getRightChild())
    {
        centerX = x;
    }

    NodePos pos;
    pos.x = centerX;
    pos.y = y;
    pos.node = node;
    m_positions[node] = pos;

    // Обновляем x для возврата
    x = rightPos;
}

void CanvasWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    if (!m_tree || m_tree->isEmpty())
    {
        QPainter painter(this);
        painter.setPen(Qt::gray);
        painter.setFont(QFont("Arial", 14));
        painter.drawText(rect(), Qt::AlignCenter, "Tree is empty");
        return;
    }

    // Вычисляем позиции
    m_positions.clear();
    int startX = NODE_SPACING;
    int startY = 50;

    calculatePositions(m_tree->getRoot(), startX, startY, 0);

    // Находим минимальный и максимальный X
    int minX = 0, maxX = width();
    for (auto it = m_positions.begin(); it != m_positions.end(); ++it)
    {
        int x = it.value().x;
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
    }

    int offsetX = (width() - (maxX - minX)) / 2 - minX;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("Arial", 10));

    // линии
    for (auto it = m_positions.begin(); it != m_positions.end(); ++it)
    {
        BinaryTree::TreeNode* node = it.key();
        NodePos pos = it.value();

        int x1 = pos.x + offsetX;
        int y1 = pos.y;

        if (node->getLeftChild() && m_positions.contains(node->getLeftChild()))
        {
            NodePos childPos = m_positions[node->getLeftChild()];
            int x2 = childPos.x + offsetX;
            int y2 = childPos.y;
            painter.setPen(QPen(Qt::gray, 2));
            painter.drawLine(x1, y1 + NODE_RADIUS, x2, y2 - NODE_RADIUS);
        }

        if (node->getRightChild() && m_positions.contains(node->getRightChild()))
        {
            NodePos childPos = m_positions[node->getRightChild()];
            int x2 = childPos.x + offsetX;
            int y2 = childPos.y;
            painter.setPen(QPen(Qt::gray, 2));
            painter.drawLine(x1, y1 + NODE_RADIUS, x2, y2 - NODE_RADIUS);
        }
    }

    // узлы
    for (auto it = m_positions.begin(); it != m_positions.end(); ++it)
    {
        NodePos pos = it.value();
        int x = pos.x + offsetX;
        int y = pos.y;

        // круг
        painter.setBrush(QBrush(QColor(0, 96, 192)));
        painter.setPen(QPen(Qt::black, 2));
        painter.drawEllipse(x - NODE_RADIUS, y - NODE_RADIUS,
            NODE_RADIUS * 2, NODE_RADIUS * 2);

        // текст
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 11, QFont::Bold));
        painter.drawText(QRect(x - NODE_RADIUS, y - NODE_RADIUS,
            NODE_RADIUS * 2, NODE_RADIUS * 2),
            Qt::AlignCenter, QString::number(pos.node->getKey()));
    }
}