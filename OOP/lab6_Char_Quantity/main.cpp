#include "charset.h"
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // 1. Тестирование конструкторов
    cout << "1. Тестирование конструкторов:\n";
    CharSet emptySet;
    cout << "Конструктор по умолчанию: " << emptySet << endl;

    CharSet set1("Hello");
    cout << "Множество set1 из 'Hello': " << set1 << endl;

    CharSet set2("World");
    cout << "Множество set2 из 'World': " << set2 << endl;

    CharSet set3(set1);
    cout << "Копия set1: " << set3 << endl;

    // 2. Тестирование методов contains() и getCardinality()
    cout << "\n2. Тестирование методов:\n";
    cout << "set1 содержит 'H': " << (set1.contains('H') ? "да" : "нет") << endl;
    cout << "set1 содержит 'h': " << (set1.contains('h') ? "да" : "нет") << endl;
    cout << "set1 содержит 'x': " << (set1.contains('x') ? "да" : "нет") << endl;
    cout << "Мощность set1: " << set1.getCardinality() << endl;
    cout << "Мощность set2: " << set2.getCardinality() << endl;

    // 3. Тестирование перегрузки операций
    cout << "\n3. Тестирование перегрузки операций:\n";
    CharSet set4;
    set4 = set1;
    cout << "set4 = set1: " << set4 << endl;

    // 4. Тестирование операторов
    cout << "\n4. Тестирование операторов:\n";
    CharSet unionSet = set1 | set2;
    cout << "Объединение set1 | set2: " << unionSet << endl;

    CharSet intersectSet = set1 & set2;
    cout << "Пересечение set1 & set2: " << intersectSet << endl;

    CharSet diffSet = set1 / set2;
    cout << "Разность set1 / set2: " << diffSet << endl;

    CharSet set1Copy("Hello");
    cout << "set1 == set1Copy: " << (set1 == set1Copy ? "да" : "нет") << endl;
    cout << "set1 != set2: " << (set1 != set2 ? "да" : "нет") << endl;

    CharSet abSet("ab");
    CharSet complement = ~abSet;
    cout << "Множество 'ab': " << abSet << endl;
    cout << "Дополнение ~abSet: мощность = " << complement.getCardinality() << endl << endl;

    
    CharSet set5("abc");
    cout << "Исходное множество: " << set5 << endl;
    CharSet setPlus = set5 + 'd';
    cout << "set5 + 'd': " << setPlus << endl;
    CharSet setMinus = set5 - 'b';
    cout << "set5 - 'b': " << setMinus << endl;

    CharSet setincluded("abcdefg");
    cout << "Исходное множество: " << setincluded << endl;
    CharSet setincludedPlus = setincluded + 'd';
    cout << "setincluded + 'd': " << setPlus << endl;
    CharSet setincludedMinus = setincluded - 'q';
    cout << "setincluded - 'q': " << setPlus << endl;


    // 5. Тестирование ввода
    cout << "\n5. Тестирование ввода\n";
    CharSet userSet;
    cout << "Введите строку для множества: ";
    cin >> userSet;
    cout << "Ваше множество: " << userSet << endl;

    return 0;
}