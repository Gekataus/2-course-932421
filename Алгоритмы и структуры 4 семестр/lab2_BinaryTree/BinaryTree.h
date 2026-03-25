#include <iostream>
#include <vector>


//Двоичное дерево
class BinaryTree
{
public:
	class TreeNode;

	//Конструкторы/деструктор
	BinaryTree() = default;
	~BinaryTree();

	//Получение корня
	TreeNode* getRoot() const;

	//Добавление узла в дерево (методом случайного выбора поддерева)
	virtual TreeNode* addNode(const int);

	//Получение вектора, содержащего все ключи дерева по возрастанию
	std::vector<TreeNode*> getAllNodes() const;

	//Получение минимального/максимального ключа дерева
	virtual int getMinimalKey() const;
	virtual int getMaximalKey() const;

	void clear();

	void traverseTreeLeftNodeRight();
	void printToConsole();


protected:

	TreeNode* root_ = nullptr;

private:

	void getAllNodesInternal(std::vector<TreeNode*>&, TreeNode*) const;
	int getMinimalKeyInternal(TreeNode*) const;

	void destroyNode(TreeNode*);

	void traverseTreeLeftNodeRightInternal(TreeNode*);

};

//Узел дерева
class BinaryTree::TreeNode 
{
public:
	//Конструкторы (по умолчанию и с параметрами)/деструктор
	TreeNode(const int = 0, TreeNode* = nullptr, TreeNode* = nullptr);
	~TreeNode() = default;

	//Получение/Изменение ключа узла
	int getKey() const;
	void setKey(const int);

	//Получение/изменение потомков ущла
	TreeNode* getLeftChild() const;
	void setLeftChild(TreeNode* const);

	TreeNode* getRightChild() const;
	void setRightChild(TreeNode* const);

	int getNodeDegree() const;
	bool isLeafNode();

private:

	int key;
	TreeNode* leftChild_, * rightChild;
};