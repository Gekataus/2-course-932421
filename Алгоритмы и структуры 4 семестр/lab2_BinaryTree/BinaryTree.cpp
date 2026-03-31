#include "BinaryTree.h"

//TreeNode
// 
// 
// Конструктор по умолчанию
BinaryTree::TreeNode::TreeNode()
    : key_(0), leftChild_(nullptr), rightChild_(nullptr)
{
}

// Конструктор с параметрами
BinaryTree::TreeNode::TreeNode(const int key, TreeNode* left, TreeNode* right)
    : key_(key), leftChild_(left), rightChild_(right)
{
}

// Получение ключа узла
int BinaryTree::TreeNode::getKey() const
{
    return key_;
}

// Установка ключа узла
void BinaryTree::TreeNode::setKey(const int key)
{
    key_ = key;
}

// Получение левого потомка
BinaryTree::TreeNode* BinaryTree::TreeNode::getLeftChild() const
{
    return leftChild_;
}

// Установка левого потомка
void BinaryTree::TreeNode::setLeftChild(TreeNode* const left)
{
    leftChild_ = left;
}

// Получение правого потомка
BinaryTree::TreeNode* BinaryTree::TreeNode::getRightChild() const
{
    return rightChild_;
}

// Установка правого потомка
void BinaryTree::TreeNode::setRightChild(TreeNode* const right)
{
    rightChild_ = right;
}


//BinaryTree
//
//
// Конструктор по умолчанию
BinaryTree::BinaryTree()
    : root_(nullptr)
{
    std::srand(std::time(nullptr));
}

// Конструктор копирования
BinaryTree::BinaryTree(const BinaryTree& other)
    : root_(nullptr)
{
    if (other.root_ == nullptr)
    {
        root_ = nullptr;
        return;
    }

    // Создание копии дерева
    root_ = new TreeNode(other.root_->getKey());

    // Копирование левого поддерева
    if (other.root_->getLeftChild() != nullptr)
    {
        BinaryTree leftTree;
        leftTree.root_ = other.root_->getLeftChild();
        BinaryTree leftCopy(leftTree);
        root_->setLeftChild(leftCopy.root_);
        leftCopy.root_ = nullptr;
    }

    // Копирование правого поддерева
    if (other.root_->getRightChild() != nullptr)
    {
        BinaryTree rightTree;
        rightTree.root_ = other.root_->getRightChild();
        BinaryTree rightCopy(rightTree);
        root_->setRightChild(rightCopy.root_);
        rightCopy.root_ = nullptr;
    }
}

// Деструктор
BinaryTree::~BinaryTree()
{
    clear();
}

// Получение корня дерева
BinaryTree::TreeNode* BinaryTree::getRoot() const
{
    return root_;
}

// Очистка дерева
void BinaryTree::clear()
{
    if (root_ == nullptr)
    {
        return;
    }

    // Удаление левого поддерева
    if (root_->getLeftChild() != nullptr)
    {
        BinaryTree leftTree;
        leftTree.root_ = root_->getLeftChild();
        leftTree.clear();
        root_->setLeftChild(nullptr);
    }

    // Удаление правого поддерева
    if (root_->getRightChild() != nullptr)
    {
        BinaryTree rightTree;
        rightTree.root_ = root_->getRightChild();
        rightTree.clear();
        root_->setRightChild(nullptr);
    }

    delete root_;
    root_ = nullptr;
}

// Проверка, пусто ли дерево
bool BinaryTree::isEmpty() const
{
    return root_ == nullptr;
}

// Получение количества узлов дерева
int BinaryTree::getNodeCount() const
{
    if (root_ == nullptr)
    {
        return 0;
    }

    int count = 1;

    if (root_->getLeftChild() != nullptr)
    {
        BinaryTree leftTree;
        leftTree.root_ = root_->getLeftChild();
        count += leftTree.getNodeCount();
    }

    if (root_->getRightChild() != nullptr)
    {
        BinaryTree rightTree;
        rightTree.root_ = root_->getRightChild();
        count += rightTree.getNodeCount();
    }

    return count;
}

