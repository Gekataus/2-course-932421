#include <cstring>
#include <iostream>
#include <stdexcept>
#include "booleanvector.h"

// Определения методов BooleanVector
BooleanVector::BooleanVector(const uint32 numBits, const bool initialValue)
    : numBits_(numBits), numBytes_((numBits + 7) / 8)
{
    if (numBytes_ > 0) {
        vectorData_ = new uint8[numBytes_];
        uint8 initialByteValue = initialValue ? 255 : 0;
        for (uint32 i = 0; i < numBytes_; i++) {
            vectorData_[i] = initialByteValue;
        }
    }
    else {
        vectorData_ = nullptr;
    }
}

BooleanVector::BooleanVector(const char* str)
{
    if (str == nullptr) {
        numBits_ = 0;
        vectorData_ = nullptr;
        numBytes_ = 0;
        return;
    }

    // Определяем длину строки
    uint32 length = 0;
    while (str[length] != '\0') length++;
    numBits_ = length;
    numBytes_ = (numBits_ + 7) / 8;

    if (numBytes_ > 0) {
        vectorData_ = new uint8[numBytes_];
        // Инициализируем нулями
        for (uint32 i = 0; i < numBytes_; i++) {
            vectorData_[i] = 0;
        }

        // Заполняем вектор из строки
        for (uint32 i = 0; i < numBits_; i++) {
            if (str[i] == '1') {
                uint32 byteIndex = i / 8;
                uint32 bitIndex = i % 8;
                vectorData_[byteIndex] |= (1 << bitIndex);
            }
        }
    }
    else {
        vectorData_ = nullptr;
    }
}

BooleanVector::BooleanVector(const BooleanVector& other)
    : numBits_(other.numBits_), numBytes_(other.numBytes_)
{
    if (other.vectorData_ != nullptr && numBytes_ > 0) {
        vectorData_ = new uint8[numBytes_];
        std::memcpy(vectorData_, other.vectorData_, numBytes_);
    }
    else {
        vectorData_ = nullptr;
    }
}

BooleanVector::~BooleanVector()
{
    delete[] vectorData_;
    vectorData_ = nullptr;
    numBits_ = 0;
    numBytes_ = 0;
}

BooleanVector& BooleanVector::operator=(const BooleanVector& other)
{
    if (this != &other) {
        delete[] vectorData_;

        numBits_ = other.numBits_;
        numBytes_ = other.numBytes_;

        if (other.vectorData_ != nullptr && numBytes_ > 0) {
            vectorData_ = new uint8[numBytes_];
            std::memcpy(vectorData_, other.vectorData_, numBytes_);
        }
        else {
            vectorData_ = nullptr;
        }
    }
    return *this;
}

BooleanVector& BooleanVector::operator=(BooleanVector&& other)
{
    if (this != &other) {
        delete[] vectorData_;

        vectorData_ = other.vectorData_;
        numBits_ = other.numBits_;
        numBytes_ = other.numBytes_;

        other.vectorData_ = nullptr;
        other.numBits_ = 0;
        other.numBytes_ = 0;
    }
    return *this;
}

uint32 BooleanVector::getWeight() const
{
    uint32 weight = 0;
    for (uint32 i = 0; i < numBits_; i++) {
        if ((*this)[i]) {
            weight++;
        }
    }
    return weight;
}

void BooleanVector::swap(BooleanVector& other)
{
    std::swap(vectorData_, other.vectorData_);
    std::swap(numBits_, other.numBits_);
    std::swap(numBytes_, other.numBytes_);
}

void BooleanVector::invert()
{
    for (uint32 i = 0; i < numBytes_; i++) {
        vectorData_[i] = ~vectorData_[i];
    }

    // Корректируем последний байт, если нужно
    if (numBits_ % 8 != 0) {
        uint8 mask = (1 << (numBits_ % 8)) - 1;
        vectorData_[numBytes_ - 1] &= mask;
    }
}

void BooleanVector::setBit(const uint32 index, const bool value)
{
    if (index >= numBits_)
        throw std::runtime_error("Индекс выходит за границы.");

    uint32 byteIndex = index / 8;
    uint32 bitIndex = index % 8;

    if (value) {
        vectorData_[byteIndex] |= (1 << bitIndex);
    }
    else {
        vectorData_[byteIndex] &= ~(1 << bitIndex);
    }
}

void BooleanVector::invertBit(const uint32 index)
{
    if (index >= numBits_)
        throw std::runtime_error("Индекс выходит за границы");

    uint32 byteIndex = index / 8;
    uint32 bitIndex = index % 8;

    // Инвертируем бит с помощью XOR
    vectorData_[byteIndex] ^= (1 << bitIndex);
}

