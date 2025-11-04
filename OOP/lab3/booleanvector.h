#pragma once
#include <stdint.h>
#include <iostream>
#include <cstring>
#include <stdexcept>

class BooleanVector
{
public:
    //- конструкторы (по умолчанию, с параметрами (размер и значение - одно и то же для всех разрядов),
    // конструктор из массива const char *, конструктор копирования);
    BooleanVector() = default; 
    BooleanVector(uint32_t size, bool value = false);
    BooleanVector(const char* bitString);
    BooleanVector(const BooleanVector& other);
    ~BooleanVector(); //- деструктор;

    uint32_t length() const; //- длина (количество бит) вектора;
    void swap(BooleanVector& other); //- обмен содержимого с другим вектором (swap);

    void invert();
    void setBit(uint32_t index, bool value);
    void setZero(uint32_t index);
    void setOne(uint32_t index);


    // Операторы
    bool operator[](uint32_t index) const;
    BooleanVector operator&(const BooleanVector& other) const;
    BooleanVector operator|(const BooleanVector& other) const;
    BooleanVector operator^(const BooleanVector& other) const;
    BooleanVector operator~() const;
    BooleanVector& operator=(const BooleanVector& other);

private:
    uint8_t* data_ = nullptr;
    uint32_t size_ = 0;
    uint32_t arraySize_ = 0;

    uint32_t calculateArraySize(uint32_t bitCount) const;
    void clearBit(uint32_t index);
    void setBitValue(uint32_t index);
    bool getBit(uint32_t index) const;
};

std::ostream& operator<<(std::ostream& os, const BooleanVector& vec);
std::istream& operator>>(std::istream& is, BooleanVector& vec);