#include <iostream>
#include "LinkedList.h"

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
        testAdd.addAtPosition(25, 2); // На позицию 2
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

            // Попытка доступа к несуществующему индексу
            // testIndex[10] = 100; // Бросит исключение
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

        // Проверка глубокого копирования
        assigned.addToTail(400);
        cout << "После добавления 400 в assigned:" << endl;
        cout << "original: " << original << endl;
        cout << "assigned: " << assigned << endl << endl;

        // Тест ввода/вывода
        cout << "10. Тест ввода/вывода" << endl;
        LinkedList<int> inputList;
        cout << "Введите элементы списка (разделенные пробелами, Enter для завершения): ";

        // Очищаем буфер
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cin >> inputList;
        cout << "Введенный список: " << inputList << endl;
        cout << "Размер: " << inputList.getSize() << endl << endl;

        // Тест очистки списка
        cout << "11. Тест очистки списка" << endl;
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

        // Тест на пустой список
        cout << "12. Тест работы с пустым списком" << endl;
        LinkedList<int> emptyList;

        cout << "isEmpty(): " << emptyList.isEmpty() << endl;
        cout << "removeFromHead(): " << (emptyList.removeFromHead() ? "успешно" : "не удалось") << endl;
        cout << "removeFromTail(): " << (emptyList.removeFromTail() ? "успешно" : "не удалось") << endl;

        try {
            int min = emptyList.findMin();
            cout << "Минимальный элемент: " << min << endl;
        }
        catch (const runtime_error& e) {
            cout << "Исключение при поиске min: " << e.what() << endl;
        }

        try {
            int max = emptyList.findMax();
            cout << "Максимальный элемент: " << max << endl;
        }
        catch (const runtime_error& e) {
            cout << "Исключение при поиске max: " << e.what() << endl;
        }

    }
    catch (const exception& e) {
        cout << "Ошибка в программе: " << e.what() << endl;
        return 1;
    }

    return 0;
}