// Добавление узла в дерево (методом случайного выбора поддерева)
BinaryTree::TreeNode* BinaryTree::addNode(const int key)
{
    if (root_ == nullptr)
    {
        root_ = new TreeNode(key);
        return root_;
    }

    TreeNode* currentNode = root_;

    while (true)
    {
        // Случайный выбор поддерева (0 - левое, 1 - правое)
        int direction = std::rand() % 2;

        if (direction == 0) // Левое поддерево
        {
            if (currentNode->getLeftChild() == nullptr)
            {
                currentNode->setLeftChild(new TreeNode(key));
                return currentNode->getLeftChild();
            }
            else
            {
                currentNode = currentNode->getLeftChild();
            }
        }
        else // Правое поддерево
        {
            if (currentNode->getRightChild() == nullptr)
            {
                currentNode->setRightChild(new TreeNode(key));
                return currentNode->getRightChild();
            }
            else
            {
                currentNode = currentNode->getRightChild();
            }
        }
    }
}

// Удаление узла из дерева по ключу
bool BinaryTree::removeNode(const int key)
{
    if (root_ == nullptr)
    {
        return false;
    }

    // Поиск узла и его родителя
    TreeNode* parent = nullptr;
    TreeNode* current = root_;

    while (current != nullptr && current->getKey() != key)
    {
        parent = current;

        // Сначала ищем в левом
        if (current->getLeftChild() != nullptr)
        {
            BinaryTree leftTree;
            leftTree.root_ = current->getLeftChild();
            if (leftTree.findNode(key) != nullptr)
            {
                current = current->getLeftChild();
                continue;
            }
        }

        // Затем в правом
        if (current->getRightChild() != nullptr)
        {
            BinaryTree rightTree;
            rightTree.root_ = current->getRightChild();
            if (rightTree.findNode(key) != nullptr)
            {
                current = current->getRightChild();
                continue;
            }
        }

        current = nullptr;
        break;
    }

    if (current == nullptr)
    {
        return false;
    }

    // Удаление узла
    // лист
    if (current->getLeftChild() == nullptr && current->getRightChild() == nullptr)
    {
        if (parent == nullptr)
        {
            delete root_;
            root_ = nullptr;
        }
        else if (parent->getLeftChild() == current)
        {
            parent->setLeftChild(nullptr);
            delete current;
        }
        else
        {
            parent->setRightChild(nullptr);
            delete current;
        }
    }
    // есть только левый потомок
    else if (current->getRightChild() == nullptr)
    {
        if (parent == nullptr)
        {
            root_ = current->getLeftChild();
            delete current;
        }
        else if (parent->getLeftChild() == current)
        {
            parent->setLeftChild(current->getLeftChild());
            delete current;
        }
        else
        {
            parent->setRightChild(current->getLeftChild());
            delete current;
        }
    }
    // есть только правый потомок
    else if (current->getLeftChild() == nullptr)
    {
        if (parent == nullptr)
        {
            root_ = current->getRightChild();
            delete current;
        }
        else if (parent->getLeftChild() == current)
        {
            parent->setLeftChild(current->getRightChild());
            delete current;
        }
        else
        {
            parent->setRightChild(current->getRightChild());
            delete current;
        }
    }
    // есть оба потомка
    else
    {
        // Находим минимальный узел в правом поддереве
        TreeNode* minParent = current;
        TreeNode* minNode = current->getRightChild();

        while (minNode->getLeftChild() != nullptr)
        {
            minParent = minNode;
            minNode = minNode->getLeftChild();
        }

        // Заменяем ключ
        current->setKey(minNode->getKey());

        // Удаляем минимальный узел
        if (minParent->getLeftChild() == minNode)
        {
            minParent->setLeftChild(minNode->getRightChild());
        }
        else
        {
            minParent->setRightChild(minNode->getRightChild());
        }

        delete minNode;
    }

    return true;
}

// Поиск узла дерева по ключу
BinaryTree::TreeNode* BinaryTree::findNode(const int key) const
{
    if (root_ == nullptr)
    {
        return nullptr;
    }

    if (root_->getKey() == key)
    {
        return root_;
    }

    TreeNode* result = nullptr;

    if (root_->getLeftChild() != nullptr)
    {
        BinaryTree leftTree;
        leftTree.root_ = root_->getLeftChild();
        result = leftTree.findNode(key);
        if (result != nullptr)
        {
            return result;
        }
    }

    if (root_->getRightChild() != nullptr)
    {
        BinaryTree rightTree;
        rightTree.root_ = root_->getRightChild();
        result = rightTree.findNode(key);
        if (result != nullptr)
        {
            return result;
        }
    }

    return nullptr;
}