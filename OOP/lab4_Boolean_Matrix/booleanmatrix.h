#pragma once

#include <stdint.h>
#include <iostream>
#include "dynamicarray.h"
#include "booleanvector.h"

class BooleanMatrix
{
public:
    // Конструкторы
    BooleanMatrix() = default;  // Конструктор по умолчанию
    BooleanMatrix(const uint32_t numRows, const uint32_t numColumns, const bool initialValue = false); //С параметрами
    BooleanMatrix(const char** charMatrix, const uint32_t numRows); //из матрицы char
    BooleanMatrix(const BooleanMatrix&) = default;   // Конструктор копирования
   
    ~BooleanMatrix() = default;  // Деструктор

    //Геттеры
    uint32_t getNumRows() const; // Число строк
    uint32_t getNumColumns() const; // Число столбцов
    uint32_t getWeight() const; // Вес матрицы
    uint32_t getRowWeight(const uint32_t rowIndex) const; // Вес j-ой строки

    //Сеттеры
    void setBit(const uint32_t rowIndex, const uint32_t bitIndex, const bool value); // Установка в 0/1 i-ой компоненты j-ой строки;
    void setBits(const uint32_t rowIndex, const uint32_t startBitIndex, const uint32_t k, const bool value); // Установка в 0/1 k компонент j-ой строки, начиная с i-ой компоненты

    // Операции
    void swap(BooleanMatrix& other); //Обмен с другой матрицей
    BooleanVector conjunctionAllRows() const; // Конъюнкция всех строк
    BooleanVector disjunctionAllRows() const; // Дизъюнкция всех строк
    void invertBit(const uint32_t rowIndex, const uint32_t bitIndex); // Инверсия в i-ой компоненты j-ой строки
    void invertBits(const uint32_t rowIndex, const uint32_t startBitIndex, const uint32_t k); // Инверсия k компонент j-ой строки, начиная с i-ой компоненты;
    
    // Перегрузки операторов
    BooleanMatrix& operator=(const BooleanMatrix&) = default; // Оператор присваивания 
    BooleanVector& operator[](const uint32_t rowIndex); //Индексация
    const BooleanVector& operator[](const uint32_t rowIndex) const; //Индексация (констрантная)

    BooleanMatrix& operator&=(const BooleanMatrix& other); 
    BooleanMatrix& operator|=(const BooleanMatrix& other);
    BooleanMatrix& operator^=(const BooleanMatrix& other);

    BooleanMatrix operator&(const BooleanMatrix& other) const;
    BooleanMatrix operator|(const BooleanMatrix& other) const;
    BooleanMatrix operator^(const BooleanMatrix& other) const;

    BooleanMatrix operator~() const; // Построчная побитовая инверсия (~)

    void addRow(const BooleanVector& row);   // Добавление строк

private:
    DynamicArray<BooleanVector> matrixData_;
};

std::ostream& operator<<(std::ostream& os, const BooleanMatrix& matrix);
std::istream& operator>>(std::istream& is, BooleanMatrix& matrix);