#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    // Тест на коллизию
    HashTable table(5);

    table.insert(10, "Десять");
    table.insert(15, "Пятнадцать");
    table.insert(20, "Двадцать");
    table.insert(25, "Двадцать пять");

    table.printTableToConsole();
    cout << endl;

    // Проверка поиска
    cout << "Проверка поиска:" << endl;
    cout << "Ключ 10: " << (table.contains(10) ? "найден" : "не найден") << endl;
    cout << "Ключ 76: " << (table.contains(76) ? "найден" : "не найден") << endl << endl;

    // Удаление
    cout << "Удаление ключа 15:" << endl;
    table.erase(15);
    table.printTableToConsole();
    cout << endl;

    cout << "Проверка после удаления:" << endl;
    cout << "Ключ 15: " << (table.contains(15) ? "найден" : "не найден") << endl;
    cout << "Ключ 20: " << (table.contains(20) ? "найден" : "не найден") << endl << endl;

    // Конструктор копирования
    cout << "Конструктор копирования:" << endl;
    HashTable table2(table);
    cout << "Оригинал:" << endl;
    table.printTableToConsole();
    cout << "\nКопия:" << endl;
    table2.printTableToConsole();
    cout << endl;

    // Оператор присваивания
    cout << "Оператор присваивания:" << endl;
    HashTable table3;
    table3 = table;
    cout << "Таблица после присваивания:" << endl;
    table3.printTableToConsole();
    cout << endl;

    // Оператор []
    cout << "Оператор []:" << endl;
    HashTable table4;
    table4[100] = "Сто";
    table4[200] = "Двести";
    table4[300] = "Триста";
    table4.printTableToConsole();

    cout << "\nЧтение через operator[]:" << endl;
    cout << "table4[100] = " << table4[100] << endl;
    cout << "table4[200] = " << table4[200] << endl;

    cout << "\nОбновление через operator[]:" << endl;
    table4[200] = "ДВЕСТИ";
    cout << "table4[200] = " << table4[200] << endl;
    table4.printTableToConsole();
    cout << endl;

    // Swap
    cout << "Обмен содержимым (swap):" << endl;
    HashTable table5;
    table5.insert(1, "Один");
    table5.insert(2, "Два");

    HashTable table6;
    table6.insert(99, "Девяносто девять");

    cout << "До swap:" << endl;
    cout << "table5: " << endl;
    table5.printTableToConsole();
    cout << "table6: " << endl;
    table6.printTableToConsole();

    table5.swap(table6);

    cout << "\nПосле swap:" << endl;
    cout << "table5: " << endl;
    table5.printTableToConsole();
    cout << "table6: " << endl;
    table6.printTableToConsole();
    cout << endl;

    // Изменение размера
    cout << "Изменение размера таблицы:" << endl;
    HashTable table7(3);
    table7.insert(10, "Десять");
    table7.insert(20, "Двадцать");
    table7.insert(30, "Тридцать");
    cout << "До изменения размера (размер 3):" << endl;
    table7.printTableToConsole();

    table7.resize(10);
    cout << "\nПосле изменения размера (размер 10):" << endl;
    table7.printTableToConsole();
    cout << endl;

    // Замена хеш-функции
    cout << "Замена хеш-функции:" << endl;
    HashTable table8;
    table8.insert(10, "Десять");
    table8.insert(20, "Двадцать");
    table8.insert(30, "Тридцать");
    cout << "С первой хеш-функцией:" << endl;
    table8.printTableToConsole();

    table8.setHashFunction(new HashFunction2());
    cout << "\nСо второй хеш-функцией:" << endl;
    table8.printTableToConsole();
    cout << endl;

    return 0;
}