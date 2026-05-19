#pragma once

#include <string>
#include <vector>
#include "booleanvector.h"

using uint = unsigned int;

const uint NUM_CHARS = 256;

class HuffmanTree
{
public:
    class TreeNode;

    HuffmanTree() = default;
    ~HuffmanTree();

    void build(const std::string& text);
    BooleanVector getCode(char symbol) const;

private:
    void deleteTree(TreeNode* node);
    void generateCodes(TreeNode* node, BooleanVector& currentCode);

    TreeNode* root_ = nullptr;
    BooleanVector codes_[NUM_CHARS];
    bool isBuilt_ = false;
};

class HuffmanTree::TreeNode
{
public:
    TreeNode(uint frequency, char character);
    TreeNode(TreeNode* leftChild, TreeNode* rightChild);
    ~TreeNode();

    uint getFrequency() const;
    const BooleanVector& getCharacterSet() const;
    bool isLeafNode() const;

    TreeNode* getLeftChild() const;
    TreeNode* getRightChild() const;
    char getCharacter() const;

private:
    TreeNode* leftChild_ = nullptr;
    TreeNode* rightChild_ = nullptr;
    BooleanVector characterSet_;
    uint frequency_ = 0;
    char character_ = '\0';
};