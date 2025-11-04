#include <stdexcept>
#include <cstring>
#include <iostream>
#include "booleanvector.h"

BooleanVector::BooleanVector(const uint32_t numBits, const bool initialValue)
    : numBits_(numBits)
{
    allocateMemory(numBits);

    uint8_t initialByteValue = initialValue ? 255 : 0;
    for (uint32_t i = 0; i < numBytes_; i++) {
        vectorData_[i] = initialByteValue;
    }

    // Обнуляем лишние биты в последнем байте
    if (numBits_ % 8 != 0) {
        uint8_t mask = (1 << (numBits_ % 8)) - 1;
        vectorData_[numBytes_ - 1] &= mask;
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
    uint32_t length = 0;
    while (str[length] != '\0') length++;
    numBits_ = length;
    allocateMemory(numBits_);

    // Заполняем вектор из строки
    for (uint32_t i = 0; i < numBits_; i++) {
        if (str[i] == '1') {
            uint32_t byteIndex = i / 8;
            uint32_t bitIndex = i % 8;
            vectorData_[byteIndex] |= (1 << bitIndex);
        }
    }
}

BooleanVector::BooleanVector(const BooleanVector& other)
    : numBits_(other.numBits_), numBytes_(other.numBytes_)
{
    if (other.vectorData_ != nullptr) {
        vectorData_ = new uint8_t[numBytes_];
        std::memcpy(vectorData_, other.vectorData_, numBytes_);
    }
}
void BooleanVector::clearMemory()
{
    delete[] vectorData_;
    vectorData_ = nullptr;
    numBits_ = 0;
    numBytes_ = 0;
}

void BooleanVector::allocateMemory(const uint32_t numBits)
{
    numBytes_ = (numBits + 7) / 8;
    if (numBytes_ > 0) {
        vectorData_ = new uint8_t[numBytes_];
        // Инициализируем нулями
        for (uint32_t i = 0; i < numBytes_; i++) {
            vectorData_[i] = 0;
        }
    }
}

BooleanVector::~BooleanVector()
{
    clearMemory();
}

BooleanVector& BooleanVector::operator=(const BooleanVector& other)
{
    if (this != &other) {
        clearMemory();
        numBits_ = other.numBits_;
        numBytes_ = other.numBytes_;
        if (other.vectorData_ != nullptr) {
            vectorData_ = new uint8_t[numBytes_];
            std::memcpy(vectorData_, other.vectorData_, numBytes_);
        }
    }
    return *this;
}

BooleanVector& BooleanVector::operator=(BooleanVector&& other)
{
    if (this != &other) {
        clearMemory();
        vectorData_ = other.vectorData_;
        numBits_ = other.numBits_;
        numBytes_ = other.numBytes_;
        other.vectorData_ = nullptr;
        other.numBits_ = 0;
        other.numBytes_ = 0;
    }
    return *this;
}

bool BooleanVector::operator[](const uint32_t index) const {
    if (index >= numBits_)
        throw std::runtime_error("Индекс выходит за границы.");

    uint32_t byteIndex = index / 8;
    uint32_t bitIndex = index % 8;

    return (vectorData_[byteIndex] >> bitIndex) & 1;
}

uint32_t BooleanVector::getWeight() const
{
    uint32_t weight = 0;
    for (uint32_t i = 0; i < numBits_; i++) {
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
    for (uint32_t i = 0; i < numBytes_; i++) {
        vectorData_[i] = ~vectorData_[i];
    }

    // Корректируем последний байт, если нужно
    if (numBits_ % 8 != 0) {
        uint8_t mask = (1 << (numBits_ % 8)) - 1;
        vectorData_[numBytes_ - 1] &= mask;
    }
}

void BooleanVector::setBit(const uint32_t index, const bool value)
{
    if (index >= numBits_)
        throw std::runtime_error("Индекс выходит за границы.");

    uint32_t byteIndex = index / 8;
    uint32_t bitIndex = index % 8;

    if (value) {
        vectorData_[byteIndex] |= (1 << bitIndex);
    }
    else {
        vectorData_[byteIndex] &= ~(1 << bitIndex);
    }
}

void BooleanVector::setZero(const uint32_t index)
{
    setBit(index, false);
}

void BooleanVector::setOne(const uint32_t index)
{
    setBit(index, true);
}

void BooleanVector::invertBit(const uint32_t index)
{
    if (index >= numBits_)
        throw std::runtime_error("Индекс выходит за границы");

    uint32_t byteIndex = index / 8;
    uint32_t bitIndex = index % 8;

    // Инвертируем бит с помощью XOR
    vectorData_[byteIndex] ^= (1 << bitIndex);
}

BooleanVector BooleanVector::operator&(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) {
        throw std::runtime_error("Векторы имеют разную длину");
    }

    BooleanVector result(numBits_, false);
    for (uint32_t i = 0; i < numBytes_; i++) {
        result.vectorData_[i] = vectorData_[i] & other.vectorData_[i];
    }
    return result;
}

BooleanVector BooleanVector::operator|(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) {
        throw std::runtime_error("Векторы имеют разную длниу!");
    }

    BooleanVector result(numBits_, false);
    for (uint32_t i = 0; i < numBytes_; i++) {
        result.vectorData_[i] = vectorData_[i] | other.vectorData_[i];
    }
    return result;
}

BooleanVector BooleanVector::operator^(const BooleanVector& other) const
{
    if (numBits_ != other.numBits_) {
        throw std::runtime_error("Векторы имеют разную длину!");
    }

    BooleanVector result(numBits_, false);
    for (uint32_t i = 0; i < numBytes_; i++) {
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

BooleanVector BooleanVector::operator<<(const uint32_t shift) const
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
    for (uint32_t i = shift; i < numBits_; i++) {
        if ((*this)[i - shift]) {
            result.setOne(i);
        }
    }

    return result;
}

BooleanVector BooleanVector::operator>>(const uint32_t shift) const
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
    for (uint32_t i = 0; i < numBits_ - shift; i++) {
        if ((*this)[i + shift]) {
            result.setOne(i);
        }
    }

    return result;
}


// ввод/вывод
std::ostream& operator<<(std::ostream& os, const BooleanVector& bv)
{
    for (uint32_t i = 0; i < bv.numBits_; i++) {
        os << (bv[i] ? '1' : '0');
    }
    return os;
}

std::istream& operator>>(std::istream& is, BooleanVector& bv)
{
    std::string input;
    is >> input;

    bv.clearMemory();
    bv.numBits_ = input.length();
    bv.allocateMemory(bv.numBits_);

    for (uint32_t i = 0; i < bv.numBits_; i++) {
        if (input[i] == '1') {
            bv.setOne(i);
        }
        else if (input[i] == '0') {
            bv.setZero(i);
        }
        else {
            throw std::runtime_error("Введён неверный символ (не 0 или 1)!");
        }
    }

    return is;
}

/* BitReference
BooleanVector::BitReference::BitReference(uint8_t* const bytePtr, const uint8_t bitIndex)
    : bytePtr_(bytePtr), bitIndex_(bitIndex) {
}

BooleanVector::BitReference::operator bool()
{
    return (*bytePtr_ >> bitIndex_) & 1;
}

BooleanVector::BitReference& BooleanVector::BitReference::operator=(const bool NewValue)
{
    if (NewValue) {
        *bytePtr_ |= (1 << bitIndex_);
    }
    else {
        *bytePtr_ &= ~(1 << bitIndex_);
    }
    return *this;
}

*/