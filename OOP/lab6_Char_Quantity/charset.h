#pragma once

#include <iostream>
#include "booleanvector.h"

class CharSet : protected BooleanVector
{
public:
    // Конструкторы
    CharSet();
    CharSet(const char*);
    CharSet(const CharSet&);  // Конструктор копирования

    // Деструктор
    ~CharSet() = default;

    // Методы
    bool contains(const char) const;
    uint32 getCardinality() const;

    // Оператор присваивания
    CharSet& operator=(const CharSet&);

    // Операции с множествами
    CharSet operator|(const CharSet&) const;
    CharSet operator&(const CharSet&) const;
    CharSet operator/(const CharSet&) const;
    CharSet operator~() const;
    CharSet operator+(const char) const;
    CharSet operator-(const char) const;

    // Операторы сравнения
    bool operator==(const CharSet&) const;
    bool operator!=(const CharSet&) const;

    // Индексация
    BitReference operator[](const uint32);
    bool operator[](const uint32) const;

    // Дружественные функции
    friend std::ostream& operator<<(std::ostream&, const CharSet&);
    friend std::istream& operator>>(std::istream&, CharSet&);
};

std::ostream& operator<<(std::ostream&, const CharSet&);
std::istream& operator>>(std::istream&, CharSet&);