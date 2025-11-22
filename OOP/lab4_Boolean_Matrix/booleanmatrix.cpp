#include "booleanmatrix.h"

using namespace std;

// Конструктор по умолчанию
BooleanMatrix::BooleanMatrix() = default;

// Конструктор с параметрами (количество строк/столбцов и значения разрядов)
BooleanMatrix::BooleanMatrix(uint32_t rows, uint32_t cols, bool defaultValue) {
    for (uint32_t i = 0; i < rows; ++i) {
        matrixData_.insertAt(i, BooleanVector(cols, defaultValue));
    }
}

// Конструктор из матрицы char
BooleanMatrix::BooleanMatrix(const char** charMatrix, const uint32_t numRows)
{
    for (uint32_t rowIndex = 0; rowIndex < numRows; ++rowIndex)
    {
        matrixData_.insert(BooleanVector(charMatrix[rowIndex]));
    }
}

// Конструктор копирования
BooleanMatrix::BooleanMatrix(const BooleanMatrix& other) : matrixData_(other.matrixData_) {}

// Получение числа строк
uint32_t BooleanMatrix::getRows() const {
    return matrixData_.getArrayLength();
}

// Получение числа столбцов
uint32_t BooleanMatrix::getCols() const {
    if (getRows() == 0) return 0;
    return matrixData_[0].getLength();
}

// Обмен содержимого с другой матрицей (swap)
void BooleanMatrix::swap(BooleanMatrix& other) {
    matrixData_.ArraysSwap(other.matrixData_);
}

// Вес матрицы (количество единичных компонент)
uint32_t BooleanMatrix::getWeight() const {
    uint32_t totalWeight = 0;
    for (uint32_t i = 0; i < getRows(); ++i) {
        totalWeight += matrixData_[i].getWeight();
    }
    return totalWeight;
}

// Конъюнкция всех строк (возвращает булев вектор)
BooleanVector BooleanMatrix::conjunctionAllRows() const {
    if (getRows() == 0) return BooleanVector();

    BooleanVector result = matrixData_[0];
    for (uint32_t i = 1; i < getRows(); ++i) {
        result = result & matrixData_[i];
    }
    return result;
}

// Дизъюнкция всех строк (возвращает булев вектор)
BooleanVector BooleanMatrix::disjunctionAllRows() const {
    if (getRows() == 0) return BooleanVector();

    BooleanVector result = matrixData_[0];
    for (uint32_t i = 1; i < getRows(); ++i) {
        result = result | matrixData_[i];
    }
    return result;
}

// Установка в 0/1 i-ой компоненты j-ой строки
void BooleanMatrix::setBit(uint32_t row, uint32_t col, bool value) {
    if (row >= getRows() || col >= getCols()) {
        throw out_of_range("Индекс выходит за границы");
    }
    matrixData_[row].setBit(col, value);
}

// Присваивание
BooleanMatrix& BooleanMatrix::operator=(const BooleanMatrix& other) {
    if (this != &other) {
        matrixData_ = other.matrixData_;
    }
    return *this;
}



// Потоковый ввод
std::istream& operator>>(std::istream& is, BooleanMatrix& bm) {
    uint32_t rows, cols;
    cout << "Введите количество строк: ";
    is >> rows;
    cout << "Введите количество столбцов: ";
    is >> cols;

    // Создаем временную матрицу
    BooleanMatrix temp(rows, cols);

    cout << "Введите матрицу (0/1 построчно, " << cols << " символов в строке):" << endl;
    for (uint32_t i = 0; i < rows; ++i) {
        string rowString;
        is >> rowString;

        if (rowString.length() != cols) {
            throw runtime_error("Неверная длина строки матрицы");
        }

        for (uint32_t j = 0; j < cols; ++j) {
            if (rowString[j] == '1') {
                temp.setBit(i, j, true);
            }
            else if (rowString[j] == '0') {
                temp.setBit(i, j, false);
            }
            else {
                throw runtime_error("Неверный символ в матрице (должны быть только 0 или 1)");
            }
        }
    }

    bm = temp;
    return is;
}

// Потоковый вывод
std::ostream& operator<<(std::ostream& os, const BooleanMatrix& bm) {
    for (uint32_t i = 0; i < bm.getRows(); ++i) {
        os << bm.matrixData_[i] << endl;
    }
    return os;
}