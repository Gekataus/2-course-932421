#pragma once
#include <assert.h>
#include <iostream>
using namespace std;

class DynamicArray
{
    public:
    //- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования) +
    DynamicArray();
    DynamicArray(int);
    DynamicArray(const DynamicArray&);

    //- деструктор +
    ~DynamicArray();


    //Геттеры
    // Геттер для получения указателя на данные массива
    const int* getArrayData() const {return arrayData_;}

    //- получение размера (количества хранимых элементов в настоящий момент) +
    int getArrayLength() const { return arrayLength_; }
    
    // Геттер для получения элемента по индексу с проверкой границ
    int getAt(int) const;


    //Сеттеры
    // Сеттер для установки длины массива
    void setArrayLength(int);
    // Сеттер для установки значения по индексу
    void setAt(int, int);


    //- обмен содержимого с другим массивом (swap) +
    void ArraysSwap(DynamicArray&);

    // - поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет) +
    int findElement(const int);

    //- сортировка элементов (пирамидальная) +
    void sift(int, int);
    void sort();

    //- вставка элемента по индексу.Если индекс некорректный, вернуть false +
    bool insertAt(const int, const int);

    //- удаление элемента по индексу. Если индекс некорректный, вернуть false +
    bool removeAt(const int);
    
    //-удаление элемента по значению(первое вхождение).Если элемент отсутствует в массиве, вернуть false +
    bool removeFirstValue(const int);

    //-удаление всех элементов с заданным значением +
    void removeAllValue(const int);

    //поиск максимального / минимального элемента +
    int findMaxEl() const;
    int findMinEl() const;
    

    //Перегрузки:
    
    //- получение ссылки на элемент по индексу ([]) +
    int& operator[](const int index)
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    const int& operator[](const int index) const
    {
        assert((index >= 0 && index < arrayLength_) && "Index is out of range.");
        return arrayData_[index];
    }

    //-присваивание копированием(=) +
    DynamicArray& operator=(const DynamicArray&);
        
    //- сложение(конкатенация) с другим массивом(здесь имеется в виду другим объектом нашего класса, а не стандартные массивы) (+ и +=) +
    DynamicArray operator+(const DynamicArray&) const;
    DynamicArray& operator+=(const DynamicArray&);
    
    //-сравнение(== и != ) +
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    private:

    int* arrayData_;
    int arrayLength_;
};

//- ввод/вывод в консоль (потоковый) +
istream& operator>>(istream& inputStream, DynamicArray& input);
ostream& operator<<(ostream& outputStream, const DynamicArray& output);