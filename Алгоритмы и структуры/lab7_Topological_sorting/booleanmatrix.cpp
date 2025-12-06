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
// Вес j-ой строки
uint32_t BooleanMatrix::getRowWeight(uint32_t row) const {
    if (row >= getRows()) {
        throw out_of_range("Индекс столбца выходит за границы");
    }
    return matrixData_[row].getWeight();
}

// Инверсия в i-ой компоненты j-ой строки
void BooleanMatrix::invertBit(uint32_t row, uint32_t col) {
    if (row >= getRows() || col >= getCols()) {
        throw out_of_range("Индекс выходит за границы");
    }
    matrixData_[row].invertBit(col);
}

// Инверсия k компонент j-ой строки, начиная с i-ой компоненты
void BooleanMatrix::invertBits(uint32_t row, uint32_t startCol, uint32_t k) {
    if (row >= getRows() || startCol >= getCols()) {
        throw out_of_range("Индекс выходит за границы");
    }
    if (startCol + k > getCols()) {
        throw out_of_range("Слишком много битов для установки");
    }

    for (uint32_t i = 0; i < k; ++i) {
        matrixData_[row].invertBit(startCol + i);
    }
}

// Установка в 0/1 i-ой компоненты j-ой строки
void BooleanMatrix::setBit(uint32_t row, uint32_t col, bool value) {
    if (row >= getRows() || col >= getCols()) {
        throw out_of_range("Индекс выходит за границы");
    }
    matrixData_[row].setBit(col, value);
}

// Установка в 0/1 k компонент j-ой строки, начиная с i-ой компоненты
void BooleanMatrix::setBits(uint32_t row, uint32_t startCol, uint32_t k, bool value) {
    if (row >= getRows() || startCol >= getCols()) {
        throw out_of_range("Индекс выходит за границы");
    }
    if (startCol + k > getCols()) {
        throw out_of_range("Слишком много битов для установки");
    }

    for (uint32_t i = 0; i < k; ++i) {
        matrixData_[row].setBit(startCol + i, value);
    }
}

// Присваивание
BooleanMatrix& BooleanMatrix::operator=(const BooleanMatrix& other) {
    if (this != &other) {
        matrixData_ = other.matrixData_;
    }
    return *this;
}


// Получение строки
BooleanVector& BooleanMatrix::operator[](uint32_t row) {
    if (row >= getRows()) {
        throw out_of_range("Индекс столбца выходит за границы");
    }
    return matrixData_[row];
}

const BooleanVector& BooleanMatrix::operator[](uint32_t row) const {
    if (row >= getRows()) {
        throw out_of_range("Индекс столбца выходит за границы");
    }
    return matrixData_[row];
}

// Построчное побитовое умножение (&, &=)
BooleanMatrix BooleanMatrix::operator&(const BooleanMatrix& other) const {
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        throw invalid_argument("Матрицы имеют разный размер");
    }

    BooleanMatrix result(getRows(), getCols());
    for (uint32_t i = 0; i < getRows(); ++i) {
        result[i] = matrixData_[i] & other.matrixData_[i];
    }
    return result;
}

BooleanMatrix& BooleanMatrix::operator&=(const BooleanMatrix& other) {
    *this = *this & other;
    return *this;
}

// Построчное побитовое сложение (|, |=)
BooleanMatrix BooleanMatrix::operator|(const BooleanMatrix& other) const {
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        throw invalid_argument("Матрицы имеют разный размер");
    }

    BooleanMatrix result(getRows(), getCols());
    for (uint32_t i = 0; i < getRows(); ++i) {
        result[i] = matrixData_[i] | other.matrixData_[i];
    }
    return result;
}

BooleanMatrix& BooleanMatrix::operator|=(const BooleanMatrix& other) {
    *this = *this | other;
    return *this;
}

// Построчное побитовое исключающее ИЛИ (^, ^=)
BooleanMatrix BooleanMatrix::operator^(const BooleanMatrix& other) const {
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        throw invalid_argument("Матрицы имеют разный размер");
    }

    BooleanMatrix result(getRows(), getCols());
    for (uint32_t i = 0; i < getRows(); ++i) {
        result[i] = matrixData_[i] ^ other.matrixData_[i];
    }
    return result;
}

BooleanMatrix& BooleanMatrix::operator^=(const BooleanMatrix& other) {
    *this = *this ^ other;
    return *this;
}

// Построчная побитовая инверсия (~)
BooleanMatrix BooleanMatrix::operator~() const {
    BooleanMatrix result(getRows(), getCols());
    for (uint32_t i = 0; i < getRows(); ++i) {
        result[i] = ~matrixData_[i];
    }
    return result;
}

// Сравнение матриц
bool BooleanMatrix::operator==(const BooleanMatrix& other) const {
    if (getRows() != other.getRows() || getCols() != other.getCols()) {
        return false;
    }

    for (uint32_t i = 0; i < getRows(); ++i) {
        if (matrixData_[i].getLength() != other.matrixData_[i].getLength()) {
            return false;
        }
        for (uint32_t j = 0; j < getCols(); ++j) {
            if (matrixData_[i][j] != other.matrixData_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool BooleanMatrix::operator!=(const BooleanMatrix& other) const {
    return !(*this == other);
}


// Потоковый ввод
istream& operator>>(istream& is, BooleanMatrix& bm) {
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
ostream& operator<<(ostream& os, const BooleanMatrix& bm) {
    for (uint32_t i = 0; i < bm.getRows(); ++i) {
        os << bm[i] << endl;
    }
    return os;
}