#include "DynamicArray.h"
#include <iostream>
#include <vector>
using namespace std;

//Конструктор по умолчанию
DynamicArray::DynamicArray() 
    : arrayData_(nullptr), arrayLength_(0) {}

//Конструктор из обычного массива
DynamicArray::DynamicArray(int initialLength) : arrayLength_(initialLength)
{

    arrayData_ = new int[initialLength];

    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[i] = 0;
    }
}

//Конструктор копирования
DynamicArray::DynamicArray(const DynamicArray& otherArray)
{

    if (otherArray.arrayLength_ == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;

        return;
    }

    arrayLength_ = otherArray.arrayLength_;
    arrayData_ = new int[arrayLength_];

    for (int index = 0; index < arrayLength_; ++index)
    {
        arrayData_[index] = otherArray.arrayData_[index];
    }
}

//Деструктор
DynamicArray::~DynamicArray()
{
    delete[] arrayData_;
}

//- обмен содержимого с другим массивом (swap)
void DynamicArray::ArraysSwap(DynamicArray& other)
{
    swap(arrayData_, other.arrayData_);
    swap(arrayLength_, other.arrayLength_);
}

// - поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет); 
int DynamicArray::findElement(const int a)
{
    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == a) return i;
    }
    
    return -1;
}

// Геттер для получения элемента по индексу с проверкой границ
int DynamicArray::getAt(int index) const {
    if (index < 0 || index >= arrayLength_) {
        throw out_of_range("Index out of range");
    }
    return arrayData_[index];
}

//Вставка элемента по индексу
bool DynamicArray::insertAt(const int index, const int value)
{
    if (index == 0 && arrayLength_ == 0)
    {
        arrayData_ = new int[1];

        arrayData_[0] = value;

        ++arrayLength_;

        return true;
    }

    if (index < 0 || index >= arrayLength_) return false;

    int* tempArrayData = new int[arrayLength_ + 1];

    for (int curIdx = 0; curIdx < index; ++curIdx)
    {
        tempArrayData[curIdx] = arrayData_[curIdx];
    }

    for (int curIdx = index; curIdx < arrayLength_; ++curIdx)
    {
        tempArrayData[curIdx + 1] = arrayData_[curIdx];
    }

    tempArrayData[index] = value;

    ++arrayLength_;

    delete[] arrayData_;

    arrayData_ = tempArrayData;

    return true;
}
//Перегрузка операции присвоения копированием
DynamicArray& DynamicArray::operator=(const DynamicArray& otherArray)
{
    if (this != &otherArray)
    {
        delete[] arrayData_;

        if (otherArray.arrayLength_ == 0)
        {
            arrayData_ = nullptr;
            arrayLength_ = 0;
        }
        else
        {
            arrayLength_ = otherArray.arrayLength_;
            arrayData_ = new int[arrayLength_];

            for (int index = 0; index < arrayLength_; ++index)
            {
                arrayData_[index] = otherArray.arrayData_[index];
            }
        }
    }

    return *this;
}

// Сеттер для установки длины массива
void DynamicArray::setArrayLength(int newLength) {
    if (newLength < 0) {
        cout << "Длина не может быть отрицательной, установлена длина 1";
        newLength = 1;
    }

    if (newLength == arrayLength_) {
        return;
    }

    if (newLength == 0) {
        delete[] arrayData_;
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    int* newData = new int[newLength];
    int elementsToCopy = min(arrayLength_, newLength);
    if (elementsToCopy > 0 && arrayData_ != nullptr) {
        copy(arrayData_, arrayData_ + elementsToCopy, newData);
    }

    for (int i = elementsToCopy; i < newLength; ++i) {
        newData[i] = 0;
    }

    delete[] arrayData_;
    arrayData_ = newData;
    arrayLength_ = newLength;
}

// Сеттер для установки значения по индексу
void DynamicArray::setAt(int index, int value) {
        if (index < 0 || index >= arrayLength_) {
            throw out_of_range("Индекс выходит за границы массива");
        }
        arrayData_[index] = value;
    }

// Перегрузка оператора ввода
istream& operator>>(istream& inputStream, DynamicArray& input)
{
    if (input.getArrayLength() != 0) {
        cout << "Введите данные для массива длинны " << input.getArrayLength() << ": ";
        for (int i = 0; i < input.getArrayLength(); ++i) {
            int value;
            inputStream >> value;
            input.setAt(i, value);
        }
    }
    else {
        int length;
        cout << "Введите длинну массива: ";
        inputStream >> length;

        input.setArrayLength(length);

        cout << "Введите данные: ";
        for (int i = 0; i < length; ++i) {
            int value;
            inputStream >> value;
            input.setAt(i, value);
        }
    }

    return inputStream;
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& outputStream, const DynamicArray& output)
{
    int length = output.getArrayLength();
    outputStream << "[ ";
    for (int i = 0; i < length; ++i) {
        outputStream << output.getArrayData()[i] << " ";
    }
    outputStream << "]";

    return outputStream;
}

// Просеивание
void DynamicArray::sift(int n, int i) {
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arrayData_[left] > arrayData_[max])
        max = left;

    if (right < n && arrayData_[right] > arrayData_[max])
        max = right;

    if (max != i) {
        swap(arrayData_[i], arrayData_[max]);
        sift(n, max);
    }
}
//Сортировка
void DynamicArray::sort() {
    int n = arrayLength_;

    // Построение пирамиды
    for (int i = n / 2 - 1; i >= 0; i--)
        sift(n, i);
    // Извлечение элементов из пирамиды
    for (int i = n - 1; i > 0; i--) {
        swap(arrayData_[0], arrayData_[i]);
        sift(i, 0);
    }
}

