#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>

// Двоичное дерево
class BinaryTree
{
public:
    class TreeNode;

    // Конструкторы/деструктор
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();

    // Получение корня дерева
    TreeNode* getRoot() const;

    // Очистка дерева (удаление всех узлов)
    void clear();

    // Проверка, пусто ли дерево
    bool isEmpty() const;

    // Получение высоты дерева
    int getHeight() const;

    // Получение количества узлов дерева
    int getNodeCount() const;

    // Получение минимального ключа дерева
    int getMinimalKey() const;

    // Получение максимального ключа дерева
    int getMaximalKey() const;

    // Добавление узла в дерево (методом случайного выбора поддерева)
    TreeNode* addNode(const int key);

    // Удаление узла из дерева по ключу
    bool removeNode(const int key);

    // Поиск узла дерева по ключу
    TreeNode* findNode(const int key) const;

    // Получение вектора, содержащего все ключи дерева по возрастанию
    std::vector<int> getAllKeysSorted() const;

    // Вывод в консоль дерева в горизонтальном виде (обход в ширину)
    void printToConsole() const;

    // Оператор присваивания
    BinaryTree& operator=(const BinaryTree& other);

protected:
    TreeNode* root_ = nullptr;

private:
    // Вспомогательные рекурсивные методы
    void copyTree(TreeNode*& target, TreeNode* source);
    void destroyNode(TreeNode* node);
    int getHeightInternal(TreeNode* node) const;
    int getMinimalKeyInternal(TreeNode* node) const;
    int getMaximalKeyInternal(TreeNode* node) const;
    void inorderTraversal(TreeNode* node, std::vector<int>& result) const;
    TreeNode* findNodeInternal(TreeNode* node, const int key) const;
    TreeNode* removeNodeInternal(TreeNode* node, const int key);
    TreeNode* findMinNode(TreeNode* node) const;
};

// Узел дерева
class BinaryTree::TreeNode
{
protected:
    // Конструкторы (по умолчанию и с параметрами)
    TreeNode();
    TreeNode(const int key, TreeNode* left = nullptr, TreeNode* right = nullptr);

    // Получение/Изменение ключа узла
    int getKey() const;
    void setKey(const int key);

    // Получение/изменение потомков узла
    TreeNode* getLeftChild() const;
    void setLeftChild(TreeNode* const left);

    TreeNode* getRightChild() const;
    void setRightChild(TreeNode* const right);

private:
    int key_;
    TreeNode* leftChild_;
    TreeNode* rightChild_;
};