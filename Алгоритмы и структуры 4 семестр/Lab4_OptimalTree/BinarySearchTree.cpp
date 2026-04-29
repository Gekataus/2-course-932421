#include "BinarySearchTree.h"
#include <algorithm>

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


//Конструкторы и деструктор

//Конструктор по умолчанию
BinarySearchTree::BinarySearchTree() : BinaryTree() {}

//Конструктор копирования
BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
    : BinaryTree()
{
    root_ = copyTreeInternal(other.root_);
}

//конструктор перемещения
BinarySearchTree::BinarySearchTree(BinarySearchTree&& other)
    : BinaryTree()
{
    root_ = other.root_;
    other.root_ = nullptr;
}

//Деструктор
BinarySearchTree::~BinarySearchTree() {}

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
    return addNodeInternal(key);
}

BinaryTree::TreeNode* BinarySearchTree::addNodeInternal(const int key)
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

//Оператор перемещения
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other)
{
    if (this != &other)
    {
        clear();
        root_ = other.root_;
        other.root_ = nullptr;
    }
    return *this;
}

BinaryTree::TreeNode* BinarySearchTree::copyTreeInternal(const TreeNode* source)
{
    if (source == nullptr)
        return nullptr;

    TreeNode* newNode = new TreeNode(source->getKey());
    newNode->setLeftChild(copyTreeInternal(source->getLeftChild()));
    newNode->setRightChild(copyTreeInternal(source->getRightChild()));
    return newNode;
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

BinarySearchTree BinarySearchTree::copySubtree(TreeNode* node) const
{
    BinarySearchTree newTree;
    newTree.root_ = copySubtreeInternal(node);
    return newTree;
}

BinaryTree::TreeNode* BinarySearchTree::copySubtreeInternal(const TreeNode* source) const
{
    if (source == nullptr)
        return nullptr;

    TreeNode* newNode = new TreeNode(source->getKey());
    newNode->setLeftChild(copySubtreeInternal(source->getLeftChild()));
    newNode->setRightChild(copySubtreeInternal(source->getRightChild()));
    return newNode;
}

BinarySearchTree BinarySearchTree::buildOptimalBST(const std::vector<int>& keys, const std::vector<int>& frequencies)
{
    // Проверка на пустые входные данные
    if (keys.empty() || frequencies.empty() || keys.size() != frequencies.size())
    {
        return BinarySearchTree();
    }

    int n = keys.size();

    // cost[i][j] - минимальная стоимость поиска в поддереве от i до j
    // root[i][j] - индекс корня оптимального поддерева от i до j
    // sumWeights[i][j] - сумма частот от i до j
    std::vector<std::vector<int>> cost(n + 2, std::vector<int>(n + 2, 0));
    std::vector<std::vector<int>> root(n + 2, std::vector<int>(n + 2, 0));
    std::vector<std::vector<int>> sumWeights(n + 2, std::vector<int>(n + 2, 0));

    // Вычисляем суммы частот для всех интервалов
    for (int i = 1; i <= n; i++)
    {
        sumWeights[i][i] = frequencies[i - 1];
        for (int j = i + 1; j <= n; j++)
        {
            sumWeights[i][j] = sumWeights[i][j - 1] + frequencies[j - 1];
        }
    }

    // Инициализация для поддеревьев из одного узла
    for (int i = 1; i <= n; i++)
    {
        cost[i][i] = frequencies[i - 1];
        root[i][i] = i;
    }

    // Построение оптимального дерева для интервалов возрастающей длины
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;
            int sum = sumWeights[i][j];

            cost[i][j] = INT_MAX;

            // Перебираем возможные корни
            for (int k = i; k <= j; k++)
            {
                int currentCost = cost[i][k - 1] + cost[k + 1][j] + sum;

                if (currentCost < cost[i][j])
                {
                    cost[i][j] = currentCost;
                    root[i][j] = k;
                }
            }
        }
    }

    // Построение дерева по таблице root
    BinarySearchTree result;
    result.root_ = buildTreeFromRoots(keys, root, 1, n);

    return result;
}

BinaryTree::TreeNode* BinarySearchTree::buildTreeFromRoots(
    const std::vector<int>& keys,
    const std::vector<std::vector<int>>& root,
    int start, int end)
{
    if (start > end)
        return nullptr;

    int r = root[start][end];
    if (r == 0)
        return nullptr;

    TreeNode* node = new TreeNode(keys[r - 1]);

    node->setLeftChild(buildTreeFromRoots(keys, root, start, r - 1));
    node->setRightChild(buildTreeFromRoots(keys, root, r + 1, end));

    return node;
}