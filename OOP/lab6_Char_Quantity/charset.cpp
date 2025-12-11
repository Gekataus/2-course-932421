#include <string.h>
#include "charset.h"

CharSet::CharSet() : BooleanVector(256, false) {}

// Конструктор из массива
CharSet::CharSet(const char* str) : BooleanVector(256, false)
{
    size_t strLength = strlen(str);

    for (size_t idx = 0; idx < strLength; ++idx)
    {
        (*this)[str[idx]] = true;
    }
}

// Конструктор копирования
CharSet::CharSet(const CharSet& other) : BooleanVector(other) {}

//проверка наличия элемента в множестве
bool CharSet::contains(const char element) const
{
    return (*this)[element];
}

//Получение мощности множества
uint32 CharSet::getCardinality() const
{
    return getWeight();
}

// Присваивание
CharSet& CharSet::operator=(const CharSet& other)
{
    if (this != &other)
    {
        BooleanVector::operator=(other);
    }
    return *this;
}

// Объединение
CharSet CharSet::operator|(const CharSet& other) const
{
    CharSet result;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        result[idx] = (*this)[idx] || other[idx];
    }

    return result;
}

// Пересечение
CharSet CharSet::operator&(const CharSet& other) const
{
    CharSet result;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        result[idx] = (*this)[idx] && other[idx];
    }

    return result;
}

// Разность
CharSet CharSet::operator/(const CharSet& other) const
{
    CharSet result;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        result[idx] = (*this)[idx] && !other[idx];
    }

    return result;
}

// Дополнение
CharSet CharSet::operator~() const
{
    CharSet result;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        result[idx] = !(*this)[idx];
    }

    return result;
}

// Добавить элемент в множество
CharSet CharSet::operator+(const char element) const
{
    CharSet result(*this);
    result[element] = true;

    return result;
}

// Удалить элемент из множества
CharSet CharSet::operator-(const char element) const
{
    CharSet result(*this);
    result[element] = false;

    return result;
}

// Сравнение на равенство
bool CharSet::operator==(const CharSet& other) const
{
    for (uint32 idx = 0; idx < 256; ++idx)
    {
        if ((*this)[idx] != other[idx])
            return false;
    }
    return true;
}

// Сравнение на неравенство
bool CharSet::operator!=(const CharSet& other) const
{
    return !(*this == other);
}

// Индексация
BooleanVector::BitReference CharSet::operator[](const uint32 index)
{
    return BooleanVector::operator[](index);
}

bool CharSet::operator[](const uint32 index) const
{
    return BooleanVector::operator[](index);
}

// Вывод
std::ostream& operator<<(std::ostream& outputStream, const CharSet& charSet)
{
    outputStream << "[ ";
    bool firstElement = true;

    for (uint32 idx = 0; idx < 256; ++idx)
    {
        if (charSet[idx])
        {
            if (!firstElement)
            {
                outputStream << ", ";
            }
            outputStream << "'" << char(idx) << "'";
            firstElement = false;
        }
    }
    outputStream << " ]";

    return outputStream;
}

// Ввод
std::istream& operator>>(std::istream& inputStream, CharSet& charset)
{
    std::string input;
    if (inputStream >> input)
    {
        // Создаем временный объект CharSet
        CharSet temp;

        // Добавляем каждый символ строки
        for (char ch : input)
        {
            temp[ch] = true;
        }

        // Присваиваем результат
        charset = temp;
    }
    return inputStream;
}