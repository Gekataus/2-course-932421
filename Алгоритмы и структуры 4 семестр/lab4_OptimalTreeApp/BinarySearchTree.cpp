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

BinarySearchTree BinarySearchTree::buildOptimalBST(const std::vector<int>& keys,
    const std::vector<int>& p,
    const std::vector<int>& q)
{
    // Проверка на пустые входные данные
    if (keys.empty() || p.size() != keys.size() || q.size() != keys.size() + 1)
    {
        return BinarySearchTree();
    }

    int n = keys.size();

    // W[i][j] - вес поддерева (сумма p и q)
    // C[i][j] - минимальная стоимость поиска в поддереве
    // R[i][j] - индекс корня оптимального поддерева
    std::vector<std::vector<int>> W(n + 2, std::vector<int>(n + 2, 0));
    std::vector<std::vector<int>> C(n + 3, std::vector<int>(n + 2, 0));
    std::vector<std::vector<int>> R(n + 2, std::vector<int>(n + 2, 0));

    // Инициализация для деревьев без вершин
    for (int i = 0; i <= n; i++)
    {
        W[i][i] = q[i];
        C[i][i] = q[i];
        R[i][i] = 0;
    }

    // Для деревьев, содержащих одну вершину
    // Вычисляем W[i][i+1], C[i][i+1], R[i][i+1]
    for (int i = 0; i < n; i++)
    {
        int j = i + 1;
        W[i][j] = W[i][i] + p[i] + q[j];  // q[i] + p[i+1] + q[i+1]
        C[i][j] = W[i][j] + C[i][i] + C[j][j];
        R[i][j] = j;
    }

    // Для деревьев, содержащих h вершин (2 <= h <= n)
    for (int h = 2; h <= n; h++)
    {
        for (int i = 0; i <= n - h; i++)
        {
            int j = i + h;

            // Вычисляем вес поддерева
            W[i][j] = W[i][j - 1] + p[j - 1] + q[j];

            // Поиск корня с минимальной стоимостью
            //k от R[i][j-1] до R[i+1][j]
            int minCost = INT_MAX;
            int bestK = -1;

            int leftBound = (R[i][j - 1] > 0) ? R[i][j - 1] : (i + 1);
            int rightBound = (R[i + 1][j] > 0) ? R[i + 1][j] : j;

            for (int k = leftBound; k <= rightBound && k >= i + 1 && k <= j; k++)
            {
                int currentCost = C[i][k - 1] + C[k][j];
                if (currentCost < minCost)
                {
                    minCost = currentCost;
                    bestK = k;
                }
            }

            C[i][j] = W[i][j] + minCost;
            R[i][j] = bestK;
        }
    }

    //Построение дерева по таблице R
    BinarySearchTree result;
    result.root_ = buildTreeFromRoots(keys, R, 0, n);

    return result;
}

BinaryTree::TreeNode* BinarySearchTree::buildTreeFromRoots(
    const std::vector<int>& keys,
    const std::vector<std::vector<int>>& root,
    int start, int end)
{
    // start - индекс начала интервала (включая левую ловушку)
    // end - индекс конца интервала (включая правую ловушку)
    if (start >= end)
        return nullptr;

    int k = root[start][end];
    if (k == 0)
        return nullptr;

    // Создаём узел с ключом
    TreeNode* node = new TreeNode(keys[k - 1]);

    // Рекурсивно строим левое и правое поддеревья
    node->setLeftChild(buildTreeFromRoots(keys, root, start, k - 1));
    node->setRightChild(buildTreeFromRoots(keys, root, k, end));

    return node;
}