BooleanVector BooleanVector::operator&(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) {
        throw std::runtime_error("Векторы имеют разную длину");
    }

    BooleanVector result(numBits_, false);
    for (uint32 i = 0; i < numBytes_; i++) {
        result.vectorData_[i] = vectorData_[i] & other.vectorData_[i];
    }
    return result;
}

BooleanVector BooleanVector::operator|(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) {
        throw std::runtime_error("Векторы имеют разную длниу");
    }

    BooleanVector result(numBits_, false);
    for (uint32 i = 0; i < numBytes_; i++) {
        result.vectorData_[i] = vectorData_[i] | other.vectorData_[i];
    }
    return result;
}

BooleanVector BooleanVector::operator^(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) {
        throw std::runtime_error("Векторы имеют разную длину");
    }

    BooleanVector result(numBits_, false);
    for (uint32 i = 0; i < numBytes_; i++) {
        result.vectorData_[i] = vectorData_[i] ^ other.vectorData_[i];
    }
    return result;
}

BooleanVector BooleanVector::operator~() const
{
    BooleanVector result(*this);
    result.invert();
    return result;
}

//Побитовые сдвиги
BooleanVector BooleanVector::operator<<(const uint32 shift) const
{
    if (shift == 0) {
        return BooleanVector(*this);  // Возвращаем копию
    }

    if (shift >= numBits_) {
        // Если сдвиг больше или равен длине - возвращаем нулевой вектор
        return BooleanVector(numBits_, false);
    }

    BooleanVector result(numBits_, false);

    // Выполняем сдвиг
    for (uint32 i = 0; i < numBits_ - shift; i++) {
        if ((*this)[i + shift]) {
            result.setBit(i, 1);
        }
    }

    return result;
}

BooleanVector BooleanVector::operator>>(const uint32 shift) const
{
    if (shift == 0) {
        return BooleanVector(*this);  // Возвращаем копию
    }

    if (shift >= numBits_) {
        // Если сдвиг больше или равен длине - возвращаем нулевой вектор
        return BooleanVector(numBits_, false);
    }

    BooleanVector result(numBits_, false);

    // Выполняем сдвиг
    for (uint32 i = shift; i < numBits_; i++) {
        if ((*this)[i - shift]) {
            result.setBit(i, 1);
        }
    }

    return result;
}

// ввод/вывод
std::ostream& operator<<(std::ostream& os, const BooleanVector& bv)
{
    for (uint32 i = 0; i < bv.numBits_; i++) {
        os << (bv[i] ? '1' : '0');
    }
    return os;
}

std::istream& operator>>(std::istream& is, BooleanVector& bv)
{
    std::string input;
    is >> input;

    // Очищаем текущие данные
    delete[] bv.vectorData_;

    bv.numBits_ = input.length();
    bv.numBytes_ = (bv.numBits_ + 7) / 8;

    if (bv.numBytes_ > 0) {
        bv.vectorData_ = new uint8[bv.numBytes_];
        // Инициализируем нулями
        for (uint32 i = 0; i < bv.numBytes_; i++) {
            bv.vectorData_[i] = 0;
        }

        for (uint32 i = 0; i < bv.numBits_; i++) {
            if (input[i] == '1') {
                bv.setBit(i, 1);
            }
            else if (input[i] == '0') {
                bv.setBit(i, 0);
            }
            else {
                throw std::runtime_error("Введён неверный символ (не 0 или 1)");
            }
        }
    }
    else {
        bv.vectorData_ = nullptr;
    }

    return is;
}

// Определения методов BitReference
BooleanVector::BitReference::BitReference(uint8* const bytePtr, const uint32 bitIndex)
    : bytePtr_(bytePtr), bitIndex_(bitIndex)
{
}

BooleanVector::BitReference& BooleanVector::BitReference::operator=(const bool value)
{
    uint8 mask = 1 << bitIndex_;

    if (value)
    {
        *bytePtr_ |= mask;
    }
    else
    {
        *bytePtr_ &= ~mask;
    }

    return *this;
}

BooleanVector::BitReference::operator bool() const { return *bytePtr_ & (1 << bitIndex_); }

// Индексация через BitReference (неконстантная версия)
BooleanVector::BitReference BooleanVector::operator[](const uint32 index)
{
    uint32 byteIndex = index / 8;
    uint32 bitIndex = index % 8;

    return BitReference(&vectorData_[byteIndex], bitIndex);
}

// Константная версия индексации
bool BooleanVector::operator[](const uint32 index) const
{
    uint32 byteIndex = index / 8;
    uint32 bitIndex = index % 8;

    return (vectorData_[byteIndex] >> bitIndex) & 1;
}