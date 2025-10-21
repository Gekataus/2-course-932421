#pragma once
#include <assert.h>

class DynamicArray
{
    //- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования) +
    DynamicArray();
    DynamicArray(int);
    DynamicArray(const DynamicArray&);

    //- конструктор перемещения +
    DynamicArray(DynamicArray&&);

    //- деструктор +
    ~DynamicArray();

    //- получение размера (количества хранимых элементов в настоящий момент);
    int ArrayLen() const;
    
    //- обмен содержимого с другим массивом (swap);
    void ArraySwap(DynamicArray&);

    // - поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
    int findElement(const int);

    //- ввод/вывод в консоль (потоковый);
    void input();
    void output() const;
    //- сортировка элементов (любым алгоритмом);
    void ArraySort();

    //- вставка элемента по индексу.Если индекс некорректный, вернуть false +
    bool insertAt(const int, const int);

    //- удаление элемента по индексу. Если индекс некорректный, вернуть false;
    bool removeAt(const int, const int);
    
    //- удаление элемента по значению (первое вхождение). Если элемент отсутствует в массиве, вернуть false;
    bool removeFirstValue(const int, const int);
    //- удаление всех элементов с заданным значением;
    bool removeAllValue(const int);

    //- поиск максимального/минимального элемента;
    int findMaxEl() const;
    int findMinEl() const;
    //- получение итераторов на начало/конец массива (методы должны называться begin и end. Метод end должен возвращать итератор не на последний элемент, а за позицию после него);

    //- вставка элемента перед итератором;
    
    //- удаление элемента или диапазона элементов с помощью итераторов.


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

    //-добавление элемента в конец массива(+и +=);


    //-присваивание перемещением(=(DynamicArray && other)) +
    DynamicArray& operator=(DynamicArray&&);
        
    //- сложение(конкатенация) с другим массивом(здесь имеется в виду другим объектом нашего класса, а не стандартные массивы) (+и += );
    //-сравнение(== и != ). 


    private:

    int* arrayData_;
    int arrayLength_;
};