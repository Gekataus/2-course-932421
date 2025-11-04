#include "booleanvector.h"

BooleanVector::BooleanVector(uint32_t size, bool value) : size_(size)
{
    if (size == 0) return;

    arraySize_ = calculateArraySize(size);
    data_ = new uint8_t[arraySize_];

    uint8_t pattern = value ? 0xFF : 0x00;
    for (uint32_t i = 0; i < arraySize_; ++i) {
        data_[i] = pattern;
    }

    // Обнуляем лишние биты в последнем байте
    if (size % 8 != 0) {
        uint8_t mask = (1 << (size % 8)) - 1;
        data_[arraySize_ - 1] &= mask;
    }
}

BooleanVector::BooleanVector(const char* bitString)
{
    if (bitString == nullptr) {
        throw std::invalid_argument("Null pointer passed to constructor");
    }

    size_ = strlen(bitString);
    if (size_ == 0) return;

    arraySize_ = calculateArraySize(size_);
    data_ = new uint8_t[arraySize_]();

    for (uint32_t i = 0; i < size_; ++i) {
        if (bitString[i] == '1') {
            setBitValue(i);
        }
        else if (bitString[i] != '0') {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            arraySize_ = 0;
            throw std::invalid_argument("String must contain only '0' and '1'");
        }
    }
}

BooleanVector::BooleanVector(const BooleanVector& other) :
    size_(other.size_), arraySize_(other.arraySize_)
{
    if (other.data_ != nullptr && arraySize_ > 0) {
        data_ = new uint8_t[arraySize_];
        memcpy(data_, other.data_, arraySize_);
    }
}

BooleanVector::~BooleanVector()
{
    delete[] data_;
}

uint32_t BooleanVector::length() const
{
    return size_;
}

uint32_t BooleanVector::calculateArraySize(uint32_t bitCount) const
{
    return (bitCount + 7) / 8;
}

void BooleanVector::clearBit(uint32_t index)
{
    data_[index / 8] &= ~(1 << (index % 8));
}

void BooleanVector::setBitValue(uint32_t index)
{
    data_[index / 8] |= (1 << (index % 8));
}

bool BooleanVector::getBit(uint32_t index) const
{
    return (data_[index / 8] >> (index % 8)) & 1;
}

void BooleanVector::swap(BooleanVector& other)
{
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(arraySize_, other.arraySize_);
}

void BooleanVector::invert()
{
    for (uint32_t i = 0; i < arraySize_; ++i) {
        data_[i] = ~data_[i];
    }

    // Корректируем последний байт, если нужно
    if (size_ % 8 != 0) {
        uint8_t mask = (1 << (size_ % 8)) - 1;
        data_[arraySize_ - 1] &= mask;
    }
}

void BooleanVector::setBit(uint32_t index, bool value)
{
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }

    if (value) {
        setBitValue(index);
    }
    else {
        clearBit(index);
    }
}

void BooleanVector::setZero(uint32_t index)
{
    setBit(index, false);
}

void BooleanVector::setOne(uint32_t index)
{
    setBit(index, true);
}

bool BooleanVector::operator[](uint32_t index) const
{
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return getBit(index);
}

BooleanVector BooleanVector::operator&(const BooleanVector& other) const
{
    if (size_ != other.size_) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    BooleanVector result(size_);
    for (uint32_t i = 0; i < arraySize_; ++i) {
        result.data_[i] = data_[i] & other.data_[i];
    }
    return result;
}

BooleanVector BooleanVector::operator|(const BooleanVector& other) const
{
    if (size_ != other.size_) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    BooleanVector result(size_);
    for (uint32_t i = 0; i < arraySize_; ++i) {
        result.data_[i] = data_[i] | other.data_[i];
    }
    return result;
}

BooleanVector BooleanVector::operator^(const BooleanVector& other) const
{
    if (size_ != other.size_) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    BooleanVector result(size_);
    for (uint32_t i = 0; i < arraySize_; ++i) {
        result.data_[i] = data_[i] ^ other.data_[i];
    }
    return result;
}

BooleanVector BooleanVector::operator~() const
{
    BooleanVector result(*this);
    result.invert();
    return result;
}

BooleanVector& BooleanVector::operator=(const BooleanVector& other)
{
    if (this != &other) {
        delete[] data_;

        size_ = other.size_;
        arraySize_ = other.arraySize_;

        if (other.data_ != nullptr && arraySize_ > 0) {
            data_ = new uint8_t[arraySize_];
            memcpy(data_, other.data_, arraySize_);
        }
        else {
            data_ = nullptr;
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const BooleanVector& vec)
{
    for (uint32_t i = 0; i < vec.length(); ++i) {
        os << (vec[i] ? '1' : '0');
    }
    return os;
}

std::istream& operator>>(std::istream& is, BooleanVector& vec)
{
    std::string input;
    is >> input;

    BooleanVector temp(input.c_str());
    vec = temp;
    return is;
}