#include "BinarySearchTree.h"
#include <iostream>
#include <vector>
#include <random>

int main()
{
    setlocale(LC_ALL, "Russian");

    // 1. Конструктор по умолчанию
    std::cout << "\n1. Конструктор по умолчанию" << std::endl;
    BinarySearchTree tree1;
    std::cout << "tree1.isEmpty() = " << (tree1.isEmpty() ? "true" : "false") << std::endl;

    // 2. Добавление узлов
    std::cout << "\n2. Добавление узлов" << std::endl;
    std::vector<int> testKeys = { 50, 30, 70, 20, 40, 60, 80, 35, 45, 55, 65, 75, 85 };
    for (int key : testKeys)
    {
        tree1.addNode(key);
        std::cout << "Добавлен: " << key << std::endl;
    }

    // 3. Вывод дерева
    std::cout << "\n3. Вывод дерева (обход в ширину)" << std::endl;
    tree1.printToConsole();

    std::cout << "\n4. Горизонтальный вывод дерева" << std::endl;
    tree1.printTreeHorizontal();

    // 3. Получение корня
    std::cout << "\n5. Получение корня" << std::endl;
    BinaryTree::TreeNode* root = tree1.getRoot();
    if (root)
        std::cout << "Корень: " << root->getKey() << std::endl;

    // 4. Количество узлов
    std::cout << "\n6. Количество узлов" << std::endl;
    std::cout << "getNodeCount() = " << tree1.getNodeCount() << std::endl;

    // 5. Высота дерева
    std::cout << "\n7. Высота дерева" << std::endl;
    std::cout << "getHeight() = " << tree1.getHeight() << std::endl;

    // 6. Минимальный и максимальный ключ
    std::cout << "\n8. Минимальный и максимальный ключ" << std::endl;
    std::cout << "getMinimalKey() = " << tree1.getMinimalKey() << std::endl;
    std::cout << "getMaximalKey() = " << tree1.getMaximalKey() << std::endl;

    // 7. Поиск узла
    std::cout << "\n9. Поиск узла" << std::endl;
    int searchKey = 45;
    BinaryTree::TreeNode* found = tree1.findNode(searchKey);
    std::cout << "Поиск ключа " << searchKey << ": " << (found ? "найден" : "не найден") << std::endl;

    searchKey = 100;
    found = tree1.findNode(searchKey);
    std::cout << "Поиск ключа " << searchKey << ": " << (found ? "найден" : "не найден") << std::endl;

    // 8. Получение всех ключей по возрастанию
    std::cout << "\n10. Получение всех ключей по возрастанию" << std::endl;
    std::vector<int> sortedKeys = tree1.getAllKeysSorted();
    std::cout << "Отсортированные ключи: ";
    for (int val : sortedKeys)
        std::cout << val << " ";
    std::cout << std::endl;

    // 9. Удаление узла (лист)
    std::cout << "\n11. Удаление узла (лист - 35)" << std::endl;
    bool removed = tree1.removeNode(35);
    std::cout << "Результат удаления: " << (removed ? "true" : "false") << std::endl;
    std::cout << "Узлов после удаления: " << tree1.getNodeCount() << std::endl;
    std::cout << "Проверка: ключ 35 " << (tree1.findNode(35) ? "найден" : "удалён") << std::endl;

    // 10. Удаление узла (с одним потомком)
    std::cout << "\n12. Удаление узла (с одним потомком - 20)" << std::endl;
    removed = tree1.removeNode(20);
    std::cout << "Результат удаления: " << (removed ? "true" : "false") << std::endl;
    std::cout << "Узлов после удаления: " << tree1.getNodeCount() << std::endl;

    // 11. Удаление узла (с двумя потомками)
    std::cout << "\n13. Удаление узла (с двумя потомками - 50)" << std::endl;
    removed = tree1.removeNode(50);
    std::cout << "Результат удаления: " << (removed ? "true" : "false") << std::endl;
    std::cout << "Новый корень: " << tree1.getRoot()->getKey() << std::endl;
    std::cout << "Узлов после удаления: " << tree1.getNodeCount() << std::endl;

    // 12. Удаление несуществующего узла
    std::cout << "\n14. Удаление несуществующего узла (999)" << std::endl;
    removed = tree1.removeNode(999);
    std::cout << "Результат удаления: " << (removed ? "true" : "false") << std::endl;

    // 14. Конструктор копирования
    std::cout << "\n15. Конструктор копирования" << std::endl;
    BinarySearchTree tree2(tree1);
    std::cout << "tree2.getNodeCount() = " << tree2.getNodeCount() << std::endl;
    std::cout << "tree2.getMinimalKey() = " << tree2.getMinimalKey() << std::endl;
    std::cout << "tree2.getMaximalKey() = " << tree2.getMaximalKey() << std::endl;
    std::cout << "tree2: ";
    tree2.printToConsole();

    // 15. Оператор присваивания
    std::cout << "\n16. Оператор присваивания" << std::endl;
    BinarySearchTree tree3;
    tree3.addNode(100);
    tree3.addNode(200);
    tree3.addNode(50);
    std::cout << "До присваивания tree3: ";
    tree3.printToConsole();

    tree3 = tree1;
    std::cout << "После присваивания tree3 = tree1" << std::endl;
    std::cout << "tree3.getNodeCount() = " << tree3.getNodeCount() << std::endl;
    std::cout << "tree3: ";
    tree3.printToConsole();

    // 16. Самоприсваивание
    std::cout << "\n17. Самоприсваивание" << std::endl;
    BinarySearchTree& selfRef = tree1;
    tree1 = selfRef;
    std::cout << "Самоприсваивание выполнено, узлов: " << tree1.getNodeCount() << std::endl;

    // 17. Очистка дерева
    std::cout << "\n18. Очистка дерева" << std::endl;
    std::cout << "До очистки узлов: " << tree1.getNodeCount() << std::endl;
    tree1.clear();
    std::cout << "После очистки узлов: " << tree1.getNodeCount() << std::endl;
    std::cout << "tree1.isEmpty() = " << (tree1.isEmpty() ? "true" : "false") << std::endl;
    tree1.printToConsole();

    // 18. Работа с пустым деревом
    std::cout << "\n19. Работа с пустым деревом" << std::endl;
    BinarySearchTree emptyTree;
    std::cout << "isEmpty() = " << (emptyTree.isEmpty() ? "true" : "false") << std::endl;
    std::cout << "getNodeCount() = " << emptyTree.getNodeCount() << std::endl;
    std::cout << "getHeight() = " << emptyTree.getHeight() << std::endl;
    std::cout << "getMinimalKey() = " << emptyTree.getMinimalKey() << std::endl;
    std::cout << "getMaximalKey() = " << emptyTree.getMaximalKey() << std::endl;

    // 19. Проверка через указатель на базовый класс
    std::cout << "\n20. Проверка через указатель на базовый класс" << std::endl;
    BinaryTree* basePtr = new BinarySearchTree();
    basePtr->addNode(50);
    basePtr->addNode(30);
    basePtr->addNode(70);
    basePtr->addNode(20);
    basePtr->addNode(40);

    std::cout << "Через указатель на BinaryTree:" << std::endl;
    std::cout << "Минимум: " << basePtr->getMinimalKey() << std::endl;
    std::cout << "Максимум: " << basePtr->getMaximalKey() << std::endl;
    std::cout << "Количество узлов: " << basePtr->getNodeCount() << std::endl;

    BinaryTree::TreeNode* foundNode = basePtr->findNode(40);
    std::cout << "Поиск 40: " << (foundNode ? "найден" : "не найден") << std::endl;

    std::vector<int> sorted = basePtr->getAllKeysSorted();
    std::cout << "Отсортированные ключи: ";
    for (int val : sorted)
        std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}