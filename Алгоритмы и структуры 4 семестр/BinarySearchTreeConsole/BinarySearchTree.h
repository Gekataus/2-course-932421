#pragma once

#include "BinaryTree.h"
#include <stack>

// Двоичное дерево поиска
class BinarySearchTree : public BinaryTree
{
public:

    // Конструкторы
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
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

private:
    // Вспомогательные методы
    TreeNode* addNodeInternal(TreeNode* node, const int key);
    TreeNode* removeNodeInternal(TreeNode* node, const int key);
    TreeNode* findMinNode(TreeNode* node) const;
    void inorderTraversal(TreeNode* node, std::vector<int>& result) const;
    TreeNode* copyTreeInternal(const TreeNode* source);
};