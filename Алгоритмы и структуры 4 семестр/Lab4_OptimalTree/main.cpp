#include "BinarySearchTree.h"
#include <iostream>
#include <vector>

int main()
{
    setlocale(LC_ALL, "Russian");

    // Проверка построения оптимального дерева поиска
    std::cout << "=== Построение оптимального дерева поиска ===\n" << std::endl;

    // Тест 1: Базовый пример
    std::cout << "Тест 1: Базовый пример" << std::endl;
    std::vector<int> keys1 = { 10, 20, 30, 40, 50 };
    std::vector<int> frequencies1 = { 3, 2, 5, 1, 4 };

    BinarySearchTree tree1 = BinarySearchTree::buildOptimalBST(keys1, frequencies1);

    std::cout << "Ключи: ";
    for (int k : keys1) std::cout << k << " ";
    std::cout << "\nЧастоты: ";
    for (int f : frequencies1) std::cout << f << " ";
    std::cout << "\nКоличество узлов: " << tree1.getNodeCount() << std::endl;
    std::cout << "Высота дерева: " << tree1.getHeight() << std::endl;
    std::cout << "Минимальный ключ: " << tree1.getMinimalKey() << std::endl;
    std::cout << "Максимальный ключ: " << tree1.getMaximalKey() << std::endl;
    std::cout << "Обход (возрастание): ";
    for (int key : tree1) std::cout << key << " ";
    std::cout << "\nГоризонтальный вывод дерева:" << std::endl;
    tree1.printTreeHorizontal();
    std::cout << std::endl;

    // Тест 2: Пустые входные данные
    std::cout << "Тест 2: Пустые входные данные" << std::endl;
    std::vector<int> keys2;
    std::vector<int> frequencies2;

    BinarySearchTree tree2 = BinarySearchTree::buildOptimalBST(keys2, frequencies2);
    std::cout << "Дерево пусто? " << (tree2.isEmpty() ? "Да" : "Нет") << std::endl;
    std::cout << "Количество узлов: " << tree2.getNodeCount() << "\n" << std::endl;

    // Тест 3: Один ключ
    std::cout << "Тест 3: Один ключ" << std::endl;
    std::vector<int> keys3 = { 100 };
    std::vector<int> frequencies3 = { 10 };

    BinarySearchTree tree3 = BinarySearchTree::buildOptimalBST(keys3, frequencies3);
    std::cout << "Корень: " << tree3.getRoot()->getKey() << std::endl;
    std::cout << "Количество узлов: " << tree3.getNodeCount() << std::endl;
    std::cout << "Горизонтальный вывод:" << std::endl;
    tree3.printTreeHorizontal();
    std::cout << std::endl;

    // Тест 4: Возрастающие частоты
    std::cout << "Тест 4: Возрастающие частоты" << std::endl;
    std::vector<int> keys4 = { 10, 20, 30, 40 };
    std::vector<int> frequencies4 = { 1, 2, 3, 4 };

    BinarySearchTree tree4 = BinarySearchTree::buildOptimalBST(keys4, frequencies4);
    std::cout << "Горизонтальный вывод:" << std::endl;
    tree4.printTreeHorizontal();
    std::cout << std::endl;

    // Тест 5: Убывающие частоты
    std::cout << "Тест 5: Убывающие частоты" << std::endl;
    std::vector<int> keys5 = { 10, 20, 30, 40 };
    std::vector<int> frequencies5 = { 4, 3, 2, 1 };

    BinarySearchTree tree5 = BinarySearchTree::buildOptimalBST(keys5, frequencies5);
    std::cout << "Горизонтальный вывод:" << std::endl;
    tree5.printTreeHorizontal();

    return 0;
}