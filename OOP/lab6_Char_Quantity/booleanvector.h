#pragma once

#include <stdint.h>
#include <iostream>

using uint8 = uint8_t;
using uint32 = uint32_t;

class BooleanVector
{
protected:
    class BitReference;

public:
    BooleanVector() = default; //Конструктор по умолчанию
    BooleanVector(const uint32, const bool); //Конструктор с параметрами
    BooleanVector(const char*); //конструктор из массива const char*
    ~BooleanVector(); //Декструктор

    BooleanVector(const BooleanVector&); //Конструктор копирования
    
    BooleanVector& operator=(const BooleanVector&); 
    BooleanVector& operator=(BooleanVector&&);

    uint32 getLength() const { return numBits_; } //Длина вектора
    uint32 getWeight() const; //Вес вектора
    void swap(BooleanVector& other); // обмен с другим вектором
    void invert(); //инверсия всех компонент вектора
    void setBit(const uint32 index, const bool value); //установка в 0/1 i-ой компоненты
    void invertBit(const uint32 index);  // Инверсия i-ой компоненты

    // Индексация
    BitReference operator[](const uint32 index);
    bool operator[](const uint32 index) const;

    // Побитовые операции
    BooleanVector operator&(const BooleanVector& other) const; //Побитовое умножение
    BooleanVector operator|(const BooleanVector& other) const; //Побитовое сложение
    BooleanVector operator^(const BooleanVector& other) const; //Побитовое исключающее ИЛИ
    BooleanVector operator~() const; //Побитовая инверсия

    // Побитовые сдвиги
    BooleanVector operator<<(const uint32 shift) const; //Сдвиг влево
    BooleanVector operator>>(const uint32 shift) const; //Сдвиг вправо

    // Потоковый ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const BooleanVector& bv);
    friend std::istream& operator>>(std::istream& is, BooleanVector& bv);

protected:
    uint8* vectorData_ = nullptr;
    uint32 numBits_ = 0;
    uint32 numBytes_ = 0;
};

// Класс для работы с отдельными битами
class BooleanVector::BitReference
{
public:
    BitReference() = default;
    BitReference(uint8* const bytePtr, const uint32 bitIndex);
    ~BitReference() = default;

    BooleanVector::BitReference& operator=(const bool value);

    operator bool() const;

private:
    uint8* bytePtr_ = nullptr;
    uint32 bitIndex_ = 0;
};