#include "DynamicArray.h"
#include <iostream>

//Конструктор по умолчанию
DynamicArray::DynamicArray() : arrayData_(nullptr), arrayLength_(0)
{
    std::cout << "DynamicArray::DynamicArray()" << std::endl;
}

//Конструктор из обычного массива
DynamicArray::DynamicArray(int initialLength) : arrayLength_(initialLength)
{
    std::cout << "DynamicArray::DynamicArray(int)" << std::endl;

    arrayData_ = new int[initialLength];

    for (int i = 0; i < arrayLength_; i++)
    {
        arrayData_[0];
    }
}

//Конструктор копирования
DynamicArray::DynamicArray(const DynamicArray& otherArray)
{
    std::cout << "DynamicArray::DynamicArray(const DynamicArray&)" << std::endl;

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

//Конструктор перемещения
DynamicArray::DynamicArray(DynamicArray&& otherArray)
{
    std::cout << "DynamicArray::DynamicArray(DynamicArray&&)" << std::endl;

    arrayData_ = otherArray.arrayData_;
    arrayLength_ = otherArray.arrayLength_;
    otherArray.arrayData_ = nullptr;
    otherArray.arrayLength_ = 0;
}

//Деструктор
DynamicArray::~DynamicArray()
{
    std::cout << "DynamicArray::~DynamicArray()" << std::endl;

    delete[] arrayData_;
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
    std::cout << "DynamicArray::operator=(const DynamicArray&)" << std::endl;

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

//Перегрузка операции присвоения перемещением
DynamicArray& DynamicArray::operator=(DynamicArray&& otherArray)
{
    std::cout << "DynamicArray::operator=(DynamicArray&&)" << std::endl;

    if (this != &otherArray)
    {
        delete[] arrayData_;

        arrayData_ = otherArray.arrayData_;
        arrayLength_ = otherArray.arrayLength_;
        otherArray.arrayData_ = nullptr;
        otherArray.arrayLength_ = 0;
    }

    return *this;
}