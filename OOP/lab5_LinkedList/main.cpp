#include <iostream>
#include "LinkedList.h"
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    try {

        cout << "1. Тест конструкторов:" << endl << endl;

        // Конструктор по умолчанию
        LinkedList<int> list1;
        cout << "Конструктор по умолчанию: " << list1 << endl;
        cout << "Размер: " << list1.getSize() << ", пустой: " << list1.isEmpty() << endl;

        // Конструктор из массива
        int arr[] = { 5, 3, 8, 1, 4 };
        LinkedList<int> list2(arr, 5);
        cout << "Конструктор из массива {5,3,8,1,4}: " << list2 << endl;
        cout << "Размер: " << list2.getSize() << endl;

        // Конструктор копирования
        LinkedList<int> list3(list2);
        cout << "Конструктор копирования: " << list3 << endl;
        cout << "list2 == list3: " << (list2 == list3) << endl << endl;


        cout << "2. тест добавления элементов:" << endl << endl;

        LinkedList<int> list4;

        // Добавление в голову
        list4.addToHead(10);
        list4.addToHead(20);
        list4.addToHead(30);
        cout << "После addToHead(10,20,30): " << list4 << endl;

        // Добавление в хвост
        list4.addToTail(40);
        list4.addToTail(50);
        cout << "После addToTail(40,50): " << list4 << endl;

        // Добавление на позицию
        list4.addAtPosition(25, 2);
        cout << "После addAtPosition(25, 2): " << list4 << endl;
        list4.addAtPosition(30, 0);
        cout << "После addAtPosition(30, 0): " << list4 << endl;
        list4.addAtPosition(15, list4.getSize());
        cout << "После addAtPosition(15, list4.getSize()): " << list4 << endl;
        list4.addAtPosition(55, list4.getSize() + 1);
        cout << "После addAtPosition(55, list4.getSize() + 1): " << list4 << endl;
        list4.addAtPosition(9, -2);
        cout << "После addAtPosition(9, -2): " << list4 << endl << endl;



        // Добавление после ключа
        int arr2[] = { 5, 3, 8, 1, 4 };
        LinkedList<int> listT(arr, 5);
        listT.addAfterKey(35, 30);
        cout << "После addAfterKey(35, 30): " << listT << endl;
        listT.addAfterKey(35, listT.getSize());
        cout << "После addAfterKey(35, listT.getSize()): " << listT << endl;
        listT.addAfterKey(35, -3);
        cout << "После addAfterKey(35, -3): " << listT << endl << endl;


        cout << "3. Тест удаления элементов:" << endl << endl;

        LinkedList<int> list5 = list4;
        cout << "Исходный список: " << list5 << endl;

        // Удаление из головы
        list5.removeFromHead();
        cout << "После removeFromHead(): " << list5 << endl;

        // Удаление из хвоста
        list5.removeFromTail();
        cout << "После removeFromTail(): " << list5 << endl;

        // Удаление по позиции
        list5.removeAtPosition(2);
        cout << "После removeAtPosition(2): " << list5 << endl;

        list5.removeAtPosition(list5.getSize());
        cout << "После removeAtPosition(list5.getSize()): " << list5 << endl;

        list5.removeAtPosition(0);
        cout << "После removeAtPosition(0): " << list5 << endl;

        list5.removeAtPosition(list5.getSize() - 1);
        cout << "После removeAtPosition(list5.getSize() - 1): " << list5 << endl;

        list5.removeAtPosition(-5);
        cout << "После removeAtPosition(-5): " << list5 << endl << endl;

        // Удаление по ключу
        list5.removeByKey(10);
        cout << "После removeByKey(10): " << list5 << endl;
        list5.removeByKey(100);
        cout << "После removeByKey(100): " << list5 << endl;
        list5.removeByKey(20);
        cout << "После removeByKey(20): " << list5 << endl;
        list5.removeByKey(40);
        cout << "После removeByKey(40): " << list5 << endl << endl;


        cout << "4. Тест поиска:" << endl << endl;

        LinkedList<int> list6;
        for (int i = 1; i <= 5; i++) {
            list6.addToTail(i * 10);
        }
        cout << "Список для поиска: " << list6 << endl;

        // Поиск через find()
        auto node = list6.find(30);
        cout << "find(30): " << (node ? "найден" : "не найден") << endl;

        node = list6.find(99);
        cout << "find(99): " << (node ? "найден" : "не найден") << endl;

        // Поиск через findIter()
        auto iter = list6.findIter(30);
        if (iter != list6.end()) {
            cout << "findIter(30): найден, значение = " << *iter << endl;
        }
        else {
            cout << "findIter(30): не найден" << endl;
        }

        iter = list6.findIter(99);
        if (iter != list6.end()) {
            cout << "findIter(99): найден" << endl;
        }
        else {
            cout << "findIter(99): не найден (возвращен end())" << endl;
        }

        // Поиск min/max
        cout << "Минимальный элемент: " << list6.findMin() << endl;
        cout << "Максимальный элемент: " << list6.findMax() << endl << endl;

        cout << "5. Тест итераторов:" << endl << endl;

        cout << "Итерация по списку: ";
        for (auto it = list6.begin(); it != list6.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;

        // Изменение через итератор
        for (auto it = list6.begin(); it != list6.end(); ++it) {
            *it = *it + 1;
        }
        cout << "После увеличения всех элементов на 1: " << list6 << endl;

        // Константные итераторы
        const LinkedList<int> constList = list6;
        cout << "Итерация по константному списку: ";
        for (auto it = constList.begin(); it != constList.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl << endl;


        cout << "6. Тест добавления по итератору:" << endl << endl;

        LinkedList<int> list7;
        list7.addToTail(10);
        list7.addToTail(30);
        list7.addToTail(50);
        cout << "Исходный список: " << list7 << endl;

        // Добавление в начало
        auto it7 = list7.begin();
        list7.add(it7, 5);
        cout << "После add(begin(), 5): " << list7 << endl;

        // Добавление в конец
        it7 = list7.end();
        list7.add(it7, 60);
        cout << "После add(end(), 60): " << list7 << endl;

        // Добавление в середину
        it7 = list7.findIter(30);
        if (it7 != list7.end()) {
            list7.add(it7, 25);
            cout << "После add(итератор_на_30, 25): " << list7 << endl;
        }
        cout << endl;

        cout << "7. Тест удаления по итератору:" << endl << endl;

        LinkedList<int> list8;
        for (int i = 1; i <= 5; i++) {
            list8.addToTail(i * 10);
        }
        cout << "Исходный список: " << list8 << endl;

        // Удаление из начала
        auto it8 = list8.begin();
        list8.remove(it8);
        cout << "После remove(begin()): " << list8 << endl;

        // Удаление из середины
        it8 = list8.findIter(30);
        if (it8 != list8.end()) {
            list8.remove(it8);
            cout << "После remove(итератор_на_30): " << list8 << endl;
        }

        // Попытка удаления end()
        it8 = list8.end();
        list8.remove(it8);
        cout << "После remove(end()): список не изменился: " << list8 << endl << endl;


        cout << "8. Тест удаления диапазона:" << endl << endl;

        LinkedList<int> list9;
        for (int i = 1; i <= 10; i++) {
            list9.addToTail(i);
        }
        cout << "Исходный список: " << list9 << endl;

        // Удаление первых 3 элементов
        auto first = list9.begin();
        auto last = list9.begin();
        for (int i = 0; i < 3; i++) ++last;
        list9.remove(first, last);
        cout << "После remove(begin(), begin()+3): " << list9 << endl;

        // Удаление с середины до конца
        first = list9.findIter(6);
        last = list9.end();
        list9.remove(first, last);
        cout << "После remove(итератор_на_6, end()): " << list9 << endl;

        // Удаление всего списка
        list9.remove(list9.begin(), list9.end());
        cout << "После remove(begin(), end()): " << list9 << " (пустой)" << endl << endl;

        // 9. Тест сортировки
        cout << "9. Тест сортировки:" << endl << endl;

        LinkedList<int> list10;
        list10.addToTail(64);
        list10.addToTail(34);
        list10.addToTail(25);
        list10.addToTail(12);
        list10.addToTail(22);
        list10.addToTail(11);
        list10.addToTail(90);

        cout << "Исходный список: " << list10 << endl;
        list10.sort();
        cout << "После sort(): " << list10 << endl;

        // Проверка сортированности
        bool sorted = true;
        auto prev = list10.begin();
        auto curr = list10.begin();
        if (curr != list10.end()) ++curr;

        while (curr != list10.end()) {
            if (*prev > *curr) {
                sorted = false;
                break;
            }
            ++prev;
            ++curr;
        }

        if (sorted) {
            cout << "Список отсортирован правильно" << endl;
        }
        else {
            cout << "Список не отсортирован" << endl;
        }
        cout << endl;


        cout << "10. Тест перегрузки операторов:" << endl << endl;

        // Оператор []
        LinkedList<int> list11;
        for (int i = 0; i < 5; i++) {
            list11.addToTail(i * 10);
        }
        cout << "Список: " << list11 << endl;
        cout << "list11[0] = " << list11[0] << endl;
        cout << "list11[2] = " << list11[2] << endl;
        cout << "list11[4] = " << list11[4] << endl;

        // Изменение через []
        list11[1] = 999;
        list11[3] = 888;
        cout << "После list11[1]=999, list11[3]=888: " << list11 << endl;

        // Проверка на выход за границы
        try {
            int val = list11[10];
            cout << "list11[10] = " << val << endl;
        }
        catch (const out_of_range& e) {
            cout << "Поймана ошибка при list11[10]: " << e.what() << endl;
        }

        // Оператор сравнения
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

        cout << "listA == listB: " << (listA == listB) << " (ожидается true)" << endl;
        cout << "listA == listC: " << (listA == listC) << " (ожидается false)" << endl;
        cout << "listA != listC: " << (listA != listC) << " (ожидается true)" << endl;

        // Оператор присваивания
        LinkedList<int> listD = listA;
        cout << "После присваивания listD = listA: " << listD << endl;
        cout << "listA == listD: " << (listA == listD) << " (ожидается true)" << endl;

        // Оператор конкатенации
        LinkedList<int> listE;
        listE.addToTail(1);
        listE.addToTail(2);

        LinkedList<int> listF;
        listF.addToTail(3);
        listF.addToTail(4);

        LinkedList<int> listG = listE + listF;
        cout << "listE + listF: " << listG << endl;

        listE += listF;
        cout << "listE += listF: " << listE << endl;
        cout << endl;


        cout << "11. Тест обмена списков:" << endl << endl;

        LinkedList<int> listH;
        listH.addToTail(1);
        listH.addToTail(2);
        listH.addToTail(3);

        LinkedList<int> listI;
        listI.addToTail(10);
        listI.addToTail(20);
        listI.addToTail(30);
        listI.addToTail(40);

        cout << "До swap:" << endl;
        cout << "listH: " << listH << " (размер: " << listH.getSize() << ")" << endl;
        cout << "listI: " << listI << " (размер: " << listI.getSize() << ")" << endl;

        listH.swap(listI);

        cout << "После swap:" << endl;
        cout << "listH: " << listH << " (размер: " << listH.getSize() << ")" << endl;
        cout << "listI: " << listI << " (размер: " << listI.getSize() << ")" << endl;
        cout << endl;

        // 12. Тест clear() и isEmpty()
        cout << "12. Тест очистки и проверки на пустоту" << endl << endl;

        LinkedList<int> listJ;
        listJ.addToTail(100);
        listJ.addToTail(200);
        listJ.addToTail(300);

        cout << "Исходный список: " << listJ << endl;
        cout << "isEmpty(): " << listJ.isEmpty() << " (ожидается false)" << endl;

        listJ.clear();
        cout << "После clear(): " << listJ << endl;
        cout << "isEmpty(): " << listJ.isEmpty() << " (ожидается true)" << endl;
        cout << "Размер: " << listJ.getSize() << " (ожидается 0)" << endl;
        cout << endl;

        cout << "13. Тест операторов ввода и вывода" << endl << endl;

        LinkedList<int> myList;

        cin >> myList;

        cout << "Вы ввели список: " << myList << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    return 0;
}