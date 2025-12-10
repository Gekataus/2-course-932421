#include <string.h>
#include "charset.h"

CharSet::CharSet() : BooleanVector(256, false) {}

CharSet::CharSet(const char* str) : BooleanVector(256, false)
{
    if (str == nullptr) return;

    size_t strLength = strlen(str);

    for (size_t idx = 0; idx < strLength; ++idx)
    {
        (*this)[str[idx]] = true;
    }
}

CharSet::CharSet(const CharSet& other) : BooleanVector(other) {}

bool CharSet::contains(const char element) const
{
    return (*this)[element];
}

uint32 CharSet::getCardinality() const
{
    return getWeight();
}

CharSet& CharSet::operator=(const CharSet& other)
{
    if (this != &other)
    {
        BooleanVector::operator=(other);
    }
    return *this;
}

CharSet CharSet::operator|(const CharSet& other) const
{
    CharSet result;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        result[idx] = (*this)[idx] || other[idx];
    }

    return result;
}

CharSet CharSet::operator&(const CharSet& other) const
{
    CharSet result;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        result[idx] = (*this)[idx] && other[idx];
    }

    return result;
}

CharSet CharSet::operator/(const CharSet& other) const
{
    CharSet result;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        result[idx] = (*this)[idx] && !other[idx];
    }

    return result;
}

CharSet CharSet::operator~() const
{
    CharSet result;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        result[idx] = !(*this)[idx];
    }

    return result;
}

CharSet CharSet::operator+(const char element) const
{
    CharSet result(*this);
    result[element] = true;

    return result;
}

CharSet CharSet::operator-(const char element) const
{
    CharSet result(*this);
    result[element] = false;

    return result;
}

bool CharSet::operator==(const CharSet& other) const
{
    for (uint32 idx = 0; idx < 256; ++idx)
    {
        if ((*this)[idx] != other[idx])
            return false;
    }
    return true;
}

bool CharSet::operator!=(const CharSet& other) const
{
    return !(*this == other);
}

BooleanVector::BitReference CharSet::operator[](const uint32 index)
{
    return BooleanVector::operator[](index);
}

bool CharSet::operator[](const uint32 index) const
{
    return BooleanVector::operator[](index);
}

std::ostream& operator<<(std::ostream& outputStream, const CharSet& charset)
{
    for (uint32 idx = 0; idx < 256; ++idx)
    {
        if (charset[idx])
        {
            outputStream << "'" << char(idx) << "', ";
        }
    }

    return outputStream;
}

std::istream& operator>>(std::istream& inputStream, CharSet& charset)
{
    std::string input;
    std::cout << "Введите строку символов для множества: ";
    if (inputStream >> input)
    {
        charset = CharSet(input.c_str());
    }
    return inputStream;
}