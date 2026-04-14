#include "BinaryTree.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <stdexcept>

// Реализация TreeNode

BinaryTree::TreeNode::TreeNode()
    : key_(0), leftChild_(nullptr), rightChild_(nullptr)
{
}

BinaryTree::TreeNode::TreeNode(const int key, TreeNode* left, TreeNode* right)
    : key_(key), leftChild_(left), rightChild_(right)
{
}

int BinaryTree::TreeNode::getKey() const
{
    return key_;
}

void BinaryTree::TreeNode::setKey(const int key)
{
    key_ = key;
}

BinaryTree::TreeNode* BinaryTree::TreeNode::getLeftChild() const
{
    return leftChild_;
}

void BinaryTree::TreeNode::setLeftChild(TreeNode* const left)
{
    leftChild_ = left;
}

BinaryTree::TreeNode* BinaryTree::TreeNode::getRightChild() const
{
    return rightChild_;
}

void BinaryTree::TreeNode::setRightChild(TreeNode* const right)
{
    rightChild_ = right;
}

// Реализация BinaryTree

BinaryTree::BinaryTree()
    : root_(nullptr)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

BinaryTree::BinaryTree(const BinaryTree& other)
    : root_(nullptr)
{
    root_ = copyTree(other.root_);
}

BinaryTree::~BinaryTree()
{
    clear();
}

BinaryTree::TreeNode* BinaryTree::getRoot() const
{
    return root_;
}

void BinaryTree::clear()
{
    destroyNode(root_);
    root_ = nullptr;
}

bool BinaryTree::isEmpty() const
{
    return root_ == nullptr;
}

int BinaryTree::getNodeCount() const
{
    if (root_ == nullptr) return 0;

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

int BinaryTree::getHeight() const
{
    return getHeightInternal(root_);
}

int BinaryTree::getMinimalKey() const
{
    if (root_ == nullptr)
    {
        throw std::runtime_error("Tree is empty");
    }
    return getMinimalKeyInternal(root_);
}

int BinaryTree::getMaximalKey() const
{
    if (root_ == nullptr)
    {
        throw std::runtime_error("Tree is empty");
    }
    return getMaximalKeyInternal(root_);
}

std::vector<int> BinaryTree::getAllKeysSorted() const
{
    std::vector<int> result;
    inorderTraversal(root_, result);
    return result;
}

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
        int direction = std::rand() % 2;

        if (direction == 0)
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
        else
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

bool BinaryTree::removeNode(const int key)
{
    if (findNode(key) == nullptr)
    {
        return false;
    }

    root_ = removeNodeInternal(root_, key);
    return true;
}

BinaryTree::TreeNode* BinaryTree::findNode(const int key) const
{
    return findNodeInternal(root_, key);
}

void BinaryTree::printToConsole() const
{
    if (!root_) return;

    std::list<BinaryTree::TreeNode*> unprocessedNodes(1, root_);

    while (!unprocessedNodes.empty())
    {
        BinaryTree::TreeNode* treeNode = unprocessedNodes.front();
        std::cout << treeNode->getKey() << " ";
        if (treeNode->getLeftChild()) unprocessedNodes.push_back(treeNode->getLeftChild());
        if (treeNode->getRightChild()) unprocessedNodes.push_back(treeNode->getRightChild());
        unprocessedNodes.pop_front();
    }
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
    if (this != &other)
    {
        clear();
        root_ = copyTree(other.root_);
    }
    return *this;
}

// Вспомогательные методы

BinaryTree::TreeNode* BinaryTree::copyTree(const TreeNode* source)
{
    if (source == nullptr)
    {
        return nullptr;
    }

    TreeNode* newNode = new TreeNode(source->getKey());
    newNode->setLeftChild(copyTree(source->getLeftChild()));
    newNode->setRightChild(copyTree(source->getRightChild()));

    return newNode;
}

void BinaryTree::destroyNode(TreeNode* node)
{
    if (node == nullptr) return;

    destroyNode(node->getLeftChild());
    destroyNode(node->getRightChild());
    delete node;
}

int BinaryTree::getHeightInternal(TreeNode* node) const
{
    if (node == nullptr) return 0;

    int leftHeight = getHeightInternal(node->getLeftChild());
    int rightHeight = getHeightInternal(node->getRightChild());

    return 1 + std::max(leftHeight, rightHeight);
}

int BinaryTree::getMinimalKeyInternal(TreeNode* node) const
{
    if (node == nullptr) return INT_MAX;

    int leftMin = getMinimalKeyInternal(node->getLeftChild());
    int rightMin = getMinimalKeyInternal(node->getRightChild());
    int currentMin = node->getKey();

    return std::min(currentMin, std::min(leftMin, rightMin));
}

int BinaryTree::getMaximalKeyInternal(TreeNode* node) const
{
    if (node == nullptr) return INT_MIN;

    int leftMax = getMaximalKeyInternal(node->getLeftChild());
    int rightMax = getMaximalKeyInternal(node->getRightChild());
    int currentMax = node->getKey();

    return std::max(currentMax, std::max(leftMax, rightMax));
}

void BinaryTree::inorderTraversal(TreeNode* node, std::vector<int>& result) const
{
    if (node == nullptr) return;

    inorderTraversal(node->getLeftChild(), result);
    result.push_back(node->getKey());
    inorderTraversal(node->getRightChild(), result);
}

BinaryTree::TreeNode* BinaryTree::findNodeInternal(TreeNode* node, const int key) const
{
    if (node == nullptr) return nullptr;

    if (node->getKey() == key) return node;

    TreeNode* leftResult = findNodeInternal(node->getLeftChild(), key);
    if (leftResult != nullptr) return leftResult;

    return findNodeInternal(node->getRightChild(), key);
}

BinaryTree::TreeNode* BinaryTree::removeNodeInternal(TreeNode* node, const int key)
{
    if (node == nullptr) return nullptr;

    if (node->getKey() == key)
    {
        if (node->getLeftChild() == nullptr)
        {
            TreeNode* rightChild = node->getRightChild();
            delete node;
            return rightChild;
        }

        if (node->getRightChild() == nullptr)
        {
            TreeNode* leftChild = node->getLeftChild();
            delete node;
            return leftChild;
        }

        TreeNode* minNode = findMinNode(node->getRightChild());
        node->setKey(minNode->getKey());
        node->setRightChild(removeNodeInternal(node->getRightChild(), minNode->getKey()));
        return node;
    }

    TreeNode* newLeft = removeNodeInternal(node->getLeftChild(), key);
    TreeNode* newRight = removeNodeInternal(node->getRightChild(), key);

    node->setLeftChild(newLeft);
    node->setRightChild(newRight);

    return node;
}

BinaryTree::TreeNode* BinaryTree::findMinNode(TreeNode* node) const
{
    while (node->getLeftChild() != nullptr)
    {
        node = node->getLeftChild();
    }
    return node;
}