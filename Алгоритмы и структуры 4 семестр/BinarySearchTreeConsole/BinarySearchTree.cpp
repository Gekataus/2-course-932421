#include "BinarySearchTree.h"
#include <algorithm>

//Конструкторы и деструктор

BinarySearchTree::BinarySearchTree() : BinaryTree() {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
    : BinaryTree()
{
    root_ = copyTreeInternal(other.root_);
}

BinarySearchTree::~BinarySearchTree() {}

//Оператор присваивания

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other)
{
    if (this != &other)
    {
        clear();
        root_ = copyTreeInternal(other.root_);
    }
    return *this;
}

//Вспомогательные методы

BinaryTree::TreeNode* BinarySearchTree::copyTreeInternal(const TreeNode* source)
{
    if (source == nullptr)
        return nullptr;

    TreeNode* newNode = new TreeNode(source->getKey());
    newNode->setLeftChild(copyTreeInternal(source->getLeftChild()));
    newNode->setRightChild(copyTreeInternal(source->getRightChild()));
    return newNode;
}

//Минимум и максимум

int BinarySearchTree::getMinimalKey() const
{
    if (root_ == nullptr)
        return INT_MAX;

    TreeNode* current = root_;
    while (current->getLeftChild() != nullptr)
        current = current->getLeftChild();

    return current->getKey();
}

int BinarySearchTree::getMaximalKey() const
{
    if (root_ == nullptr)
        return INT_MIN;

    TreeNode* current = root_;
    while (current->getRightChild() != nullptr)
        current = current->getRightChild();

    return current->getKey();
}

//Добавление узла

BinaryTree::TreeNode* BinarySearchTree::addNode(const int key)
{
    return addNodeInternal(root_, key);
}

BinaryTree::TreeNode* BinarySearchTree::addNodeInternal(TreeNode* node, const int key)
{
    if (!root_)
    {
        root_ = new TreeNode(key);
        return root_;
    }

    TreeNode* currentNode = root_;

    while (true)
    {
        if (key < currentNode->getKey())
        {
            if (!currentNode->getLeftChild())
            {
                currentNode->setLeftChild(new TreeNode(key));
                return currentNode->getLeftChild();
            }
            else
            {
                currentNode = currentNode->getLeftChild();
            }
        }
        else
        {
            if (!currentNode->getRightChild())
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

//Поиск узла

BinaryTree::TreeNode* BinarySearchTree::findNode(const int key) const
{
    TreeNode* current = root_;
    while (current != nullptr)
    {
        if (key == current->getKey())
            return current;
        else if (key < current->getKey())
            current = current->getLeftChild();
        else
            current = current->getRightChild();
    }
    return nullptr;
}

//Удаление узла

bool BinarySearchTree::removeNode(const int key)
{
    if (findNode(key) == nullptr)
        return false;

    root_ = removeNodeInternal(root_, key);
    return true;
}

BinaryTree::TreeNode* BinarySearchTree::removeNodeInternal(TreeNode* node, const int key)
{
    if (node == nullptr)
        return nullptr;

    if (key < node->getKey())
    {
        node->setLeftChild(removeNodeInternal(node->getLeftChild(), key));
    }
    else if (key > node->getKey())
    {
        node->setRightChild(removeNodeInternal(node->getRightChild(), key));
    }
    else
    {
        if (node->getLeftChild() == nullptr)
        {
            TreeNode* right = node->getRightChild();
            delete node;
            return right;
        }
        else if (node->getRightChild() == nullptr)
        {
            TreeNode* left = node->getLeftChild();
            delete node;
            return left;
        }
        else
        {
            TreeNode* minNode = findMinNode(node->getRightChild());
            node->setKey(minNode->getKey());
            node->setRightChild(removeNodeInternal(node->getRightChild(), minNode->getKey()));
        }
    }
    return node;
}

BinaryTree::TreeNode* BinarySearchTree::findMinNode(TreeNode* node) const
{
    while (node->getLeftChild() != nullptr)
        node = node->getLeftChild();
    return node;
}

//Получение всех ключей по возрастанию

std::vector<int> BinarySearchTree::getAllKeysSorted() const
{
    std::vector<int> result;
    inorderTraversal(root_, result);
    return result;
}

void BinarySearchTree::inorderTraversal(TreeNode* node, std::vector<int>& result) const
{
    if (node == nullptr)
        return;

    inorderTraversal(node->getLeftChild(), result);
    result.push_back(node->getKey());
    inorderTraversal(node->getRightChild(), result);
}


BinarySearchTree::Iterator BinarySearchTree::begin()
{
    return Iterator(root_);
}

BinarySearchTree::Iterator BinarySearchTree::end()
{
    return Iterator(root_, true);
}

BinarySearchTree::ConstIterator BinarySearchTree::begin() const
{
    return ConstIterator(root_);
}

BinarySearchTree::ConstIterator BinarySearchTree::end() const
{
    return ConstIterator(root_, true);
}

// Итератор

BinarySearchTree::Iterator::Iterator(TreeNode* root, bool end)
{
    if (end)
    {
        current_ = nullptr;
        return;
    }

    current_ = root;
    pushLeftPath(current_);

    if (!stack_.empty())
    {
        current_ = stack_.top();
        stack_.pop();
    }
    else
    {
        current_ = nullptr;
    }
}

void BinarySearchTree::Iterator::pushLeftPath(TreeNode* node)
{
    while (node != nullptr)
    {
        stack_.push(node);
        node = node->getLeftChild();
    }
}

bool BinarySearchTree::Iterator::operator!=(const Iterator& other) const
{
    return current_ != other.current_;
}

int BinarySearchTree::Iterator::operator*() const
{
    return current_->getKey();
}

BinarySearchTree::Iterator& BinarySearchTree::Iterator::operator++()
{
    if (current_ == nullptr)
        return *this;

    if (current_->getRightChild() != nullptr)
    {
        current_ = current_->getRightChild();
        pushLeftPath(current_);
    }

    if (!stack_.empty())
    {
        current_ = stack_.top();
        stack_.pop();
    }
    else
    {
        current_ = nullptr;
    }

    return *this;
}
// Константный итератор

BinarySearchTree::ConstIterator::ConstIterator(const TreeNode* root, bool end)
{
    if (end)
    {
        current_ = nullptr;
        return;
    }

    current_ = root;
    pushLeftPath(current_);

    if (!stack_.empty())
    {
        current_ = stack_.top();
        stack_.pop();
    }
    else
    {
        current_ = nullptr;
    }
}

void BinarySearchTree::ConstIterator::pushLeftPath(const TreeNode* node)
{
    while (node != nullptr)
    {
        stack_.push(node);
        node = node->getLeftChild();
    }
}

bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator& other) const
{
    return current_ != other.current_;
}

int BinarySearchTree::ConstIterator::operator*() const
{
    return current_->getKey();
}

BinarySearchTree::ConstIterator& BinarySearchTree::ConstIterator::operator++()
{
    if (current_ == nullptr)
        return *this;

    if (current_->getRightChild() != nullptr)
    {
        current_ = current_->getRightChild();
        pushLeftPath(current_);
    }

    if (!stack_.empty())
    {
        current_ = stack_.top();
        stack_.pop();
    }
    else
    {
        current_ = nullptr;
    }

    return *this;
}