#include "BinarySearchTree.h"
#include <iostream>
#include <vector>

int main()
{
    setlocale(LC_ALL, "Russian");

    // Данные для оптимального дерева
    std::vector<int> keys = { 10, 20, 30, 40 };
    std::vector<int> p = { 2, 1, 1, 5 };      // частоты ключей
    std::vector<int> q = { 1, 10, 1, 1, 10 }; // частоты ловушек

    // Построение оптимального дерева
    BinarySearchTree optimalTree = BinarySearchTree::buildOptimalBST(keys, p, q);

    // Вывод информации о дереве
    std::cout << "Ключи: ";
    for (int k : keys) std::cout << k << " ";
    std::cout << std::endl;

    std::cout << "Частоты ключей p: ";
    for (int freq : p) std::cout << freq << " ";
    std::cout << std::endl;

    std::cout << "Частоты ловушек q: ";
    for (int freq : q) std::cout << freq << " ";
    std::cout << std::endl;

    std::cout << "\nКоличество узлов: " << optimalTree.getNodeCount() << std::endl;
    std::cout << "Высота дерева: " << optimalTree.getHeight() << std::endl;
    std::cout << "Минимальный ключ: " << optimalTree.getMinimalKey() << std::endl;
    std::cout << "Максимальный ключ: " << optimalTree.getMaximalKey() << std::endl;

    std::cout << "\nОбход в порядке возрастания: ";
    for (int key : optimalTree)
        std::cout << key << " ";
    std::cout << std::endl;

    std::cout << "\nГоризонтальный вывод дерева:" << std::endl;
    optimalTree.printTreeHorizontal();

    return 0;
}