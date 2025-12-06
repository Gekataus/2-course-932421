#pragma once

#include "dynamicarray.h"
#include "booleanvector.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>

class BooleanMatrix {
public:
    // Конструкторы
    BooleanMatrix();
    BooleanMatrix(uint32_t rows, uint32_t cols, bool defaultValue = false);
    BooleanMatrix(const char**, const uint32_t);
    BooleanMatrix(const BooleanMatrix&);

    // Деструктор
    ~BooleanMatrix() = default;

    // Получение числа строк и столбцов
    uint32_t getRows() const;
    uint32_t getCols() const;

    // Обмен содержимого с другой матрицей (swap)
    void swap(BooleanMatrix&);

    // Вес матрицы (количество единичных компонент)
    uint32_t getWeight() const;

    // Конъюнкция всех строк (возвращает булев вектор)
    BooleanVector conjunctionAllRows() const;

    // Дизъюнкция всех строк (возвращает булев вектор)
    BooleanVector disjunctionAllRows() const;

    // Вес j-ой строки
    uint32_t getRowWeight(uint32_t) const;

    // Инверсия в i-ой компоненты j-ой строки
    void invertBit(uint32_t, uint32_t);

    //инверсия k компонент j - ой строки, начиная с i - ой компоненты
    void invertBits(uint32_t, uint32_t, uint32_t);

    // Установка в 0/1 i-ой компоненты j-ой строки
    void setBit(uint32_t, uint32_t, bool);

    //установка в 0/1 k компонент j-ой строки, начиная с i-ой компоненты
    void setBits(uint32_t, uint32_t, uint32_t, bool);

    // Присваивание
    BooleanMatrix& operator=(const BooleanMatrix&);

    // Получение строки
    BooleanVector& operator[](uint32_t);
    const BooleanVector& operator[](uint32_t) const;

    // Построчное побитовое умножение (&,&=)
    BooleanMatrix operator&(const BooleanMatrix&) const;
    BooleanMatrix& operator&=(const BooleanMatrix&);


    // Построчное побитовое сложение (|,|=)
    BooleanMatrix operator|(const BooleanMatrix&) const;
    BooleanMatrix& operator|=(const BooleanMatrix&);

    // Построчное побитовое исключающее ИЛИ (^,^=)
    BooleanMatrix operator^(const BooleanMatrix&) const;
    BooleanMatrix& operator^=(const BooleanMatrix&);

    // Построчная побитовая инверсия (~)
    BooleanMatrix operator~() const;

    // Сравнение матриц
    bool operator==(const BooleanMatrix&) const;
    bool operator!=(const BooleanMatrix&) const;


private:
    DynamicArray<BooleanVector> matrixData_;

};

// Потоковый ввод/вывод
std::istream& operator>>(std::istream& is, BooleanMatrix& bm);
std::ostream& operator<<(std::ostream& os, const BooleanMatrix& bm);