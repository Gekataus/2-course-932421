#include "DynamicArray.h"
#include <iostream>

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
    std::cout << "DynamicArray::~DynamicArray()" << std::endl;

    delete[] arrayData_;
}

//- обмен содержимого с другим массивом (swap)
void DynamicArray::ArraysSwap(DynamicArray& other)
{
    std::swap(arrayData_, other.arrayData_);
    std::swap(arrayLength_, other.arrayLength_);
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

std::istream& operator>>(std::istream& inputStream, DynamicArray& input)
{
    for (int i = 0; i < input.ArrayLenght(); ++i)
    {

    }


    return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const DynamicArray& output)
{
    for (int i = 0; i < output.ArrayLenght(); ++i)
    {

    }


    return outputStream;
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