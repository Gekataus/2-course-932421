#pragma once

#include "BinaryTree.h"
#include <stack>

// Двоичное дерево поиска
class BinarySearchTree : public BinaryTree
{
public:

    // Итератор
    class Iterator
    {
    public:
        Iterator(TreeNode* root, bool end = false);
        bool operator!=(const Iterator& other) const;
        int operator*() const;
        Iterator& operator++();

    private:
        std::stack<TreeNode*> stack_;
        TreeNode* current_;
        void pushLeftPath(TreeNode* node);
    };

    // Константный итератор
    class ConstIterator
    {
    public:
        ConstIterator(const TreeNode* root, bool end = false);
        bool operator!=(const ConstIterator& other) const;
        int operator*() const;
        ConstIterator& operator++();

    private:
        std::stack<const TreeNode*> stack_;
        const TreeNode* current_;
        void pushLeftPath(const TreeNode* node);
    };

    // Конструкторы
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree(BinarySearchTree&& other);

    // Деструктор
    ~BinarySearchTree();

    // получение минимального/максимального ключа
    int getMinimalKey() const override;
    int getMaximalKey() const override;

    // Добавление узла в дерево
    TreeNode* addNode(const int key) override;

    // Удаление узла
    bool removeNode(const int key) override;

    //Поиск узла
    TreeNode* findNode(const int key) const override;

    //Получение отсортированного по возрастанию вектора из ключей дерева
    std::vector<int> getAllKeysSorted() const override;

    // Оператор присваивания
    BinarySearchTree& operator=(const BinarySearchTree& other);
    BinarySearchTree& operator=(BinarySearchTree&& other);  // оператор перемещения

    static BinarySearchTree buildOptimalBST(const std::vector<int>& keys,
        const std::vector<int>& p,
        const std::vector<int>& q);

    // Итераторы
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;

    // Копирование поддерева узла (возвращает новый объект класса)
    BinarySearchTree copySubtree(TreeNode* node) const;

private:
    // Вспомогательные методы
    TreeNode* addNodeInternal(const int key);
    TreeNode* removeNodeInternal(TreeNode* node, const int key);
    TreeNode* findMinNode(TreeNode* node) const;
    void inorderTraversal(TreeNode* node, std::vector<int>& result) const;
    TreeNode* copyTreeInternal(const TreeNode* source);

    TreeNode* copySubtreeInternal(const TreeNode* node) const;
    static TreeNode* buildTreeFromRoots(const std::vector<int>& keys,
        const std::vector<std::vector<int>>& root,
        int start, int end);
};