#include "BinaryTree.h"
#include <random>
#include <iostream>
#include <vector>

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "1. Конструктор по умолчанию" << std::endl;
    BinaryTree tree1;
    std::cout << "tree1.isEmpty() = " << (tree1.isEmpty() ? "true" : "false") << std::endl;
    
    std::cout << "\n2. Добавление узлов" << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    std::vector<int> insertedKeys;
    for (int i = 0; i < 15; ++i)
    {
        int key = dis(gen);
        insertedKeys.push_back(key);
        tree1.addNode(key);
        std::cout << "Добавлен: " << key << std::endl;
    }
    
    std::cout << "\n3. Получение корня" << std::endl;
    BinaryTree::TreeNode* root = tree1.getRoot();
    if (root)
        std::cout << "Корень: " << root->getKey() << std::endl;
    else
        std::cout << "Дерево пусто" << std::endl;
    
    std::cout << "\n4. Количество узлов" << std::endl;
    std::cout << "getNodeCount() = " << tree1.getNodeCount() << std::endl;
    
    std::cout << "\n5. Высота дерева" << std::endl;
    std::cout << "getHeight() = " << tree1.getHeight() << std::endl;
    
    std::cout << "\n6. Минимальный и максимальный ключ" << std::endl;
    try
    {
        std::cout << "getMinimalKey() = " << tree1.getMinimalKey() << std::endl;
        std::cout << "getMaximalKey() = " << tree1.getMaximalKey() << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    std::cout << "\n7. Поиск узла" << std::endl;
    for (int key : insertedKeys)
    {
        BinaryTree::TreeNode* found = tree1.findNode(key);
        if (found)
        {
            std::cout << "Ключ " << key << " найден" << std::endl;
            break;
        }
    }
    
    int searchKey = 999;
    BinaryTree::TreeNode* notFound = tree1.findNode(searchKey);
    std::cout << "Поиск ключа " << searchKey << ": " 
              << (notFound ? "найден" : "не найден") << std::endl;
    
    std::cout << "\n8. Получение всех ключей по возрастанию" << std::endl;
    std::vector<int> sortedKeys = tree1.getAllKeysSorted();
    for (int val : sortedKeys)
        std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "\n9. Удаление узла" << std::endl;
    int keyToRemove = insertedKeys[insertedKeys.size() / 2];
    std::cout << "Удаляем ключ " << keyToRemove << std::endl;
    
    bool removed = tree1.removeNode(keyToRemove);
    std::cout << "Результат: " << (removed ? "true" : "false") << std::endl;
    
    if (removed)
    {
        std::cout << "После удаления ключ " << keyToRemove 
                  << (tree1.findNode(keyToRemove) ? " еще существует" : " удален") << std::endl;
        std::cout << "Узлов после удаления: " << tree1.getNodeCount() << std::endl;
    }
    
    std::cout << "\nУдаляем несуществующий ключ 999: ";
    bool removedFalse = tree1.removeNode(999);
    std::cout << (removedFalse ? "true" : "false") << std::endl;
    
    std::cout << "\n10. Вывод дерева в консоль" << std::endl;
    tree1.printToConsole();
    
    std::cout << "\n11. Конструктор копирования" << std::endl;
    BinaryTree tree2(tree1);
    std::cout << "tree2.getNodeCount() = " << tree2.getNodeCount() << std::endl;
    std::cout << "tree2.getHeight() = " << tree2.getHeight() << std::endl;
    tree2.printToConsole();
    
    std::cout << "\n12. Оператор присваивания" << std::endl;
    BinaryTree tree3;
    tree3.addNode(100);
    tree3.addNode(200);
    std::cout << "До присваивания tree3: ";
    tree3.printToConsole();
    
    tree3 = tree1;
    std::cout << "После присваивания tree3 = tree1" << std::endl;
    std::cout << "tree3.getNodeCount() = " << tree3.getNodeCount() << std::endl;
    tree3.printToConsole();
    
    std::cout << "\n13. Самоприсваивание" << std::endl;
    BinaryTree& selfRef = tree1;
    tree1 = selfRef;
    std::cout << "Самоприсваивание выполнено, узлов: " << tree1.getNodeCount() << std::endl;
    
    std::cout << "\n14. Очистка дерева" << std::endl;
    std::cout << "До очистки узлов: " << tree1.getNodeCount() << std::endl;
    tree1.clear();
    std::cout << "После очистки узлов: " << tree1.getNodeCount() << std::endl;
    std::cout << "tree1.isEmpty() = " << (tree1.isEmpty() ? "true" : "false") << std::endl;
    tree1.printToConsole();
    
    std::cout << "\n15. Деструктор" << std::endl;
    {
        BinaryTree localTree;
        localTree.addNode(42);
        localTree.addNode(17);
        localTree.addNode(89);
        std::cout << "Локальное дерево создано, узлов: " << localTree.getNodeCount() << std::endl;
        localTree.printToConsole();
        std::cout << "Выход из области видимости" << std::endl;
    }
    std::cout << "Деструктор вызван" << std::endl;
    
    std::cout << "\n16. Работа с пустым деревом" << std::endl;
    BinaryTree emptyTree;
    std::cout << "isEmpty() = " << (emptyTree.isEmpty() ? "true" : "false") << std::endl;
    std::cout << "getNodeCount() = " << emptyTree.getNodeCount() << std::endl;
    std::cout << "getHeight() = " << emptyTree.getHeight() << std::endl;
    
    try
    {
        std::cout << "getMinimalKey() = " << emptyTree.getMinimalKey() << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Ошибка при получении минимума: " << e.what() << std::endl;
    }

    BinaryTree horisontal;
    horisontal.addNode(42);
    horisontal.addNode(2);
    horisontal.addNode(50);
    horisontal.addNode(30);
    horisontal.addNode(80);
    horisontal.addNode(20);
    horisontal.addNode(25);
    std::cout << "Дерево: "; horisontal.printToConsole(); std::cout << std::endl;
    std::cout << "Горизонтальный вывод дерева: " << std::endl; horisontal.printTreeHorizontal();
    
    return 0;
}