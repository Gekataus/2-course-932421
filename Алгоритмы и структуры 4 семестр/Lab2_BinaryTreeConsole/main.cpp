#include "BinaryTree.h"
#include <random>
#include <iostream>

int main()
{
    BinaryTree tree;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < 10; ++i)
    {
        tree.addNode(dis(gen));
    }

    tree.printToConsole(); std::cout << std::endl;

    BinaryTree tree2;
    tree2.addNode(45);
    tree2.addNode(50);
    tree2.addNode(20);
    tree2.addNode(60);
    tree2.printToConsole();


    return 0;
}