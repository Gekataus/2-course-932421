#include <iostream>
#include "LinkedList.h"
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        // Тест конструкторов
        cout << "1. Тест конструкторов LinkedList" << endl;

        // Конструктор по умолчанию
        LinkedList<int> defaultList;
        cout << "Конструктор по умолчанию (размер: " << defaultList.getSize() << ")" << endl;

        // Конструктор из массива
        int arr[] = { 1, 2, 3, 4, 5 };
        LinkedList<int> arrayList(arr, 5);
        cout << "Конструктор из массива {1,2,3,4,5}: " << arrayList << endl;
        cout << "Размер: " << arrayList.getSize() << endl;

        // Конструктор копирования
        LinkedList<int> copiedList(arrayList);
        cout << "Конструктор копирования: " << copiedList << endl;
        cout << "Размер: " << copiedList.getSize() << endl << endl;

        // Тест добавления элементов
        cout << "2. Тест добавления элементов" << endl;
        LinkedList<int> testAdd;

        // Добавление в голову
        testAdd.addToHead(10);
        testAdd.addToHead(20);
        testAdd.addToHead(30);
        cout << "После addToHead(10,20,30): " << testAdd << endl;

        // Добавление в хвост
        testAdd.addToTail(40);
        testAdd.addToTail(50);
        cout << "После addToTail(40,50): " << testAdd << endl;

        // Добавление на позицию
        testAdd.addAtPosition(25, 2); // На позицию 2 (0-based)
        cout << "После addAtPosition(25, 2): " << testAdd << endl;

        // Добавление после ключа
        testAdd.addAfterKey(35, 30); // После первого вхождения 30
        cout << "После addAfterKey(35, 30): " << testAdd << endl;

        testAdd.addAfterKey(45, 40); // После первого вхождения 40
        cout << "После addAfterKey(45, 40): " << testAdd << endl << endl;

        // Тест удаления элементов
        cout << "3. Тест удаления элементов" << endl;
        LinkedList<int> testRemove = testAdd;
        cout << "Исходный список: " << testRemove << endl;

        // Удаление из головы
        testRemove.removeFromHead();
        cout << "После removeFromHead(): " << testRemove << endl;

        // Удаление из хвоста
        testRemove.removeFromTail();
        cout << "После removeFromTail(): " << testRemove << endl;

        // Удаление по позиции
        testRemove.removeAtPosition(2);
        cout << "После removeAtPosition(2): " << testRemove << endl;

        // Удаление по ключу
        testRemove.removeByKey(25);
        cout << "После removeByKey(25): " << testRemove << endl << endl;

        // Тест поиска
        cout << "4. Тест поиска элементов" << endl;
        LinkedList<int> testFind;
        for (int i = 1; i <= 10; i++) {
            testFind.addToTail(i * 10);
        }
        cout << "Список: " << testFind << endl;

        auto found = testFind.find(50);
        if (found) {
            cout << "Найден элемент 50" << endl;
        }
        else {
            cout << "Элемент 50 не найден" << endl;
        }

        found = testFind.find(99);
        if (found) {
            cout << "Найден элемент 99" << endl;
        }
        else {
            cout << "Элемент 99 не найден" << endl;
        }

        // Поиск min/max
        cout << "Минимальный элемент: " << testFind.findMin() << endl;
        cout << "Максимальный элемент: " << testFind.findMax() << endl << endl;

        // Тест обмена (swap)
        cout << "5. Тест обмена списков (swap)" << endl;
        LinkedList<int> list1;
        list1.addToTail(1);
        list1.addToTail(2);
        list1.addToTail(3);

        LinkedList<int> list2;
        list2.addToTail(10);
        list2.addToTail(20);
        list2.addToTail(30);
        list2.addToTail(40);

        cout << "До swap:" << endl;
        cout << "list1: " << list1 << " (размер: " << list1.getSize() << ")" << endl;
        cout << "list2: " << list2 << " (размер: " << list2.getSize() << ")" << endl;

        list1.swap(list2);

        cout << "После swap:" << endl;
        cout << "list1: " << list1 << " (размер: " << list1.getSize() << ")" << endl;
        cout << "list2: " << list2 << " (размер: " << list2.getSize() << ")" << endl << endl;

        // Тест оператора []
        cout << "6. Тест оператора []" << endl;
        LinkedList<int> testIndex;
        for (int i = 0; i < 5; i++) {
            testIndex.addToTail(i * 10);
        }
        cout << "Список: " << testIndex << endl;

        try {
            cout << "testIndex[0] = " << testIndex[0] << endl;
            cout << "testIndex[2] = " << testIndex[2] << endl;
            cout << "testIndex[4] = " << testIndex[4] << endl;

            // Изменение через оператор []
            testIndex[1] = 999;
            testIndex[3] = 888;
            cout << "После изменения testIndex[1]=999, testIndex[3]=888: " << testIndex << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка доступа по индексу: " << e.what() << endl;
        }
        cout << endl;

        // Тест операторов сравнения
        cout << "7. Тест операторов сравнения" << endl;
        LinkedList<int> listA;
        listA.addToTail(1);
        listA.addToTail(2);
        listA.addToTail(3);

        LinkedList<int> listB;
        listB.addToTail(1);
        listB.addToTail(2);
        listB.addToTail(3);

        LinkedList<int> listC;
        listC.addToTail(1);
        listC.addToTail(3);
        listC.addToTail(2);

        cout << "listA: " << listA << endl;
        cout << "listB: " << listB << endl;
        cout << "listC: " << listC << endl;
        cout << "listA == listB: " << (listA == listB) << endl;
        cout << "listA == listC: " << (listA == listC) << endl;
        cout << "listA != listC: " << (listA != listC) << endl << endl;

        // Тест конкатенации
        cout << "8. Тест конкатенации списков" << endl;
        LinkedList<int> concat1;
        concat1.addToTail(1);
        concat1.addToTail(2);
        concat1.addToTail(3);

        LinkedList<int> concat2;
        concat2.addToTail(4);
        concat2.addToTail(5);
        concat2.addToTail(6);

        cout << "concat1: " << concat1 << endl;
        cout << "concat2: " << concat2 << endl;

        LinkedList<int> concatResult = concat1 + concat2;
        cout << "concat1 + concat2: " << concatResult << endl;

        concat1 += concat2;
        cout << "concat1 += concat2: " << concat1 << endl << endl;

        // Тест оператора присваивания
        cout << "9. Тест оператора присваивания" << endl;
        LinkedList<int> original;
        original.addToTail(100);
        original.addToTail(200);
        original.addToTail(300);

        LinkedList<int> assigned;
        assigned = original;

        cout << "original: " << original << endl;
        cout << "assigned: " << assigned << endl;
        cout << "original == assigned: " << (original == assigned) << endl;

        // Тест очистки списка
        cout << "10. Тест очистки списка" << endl;
        LinkedList<int> testClear;
        testClear.addToTail(1);
        testClear.addToTail(2);
        testClear.addToTail(3);

        cout << "До clear(): " << testClear << endl;
        cout << "isEmpty(): " << testClear.isEmpty() << endl;

        testClear.clear();

        cout << "После clear(): " << testClear << endl;
        cout << "isEmpty(): " << testClear.isEmpty() << endl;
        cout << "Размер: " << testClear.getSize() << endl << endl;

        cout << endl;

        // Тест итераторов
        cout << "12. Тест базовых операций с итераторами" << endl;
        LinkedList<int> iterList;
        for (int i = 1; i <= 5; i++) {
            iterList.addToTail(i * 10);
        }
        cout << "Исходный список: " << iterList << endl;

        // Использование begin() и end()
        cout << "Итерирование (begin() и end()): ";
        for (auto it = iterList.begin(); it != iterList.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;

        // Тест константных итераторов
        cout << "13. Тест константных итераторов" << endl;
        const LinkedList<int> constList = iterList;

        cout << "Константный список: " << constList << endl;
        cout << "Итерирование через константные итераторы: ";
        for (auto it = constList.cbegin(); it != constList.cend(); ++it) {
            cout << *it << " ";
        }
        cout << endl;

        cout << "Range-based for loop для константного списка: ";
        for (const auto& item : constList) {
            cout << item << " ";
        }
        cout << endl << endl;

        // Тест поиска через итераторы
        cout << "14. Тест findIter()" << endl;
        LinkedList<int> findList;
        findList.addToTail(10);
        findList.addToTail(20);
        findList.addToTail(30);
        findList.addToTail(40);
        findList.addToTail(50);
        cout << "Список для поиска: " << findList << endl;

        auto iter = findList.findIter(30);
        if (iter != findList.end()) {
            cout << "Найден элемент 30. Значение: " << *iter << endl;

            // Проверка декремента итератора
            --iter;
            cout << "Предыдущий элемент: " << *iter << endl;

            // Проверка инкремента
            ++iter; ++iter;
            cout << "Следующий за найденным: " << *iter << endl;
        }
        else {
            cout << "Элемент 30 не найден" << endl;
        }

        iter = findList.findIter(99);
        if (iter != findList.end()) {
            cout << "Найден элемент 99" << endl;
        }
        else {
            cout << "Элемент 99 не найден (возвращен end())" << endl;
        }
        cout << endl;

        // Тест добавления по итератору
        cout << "15. Тест add() по итератору" << endl;
        LinkedList<int> addList;
        addList.addToTail(1);
        addList.addToTail(3);
        addList.addToTail(5);
        cout << "Исходный список: " << addList << endl;

        // Добавление в начало
        auto addIter = addList.begin();
        addList.add(addIter, 0);
        cout << "После add(begin(), 0): " << addList << endl;

        // Добавление в конец
        addIter = addList.end();
        addList.add(addIter, 6);
        cout << "После add(end(), 6): " << addList << endl;

        // Добавление в середину
        addIter = addList.findIter(3);
        if (addIter != addList.end()) {
            addList.add(addIter, 2);
            cout << "После add(итератор_на_3, 2): " << addList << endl;
        }

        // Добавление после другого элемента
        addIter = addList.findIter(3);
        if (addIter != addList.end()) {
            ++addIter; // Переходим к следующему после 3
            addList.add(addIter, 4);
            cout << "После add(итератор_после_3, 4): " << addList << endl;
        }
        cout << endl;

        // Тест удаления по итератору
        cout << "16. Тест remove() по итератору" << endl;
        LinkedList<int> removeList;
        for (int i = 1; i <= 10; i++) {
            removeList.addToTail(i);
        }
        cout << "Исходный список: " << removeList << endl;

        // Удаление из начала
        auto removeIter = removeList.begin();
        removeList.remove(removeIter);
        cout << "После remove(begin()): " << removeList << endl;

        // Удаление из конца
        removeIter = removeList.end();
        --removeIter; // Переходим к последнему элементу
        removeList.remove(removeIter);
        cout << "После remove(end()-1): " << removeList << endl;

        // Удаление из середины
        removeIter = removeList.findIter(5);
        if (removeIter != removeList.end()) {
            removeList.remove(removeIter);
            cout << "После remove(итератор_на_5): " << removeList << endl;
        }

        // Удаление несуществующего элемента
        removeIter = removeList.findIter(99);
        removeList.remove(removeIter); // Ничего не должно произойти
        cout << "После попытки remove(несуществующий): " << removeList << endl << endl;

        // Тест удаления диапазона
        cout << "17. Тест remove() диапазона элементов" << endl;
        LinkedList<int> rangeList;
        for (int i = 1; i <= 10; i++) {
            rangeList.addToTail(i * 10);
        }
        cout << "Исходный список: " << rangeList << endl;

        // Удаление с начала до середины
        auto first = rangeList.begin();
        auto last = rangeList.begin();
        for (int i = 0; i < 3; i++) ++last;
        rangeList.remove(first, last);
        cout << "После remove(begin(), begin()+3): " << rangeList << endl;

        // Удаление с середины до конца
        first = rangeList.findIter(70);
        last = rangeList.end();
        rangeList.remove(first, last);
        cout << "После remove(итератор_на_70, end()): " << rangeList << endl;

        // Удаление одного элемента (диапазон из одного)
        first = rangeList.findIter(50);
        last = first;
        ++last;
        rangeList.remove(first, last);
        cout << "После remove(итератор_на_50, итератор_на_50+1): " << rangeList << endl;

        // Удаление всего списка
        rangeList.remove(rangeList.begin(), rangeList.end());
        cout << "После remove(begin(), end()): " << rangeList << " (пустой)" << endl << endl;

        // Тест сортировки
        cout << "18. Тест сортировки списка" << endl;
        LinkedList<int> sortList;

        // Случайный список
        sortList.addToTail(64);
        sortList.addToTail(34);
        sortList.addToTail(25);
        sortList.addToTail(12);
        sortList.addToTail(22);
        sortList.addToTail(11);
        sortList.addToTail(90);

        cout << "Исходный список: " << sortList << endl;

        sortList.sort();
        cout << "После sort(): " << sortList << endl;

        // Проверка сортировки по возрастанию
        bool isSorted = true;
        auto prev = sortList.begin();
        auto curr = sortList.begin();
        if (curr != sortList.end()) ++curr;

        while (curr != sortList.end()) {
            if (*prev > *curr) {
                isSorted = false;
                break;
            }
            ++prev;
            ++curr;
        }

        if (isSorted) {
            cout << "Список отсортирован по возрастанию" << endl;
        }
        else {
            cout << "Список не отсортирован корректно" << endl;
        }

        // Тест ввода/вывода
        cout << "20. Тест ввода/вывода" << endl;
        LinkedList<int> inputList;
        cout << "Введите список (сначала количество элементов, затем элементы):" << endl;
        cin >> inputList;
        cout << "Введенный список: " << inputList << endl;
        cout << "Размер: " << inputList.getSize() << endl;

        // Проверка сортировки введенного списка
        inputList.sort();
        cout << "Отсортированный список: " << inputList << endl << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка в программе: " << e.what() << endl;
        return 1;
    }

    return 0;
}