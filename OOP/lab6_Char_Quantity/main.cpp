#include "charset.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    // 1. Тестирование конструкторов
    std::cout << "1. Тестирование конструкторов:\n";
    CharSet emptySet;
    std::cout << "   - Пустое множество: " << emptySet << std::endl;

    CharSet set1("Hello");
    std::cout << "   - Множество из 'Hello': " << set1 << std::endl;

    CharSet set2("World");
    std::cout << "   - Множество из 'World': " << set2 << std::endl;

    CharSet set3(set1);
    std::cout << "   - Копия set1: " << set3 << std::endl;

    // 2. Тестирование методов contains() и getCardinality()
    std::cout << "\n2. Тестирование методов:\n";
    std::cout << "   - set1 содержит 'H': " << (set1.contains('H') ? "да" : "нет") << std::endl;
    std::cout << "   - set1 содержит 'h': " << (set1.contains('h') ? "да" : "нет") << std::endl;
    std::cout << "   - set1 содержит 'x': " << (set1.contains('x') ? "да" : "нет") << std::endl;
    std::cout << "   - Мощность set1: " << set1.getCardinality() << std::endl;
    std::cout << "   - Мощность set2: " << set2.getCardinality() << std::endl;

    // 3. Тестирование операторов сравнения
    std::cout << "\n3. Тестирование операторов сравнения:\n";
    CharSet set1Copy("Hello");
    std::cout << "   - set1 == set1Copy: " << (set1 == set1Copy ? "да" : "нет") << std::endl;
    std::cout << "   - set1 != set2: " << (set1 != set2 ? "да" : "нет") << std::endl;

    // 4. Тестирование оператора присваивания
    std::cout << "\n4. Тестирование оператора присваивания:\n";
    CharSet set4;
    set4 = set1;
    std::cout << "   - set4 = set1: " << set4 << std::endl;
    std::cout << "   - set4 == set1: " << (set4 == set1 ? "да" : "нет") << std::endl;

    // 5. Тестирование операций с множествами
    std::cout << "\n5. Тестирование операций с множествами:\n";
    CharSet unionSet = set1 | set2;
    std::cout << "   - Объединение set1 | set2: " << unionSet << std::endl;

    CharSet intersectSet = set1 & set2;
    std::cout << "   - Пересечение set1 & set2: " << intersectSet << std::endl;

    CharSet diffSet = set1 / set2;
    std::cout << "   - Разность set1 / set2: " << diffSet << std::endl;

    // 6. Тестирование унарной операции дополнения
    std::cout << "\n6. Тестирование дополнения:\n";
    CharSet smallSet("ab");
    CharSet complement = ~smallSet;
    std::cout << "   - Множество 'ab': " << smallSet << std::endl;
    std::cout << "   - Дополнение ~smallSet: мощность = " << complement.getCardinality() << std::endl;

    // 7. Тестирование операций с элементами
    std::cout << "\n7. Тестирование операций с элементами:\n";
    CharSet set5("abc");
    std::cout << "   - Исходное множество: " << set5 << std::endl;

    CharSet setPlus = set5 + 'd';
    std::cout << "   - set5 + 'd': " << setPlus << std::endl;

    CharSet setMinus = set5 - 'b';
    std::cout << "   - set5 - 'b': " << setMinus << std::endl;

    // 8. Тестирование комплексных операций
    std::cout << "\n8. Тестирование комплексных операций:\n";
    CharSet vowels("aeiou");
    CharSet word("hello");

    std::cout << "   - Гласные: " << vowels << std::endl;
    std::cout << "   - Слово 'hello': " << word << std::endl;
    std::cout << "   - Гласные в слове: " << (word & vowels) << std::endl;
    std::cout << "   - Согласные в слове: " << (word / vowels) << std::endl;

    // 9. Тестирование свойств множеств
    std::cout << "\n9. Тестирование свойств:\n";
    CharSet A("abc");
    CharSet B("bcd");
    CharSet C("cde");

    // Ассоциативность объединения
    CharSet unionAB = (A | B) | C;
    CharSet unionBC = A | (B | C);
    std::cout << "   - Ассоциативность (A|B)|C == A|(B|C): "
        << (unionAB == unionBC ? "да" : "нет") << std::endl;

    // Идемпотентность
    std::cout << "   - Идемпотентность A|A == A: " << ((A | A) == A ? "да" : "нет") << std::endl;
    std::cout << "   - Идемпотентность A&A == A: " << ((A & A) == A ? "да" : "нет") << std::endl;

    // 10. Тестирование ввода
    std::cout << "\n10. Тестирование ввода\n";
    CharSet userSet;
    std::cout << "   Введите строку для множества: ";
    std::cin >> userSet;
    std::cout << "   Вы ввели: " << userSet << std::endl;

    // 11. Тест пустого множества
    std::cout << "\n11. Тест пустого множества:\n";
    CharSet empty;
    std::cout << "   - Пустое множество: " << empty << std::endl;
    std::cout << "   - Мощность пустого множества: " << empty.getCardinality() << std::endl;
    std::cout << "   - empty | set1 == set1: " << ((empty | set1) == set1 ? "да" : "нет") << std::endl;
    std::cout << "   - empty & set1 == empty: " << ((empty & set1) == empty ? "да" : "нет") << std::endl;

    return 0;
}