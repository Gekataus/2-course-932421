#include "huffmantree.h"
#include "booleanvector.h"
#include <algorithm>
#include <iostream>
#include <fstream>

HuffmanTree::TreeNode::TreeNode(uint frequency, char character)
    : frequency_(frequency), character_(character)
{
    characterSet_ = BooleanVector(NUM_CHARS, false);
    characterSet_.setBit((unsigned char)character, true);
}

HuffmanTree::TreeNode::TreeNode(TreeNode* leftChild, TreeNode* rightChild)
    : leftChild_(leftChild), rightChild_(rightChild)
{
    frequency_ = leftChild->getFrequency() + rightChild->getFrequency();

    characterSet_ = BooleanVector(NUM_CHARS, false);
    for (uint i = 0; i < NUM_CHARS; i++)
    {
        if (leftChild->getCharacterSet()[i] || rightChild->getCharacterSet()[i])
        {
            characterSet_.setBit(i, true);
        }
    }
    character_ = '\0';
}

HuffmanTree::TreeNode::~TreeNode()
{
}

uint HuffmanTree::TreeNode::getFrequency() const
{
    return frequency_;
}

const BooleanVector& HuffmanTree::TreeNode::getCharacterSet() const
{
    return characterSet_;
}

bool HuffmanTree::TreeNode::isLeafNode() const
{
    return leftChild_ == nullptr && rightChild_ == nullptr;
}

HuffmanTree::TreeNode* HuffmanTree::TreeNode::getLeftChild() const
{
    return leftChild_;
}

HuffmanTree::TreeNode* HuffmanTree::TreeNode::getRightChild() const
{
    return rightChild_;
}

char HuffmanTree::TreeNode::getCharacter() const
{
    return character_;
}

HuffmanTree::~HuffmanTree()
{
    deleteTree(root_);
}

void HuffmanTree::deleteTree(TreeNode* node)
{
    if (node == nullptr) return;
    deleteTree(node->getLeftChild());
    deleteTree(node->getRightChild());
    delete node;
}

void HuffmanTree::build(const std::string& text)
{
    deleteTree(root_);
    root_ = nullptr;
    isBuilt_ = false;

    for (uint i = 0; i < NUM_CHARS; i++)
    {
        codes_[i] = BooleanVector();
    }

    if (text.empty()) return;

    uint frequencies[NUM_CHARS] = { 0 };
    for (char c : text)
    {
        frequencies[(unsigned char)c]++;
    }

    std::vector<TreeNode*> nodes;
    for (uint i = 0; i < NUM_CHARS; i++)
    {
        if (frequencies[i] > 0)
        {
            nodes.push_back(new TreeNode(frequencies[i], (char)i));
        }
    }

    std::sort(nodes.begin(), nodes.end(),
        [](const TreeNode* a, const TreeNode* b) {
            return a->getFrequency() < b->getFrequency();
        });

    while (nodes.size() > 1)
    {
        TreeNode* left = nodes[0];
        TreeNode* right = nodes[1];

        TreeNode* parent = new TreeNode(left, right);

        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());

        auto it = std::lower_bound(nodes.begin(), nodes.end(), parent,
            [](const TreeNode* a, const TreeNode* b) {
                return a->getFrequency() < b->getFrequency();
            });
        nodes.insert(it, parent);
    }

    if (!nodes.empty())
    {
        root_ = nodes[0];
        BooleanVector currentCode;
        generateCodes(root_, currentCode);
        isBuilt_ = true;
    }
}

double HuffmanTree::encode(const std::string& inputFileName, const std::string& outputFileName)
{
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        return -1.0;
    }

    std::string text;
    char ch;
    while (inputFile.get(ch))
    {
        text += ch;
    }
    inputFile.close();

    if (text.empty())
    {
        return -1.0;
    }

    if (!isBuilt_)
    {
        build(text);
    }

    std::string encodedString;
    for (char c : text)
    {
        BooleanVector code = getCode(c);
        for (uint i = 0; i < code.getLength(); i++)
        {
            encodedString += (code[i] ? '1' : '0');
        }
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        return -1.0;
    }

    outputFile << encodedString;
    outputFile.close();

    double originalSize = text.length() * 8;
    double compressedSize = encodedString.length();

    if (originalSize > 0)
    {
        return (compressedSize / originalSize) * 100.0;
    }

    return 0.0;
}

void HuffmanTree::generateCodes(TreeNode* node, BooleanVector& currentCode)
{
    if (node == nullptr) return;

    if (node->isLeafNode())
    {
        codes_[(unsigned char)node->getCharacter()] = currentCode;
    }
    else
    {
        uint oldLength = currentCode.getLength();

        BooleanVector leftCode(oldLength + 1, false);
        for (uint i = 0; i < oldLength; i++)
        {
            if (currentCode[i])
                leftCode.setBit(i, true);
        }
        leftCode.setBit(oldLength, false);
        generateCodes(node->getLeftChild(), leftCode);

        BooleanVector rightCode(oldLength + 1, false);
        for (uint i = 0; i < oldLength; i++)
        {
            if (currentCode[i])
                rightCode.setBit(i, true);
        }
        rightCode.setBit(oldLength, true);
        generateCodes(node->getRightChild(), rightCode);
    }
}

BooleanVector HuffmanTree::getCode(char symbol) const
{
    return codes_[(unsigned char)symbol];
}