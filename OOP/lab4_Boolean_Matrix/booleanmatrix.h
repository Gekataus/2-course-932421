#include "dynamicarray.h"
#include "booleanvector.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>

class BooleanMatrix {

private:
    DynamicArray<BooleanVector> matrixData_;

public:
    // Конструкторы
    BooleanMatrix();
    BooleanMatrix(uint32_t rows, uint32_t cols, bool defaultValue = false);
    BooleanMatrix(const char** charMatrix, const uint32_t numRows);
    BooleanMatrix(const BooleanMatrix& other);

    // Присваивание
    BooleanMatrix& operator=(const BooleanMatrix& other);

    // Получение числа строк и столбцов
    uint32_t getRows() const;
    uint32_t getCols() const;

    // Установка в 0/1 i-ой компоненты j-ой строки
    void setBit(uint32_t row, uint32_t col, bool value);

    // Обмен содержимого с другой матрицей (swap)
    void swap(BooleanMatrix& other);

    // Вес матрицы (количество единичных компонент)
    uint32_t getWeight() const;

    // Конъюнкция всех строк (возвращает булев вектор)
    BooleanVector conjunctionAllRows() const;

    // Дизъюнкция всех строк (возвращает булев вектор)
    BooleanVector disjunctionAllRows() const;


    // Потоковый ввод/вывод
    friend std::istream& operator>>(std::istream& is, BooleanMatrix& bm);
    friend std::ostream& operator<<(std::ostream& os, const BooleanMatrix& bm);
};