//- удаление элемента по индексу. Если индекс некорректный, вернуть false
bool DynamicArray::removeAt(const int index) {
    // Проверка корректности индекса
    if (index < 0 || index >= arrayLength_) {
        return false;
    }

    // Создаем новый массив на 1 элемент меньше
    int* newData = new int[arrayLength_ - 1];

    // Копируем элементы до удаляемого индекса
    for (int i = 0; i < index; ++i) {
        newData[i] = arrayData_[i];
    }

    // Копируем элементы после удаляемого индекса
    for (int i = index + 1; i < arrayLength_; ++i) {
        newData[i - 1] = arrayData_[i];
    }

    // Освобождаем старую память и обновляем указатель
    delete[] arrayData_;
    arrayData_ = newData;
    arrayLength_--;

    return true;
}

//- Удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false
bool DynamicArray::removeFirstValue(const int value)
{
    int index = findElement(value);
    if (index == -1)
        return false;
    return removeAt(index);
}

//-удаление всех элементов с заданным значением
void DynamicArray::removeAllValue(const int value)
{
    if (arrayLength_ == 0) return;

    int countToKeep = 0;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != value)
            ++countToKeep;
    //Нет таких элементов
    if (countToKeep == arrayLength_) return;

    int* tempArrayData = (countToKeep > 0) ? new int[countToKeep] : nullptr;

    int j = 0;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != value)
            tempArrayData[j++] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_ = countToKeep;
}

//поиск максимального / минимального элемента
int DynamicArray::findMaxEl() const {
    assert(arrayLength_ > 0 && "Массив пуст");
    int maxVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] > maxVal)
            maxVal = arrayData_[i];
    return maxVal;
}

int DynamicArray::findMinEl() const {
    assert(arrayLength_ > 0 && "Массив пуст");
    int minVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] < minVal)
            minVal = arrayData_[i];
    return minVal;
}

// Перегрузка сложения (конкатенация) с другим массивом (+)
DynamicArray DynamicArray::operator+(const DynamicArray& other) const
{
    DynamicArray result;
    result.arrayLength_ = arrayLength_ + other.arrayLength_;
    result.arrayData_ = new int[result.arrayLength_];

    for (int i = 0; i < arrayLength_; ++i)
        result.arrayData_[i] = arrayData_[i];

    for (int j = 0; j < other.arrayLength_; ++j)
        result.arrayData_[arrayLength_ + j] = other.arrayData_[j];

    return result;
}

// Перегрузка сложения (конкатенация) с другим массивом (+=)
DynamicArray& DynamicArray::operator+=(const DynamicArray& other)
{
    int* tempArrayData = new int[arrayLength_ + other.arrayLength_];

    for (int i = 0; i < arrayLength_; ++i)
        tempArrayData[i] = arrayData_[i];

    for (int j = 0; j < other.arrayLength_; ++j)
        tempArrayData[arrayLength_ + j] = other.arrayData_[j];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_ += other.arrayLength_;

    return *this;
}

//  Перегрузка сравнение (==)
bool DynamicArray::operator==(const DynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != other.arrayData_[i])
            return false;
    return true;
}

// Перегрузка сравнение (!=)
bool DynamicArray::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}