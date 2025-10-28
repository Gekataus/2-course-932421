#pragma once
#pragma once
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

template<typename T>
class DynamicArray
{
public:
    //- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования) +
    DynamicArray();
    DynamicArray(int);
    DynamicArray(const DynamicArray<T>&);

    //- деструктор +
    ~DynamicArray();

    //Геттеры
    // Геттер для получения указателя на данные массива
    const T* getArrayData() const { return arrayData_; }

    //- получение размера (количества хранимых элементов в настоящий момент) +
    int getArrayLength() const { return arrayLength_; }

    // Геттер для получения элемента по индексу
    T getAt(int) const;

    //Сеттеры
    // Сеттер для установки длины массива
    void setArrayLength(int);
    // Сеттер для установки значения по индексу
    void setAt(int, const T&);

    //- обмен содержимого с другим массивом (swap) +
    void ArraysSwap(DynamicArray<T>&);

    // - поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет) +
    int findElement(const T&) const;

    //- сортировка элементов (пирамидальная) +
    void sift(int, int);
    void sort();

    //- вставка элемента по индексу.Если индекс некорректный, вернуть false +
    bool insertAt(const int, const T&);

    //- удаление элемента по индексу. Если индекс некорректный, вернуть false +
    bool removeAt(const int);

    //-удаление элемента по значению(первое вхождение).Если элемент отсутствует в массиве, вернуть false +
    bool removeFirstValue(const T&);

    //-удаление всех элементов с заданным значением +
    void removeAllValue(const T&);

    //поиск максимального / минимального элемента +
    T findMaxEl() const;
    T findMinEl() const;


    //Перегрузки:

    //- получение ссылки на элемент по индексу ([]) +
    T& operator[](const int index)
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    const T& operator[](const int index) const
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    //-присваивание копированием(=) +
    DynamicArray<T>& operator=(const DynamicArray<T>&);

    //- сложение(конкатенация) с другим массивом(здесь имеется в виду другим объектом нашего класса, а не стандартные массивы) (+ и +=) +
    DynamicArray<T> operator+(const DynamicArray<T>&) const;
    DynamicArray<T>& operator+=(const DynamicArray<T>&);

    //-сравнение(== и != ) +
    bool operator==(const DynamicArray<T>& other) const;
    bool operator!=(const DynamicArray<T>& other) const;

private:
    T* arrayData_;
    int arrayLength_;
};

//- ввод/вывод в консоль (потоковый) +
template<typename T>
istream& operator>>(istream& inputStream, DynamicArray<T>& input);

template<typename T>
ostream& operator<<(ostream& outputStream, const DynamicArray<T>& output);

// Реализация методов класса DynamicArray

//Конструктор по умолчанию
template<typename T>
DynamicArray<T>::DynamicArray()
    : arrayData_(nullptr), arrayLength_(0) {
}

//Конструктор из обычного массива
template<typename T>
DynamicArray<T>::DynamicArray(int initialLength) : arrayLength_(initialLength)
{
    arrayData_ = new T[initialLength];
    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[i] = T();
    }
}

//Конструктор копирования
template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& otherArray)
{
    if (otherArray.arrayLength_ == 0)
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    arrayLength_ = otherArray.arrayLength_;
    arrayData_ = new T[arrayLength_];

    for (int index = 0; index < arrayLength_; ++index)
    {
        arrayData_[index] = otherArray.arrayData_[index];
    }
}

//Деструктор
template<typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] arrayData_;
}

// Геттер для получения элемента по индексу
template<typename T>
T DynamicArray<T>::getAt(int index) const {
    if (index < 0 || index >= arrayLength_) {
        throw out_of_range("Index out of range");
    }
    return arrayData_[index];
}

// Сеттер для установки длины массива
template<typename T>
void DynamicArray<T>::setArrayLength(int newLength) {
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

    T* newData = new T[newLength];
    int elementsToCopy = min(arrayLength_, newLength);
    if (elementsToCopy > 0 && arrayData_ != nullptr) {
        for (int i = 0; i < elementsToCopy; ++i) {
            newData[i] = arrayData_[i];
        }
    }

    for (int i = elementsToCopy; i < newLength; ++i) {
        newData[i] = T();
    }

    delete[] arrayData_;
    arrayData_ = newData;
    arrayLength_ = newLength;
}

// Сеттер для установки значения по индексу
template<typename T>
void DynamicArray<T>::setAt(int index, const T& value) {
    if (index < 0 || index >= arrayLength_) {
        throw out_of_range("Индекс выходит за границы массива");
    }
    arrayData_[index] = value;
}

//- обмен содержимого с другим массивом (swap)
template<typename T>
void DynamicArray<T>::ArraysSwap(DynamicArray<T>& other)
{
    swap(arrayData_, other.arrayData_);
    swap(arrayLength_, other.arrayLength_);
}

// - поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет); 
template<typename T>
int DynamicArray<T>::findElement(const T& a) const
{
    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == a) return i;
    }

    return -1;
}

// Просеивание
template<typename T>
void DynamicArray<T>::sift(int n, int i) {
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
template<typename T>
void DynamicArray<T>::sort() {
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

//Вставка элемента по индексу
template<typename T>
bool DynamicArray<T>::insertAt(const int index, const T& value)
{
    if (index == 0 && arrayLength_ == 0)
    {
        arrayData_ = new T[1];
        arrayData_[0] = value;
        ++arrayLength_;
        return true;
    }

    if (index < 0 || index >= arrayLength_) return false;

    T* tempArrayData = new T[arrayLength_ + 1];

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

//- удаление элемента по индексу. Если индекс некорректный, вернуть false
template<typename T>
bool DynamicArray<T>::removeAt(const int index) {
    // Проверка корректности индекса
    if (index < 0 || index >= arrayLength_) {
        return false;
    }

    // Создаем новый массив на 1 элемент меньше
    T* newData = new T[arrayLength_ - 1];

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
template<typename T>
bool DynamicArray<T>::removeFirstValue(const T& value)
{
    int index = findElement(value);
    if (index == -1)
        return false;
    return removeAt(index);
}

//-удаление всех элементов с заданным значением
template<typename T>
void DynamicArray<T>::removeAllValue(const T& value)
{
    if (arrayLength_ == 0) return;

    int countToKeep = 0;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != value)
            ++countToKeep;
    //Нет таких элементов
    if (countToKeep == arrayLength_) return;

    T* tempArrayData = (countToKeep > 0) ? new T[countToKeep] : nullptr;

    int j = 0;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != value)
            tempArrayData[j++] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = tempArrayData;
    arrayLength_ = countToKeep;
}

//поиск максимального / минимального элемента
template<typename T>
T DynamicArray<T>::findMaxEl() const {
    assert(arrayLength_ > 0 && "Массив пуст");
    T maxVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] > maxVal)
            maxVal = arrayData_[i];
    return maxVal;
}

template<typename T>
T DynamicArray<T>::findMinEl() const {
    assert(arrayLength_ > 0 && "Массив пуст");
    T minVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; ++i)
        if (arrayData_[i] < minVal)
            minVal = arrayData_[i];
    return minVal;
}

//Перегрузка операции присвоения копированием
template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& otherArray)
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
            arrayData_ = new T[arrayLength_];

            for (int index = 0; index < arrayLength_; ++index)
            {
                arrayData_[index] = otherArray.arrayData_[index];
            }
        }
    }

    return *this;
}

// Перегрузка сложения (конкатенация) с другим массивом (+)
template<typename T>
DynamicArray<T> DynamicArray<T>::operator+(const DynamicArray<T>& other) const
{
    DynamicArray<T> result;
    result.arrayLength_ = arrayLength_ + other.arrayLength_;
    result.arrayData_ = new T[result.arrayLength_];

    for (int i = 0; i < arrayLength_; ++i)
        result.arrayData_[i] = arrayData_[i];

    for (int j = 0; j < other.arrayLength_; ++j)
        result.arrayData_[arrayLength_ + j] = other.arrayData_[j];

    return result;
}

// Перегрузка сложения (конкатенация) с другим массивом (+=)
template<typename T>
DynamicArray<T>& DynamicArray<T>::operator+=(const DynamicArray<T>& other)
{
    T* tempArrayData = new T[arrayLength_ + other.arrayLength_];

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
template<typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;
    for (int i = 0; i < arrayLength_; ++i)
        if (arrayData_[i] != other.arrayData_[i])
            return false;
    return true;
}

// Перегрузка сравнение (!=)
template<typename T>
bool DynamicArray<T>::operator!=(const DynamicArray<T>& other) const
{
    return !(*this == other);
}

// Перегрузка оператора ввода
template<typename T>
istream& operator>>(istream& inputStream, DynamicArray<T>& input)
{
    if (input.getArrayLength() != 0) {
        cout << "Введите данные для массива длинны " << input.getArrayLength() << ": ";
        for (int i = 0; i < input.getArrayLength(); ++i) {
            T value;
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
            T value;
            inputStream >> value;
            input.setAt(i, value);
        }
    }

    return inputStream;
}

// Перегрузка оператора вывода
template<typename T>
ostream& operator<<(ostream& outputStream, const DynamicArray<T>& output)
{
    int length = output.getArrayLength();
    outputStream << "[ ";
    for (int i = 0; i < length; ++i) {
        outputStream << output.getArrayData()[i] << " ";
    }
    outputStream << "]";

    return outputStream;
}