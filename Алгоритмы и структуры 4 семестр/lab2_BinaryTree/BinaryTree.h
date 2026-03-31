#include <iostream>
#include <vector>


//Двоичное дерево
class BinaryTree
{
public:
	class TreeNode;

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

    // Получение количества узлов дерева
    int getNodeCount() const;

    // Добавление узла в дерево (методом случайного выбора поддерева)
    TreeNode* addNode(const int key);

    // Удаление узла из дерева по ключу
    bool removeNode(const int key);

    // Поиск узла дерева по ключу
    TreeNode* findNode(const int key) const;

    // Вывод в консоль дерева в горизонтальном виде
    void printToConsole() const;

    // Оператор присваивания
    BinaryTree& operator=(const BinaryTree& other);


protected:

	TreeNode* root_ = nullptr;

private:

	void getAllNodesInternal(std::vector<TreeNode*>&, TreeNode*) const;
	int getMinimalKeyInternal(TreeNode*) const;

	void destroyNode(TreeNode*);

	void traverseTreeLeftNodeRightInternal(TreeNode*);

};


class BinaryTree::TreeNode
{
public:
    // Конструкторы (по умолчанию и с параметрами)
    TreeNode();
    TreeNode(const int key, TreeNode* left = nullptr, TreeNode* right = nullptr);

    // Получение ключа узла
    int getKey() const;

    // Установка ключа узла
    void setKey(const int key);

    // Получение левого потомка
    TreeNode* getLeftChild() const;

    // Установка левого потомка
    void setLeftChild(TreeNode* const left);

    // Получение правого потомка
    TreeNode* getRightChild() const;

    // Установка правого потомка
    void setRightChild(TreeNode* const right);

private:
    int key_;
    TreeNode* leftChild_;
    TreeNode* rightChild_;
};