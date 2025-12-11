#pragma once

#include <iostream>
#include "booleanvector.h"

class CharSet : protected BooleanVector
{
public:
    // Конструкторы
    CharSet(); // По умолчанию
    CharSet(const char*); // Конструктор из массива
    CharSet(const CharSet&);  // Конструктор копирования

    // Деструктор
    ~CharSet() = default;

    //проверка наличия элемента в множестве
    bool contains(const char) const;

    //Получение мощности множества
    uint32 getCardinality() const;

    // Перегрузки
    CharSet& operator=(const CharSet&); // Присваивание
    CharSet operator|(const CharSet&) const; // Объединение
    CharSet operator&(const CharSet&) const; // Пересечение
    CharSet operator/(const CharSet&) const; // Разность
    CharSet operator~() const; // Дополнение
    CharSet operator+(const char) const; // Добавить элемент в множество
    CharSet operator-(const char) const; // Удалить элемент из множества
    bool operator==(const CharSet&) const; // Сравнение на равенство
    bool operator!=(const CharSet&) const; // Сравнение на неравенство

    // Индексация
    BitReference operator[](const uint32);
    bool operator[](const uint32) const;

    // Ввод/Вывод
    friend std::ostream& operator<<(std::ostream&, const CharSet&);
    friend std::istream& operator>>(std::istream&, CharSet&);
};