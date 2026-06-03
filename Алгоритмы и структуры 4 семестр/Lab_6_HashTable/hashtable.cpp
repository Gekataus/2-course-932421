#include <cmath>
#include <iostream>
#include "hashtable.h"

//HashFunction1
uint HashFunction1::hash(const uint key, const uint tableSize, const uint attempt) const
{
    const double a = (std::sqrt(5.0) - 1.0) / 2.0;

    if (attempt == 0)
    {
        uint h0 = key % tableSize;
        return uint(std::floor(double(h0) * a * double(tableSize))) % tableSize;
    }
    else
    {
        uint prevHash = hash(key, tableSize, attempt - 1);
        return uint(std::floor(double(prevHash) * a * double(tableSize))) % tableSize;
    }
}

IHashFunction* HashFunction1::clone() const
{
    return new HashFunction1();
}

//HashFunction2
uint HashFunction2::hash(const uint key, const uint tableSize, const uint attempt) const
{
    uint h0 = key % tableSize;
    uint step = 1 + (key % (tableSize - 2));
    return (h0 + attempt * step) % tableSize;
}

IHashFunction* HashFunction2::clone() const
{
    return new HashFunction2();
}

//HashTable

// Конструктор по умолчанию
HashTable::HashTable(const uint defaultTableSize)
{
    tableData_.resize(defaultTableSize);
    keysCount_ = 0;
    currentHashFunction_ = new HashFunction1();
}

// Конструктор копирования
HashTable::HashTable(const HashTable& other)
{
    tableData_.resize(other.tableData_.size());
    keysCount_ = 0;
    currentHashFunction_ = nullptr;
    copyFrom(other);
}

// Деструктор
HashTable::~HashTable()
{
    clearTable();
    delete currentHashFunction_;
}

// оператор присваивания
HashTable& HashTable::operator=(const HashTable& other)
{
    if (this != &other)
    {
        HashTable temp(other);
        swap(temp);
    }
    return *this;
}

// Обмен содержимым с другой таблицей(swap)
void HashTable::swap(HashTable& other)
{
    std::swap(tableData_, other.tableData_);
    std::swap(keysCount_, other.keysCount_);
    std::swap(currentHashFunction_, other.currentHashFunction_);
}

void HashTable::clearTable()
{
    for (size_t i = 0; i < tableData_.size(); i++)
    {
        KeyValuePair* cur = tableData_[i].head;
        while (cur)
        {
            KeyValuePair* next = cur->next;
            delete cur;
            cur = next;
        }
        tableData_[i].head = nullptr;
        tableData_[i].empty = true;
    }
    tableData_.clear();
    keysCount_ = 0;
}

void HashTable::copyFrom(const HashTable& other)
{
    clearTable();
    tableData_.resize(other.tableData_.size());
    keysCount_ = 0;

    if (other.currentHashFunction_)
    {
        currentHashFunction_ = other.currentHashFunction_->clone();
    }

    // Копируем все элементы из other в текущую таблицу
    for (size_t i = 0; i < other.tableData_.size(); i++)
    {
        if (!other.tableData_[i].empty)
        {
            KeyValuePair* srcNode = other.tableData_[i].head;
            KeyValuePair* tail = nullptr;

            while (srcNode)
            {
                // Создаём новый узел
                KeyValuePair* newNode = new KeyValuePair(srcNode->key, srcNode->value);

                if (!tableData_[i].head)
                {
                    // Первый узел в цепочке
                    tableData_[i].head = newNode;
                    tail = newNode;
                }
                else
                {
                    // Добавляем в конец цепочки
                    tail->next = newNode;
                    tail = newNode;
                }

                srcNode = srcNode->next;
            }
            tableData_[i].empty = false;
            // Увеличиваем счётчик на количество скопированных узлов
            KeyValuePair* countNode = tableData_[i].head;
            while (countNode)
            {
                ++keysCount_;
                countNode = countNode->next;
            }
        }
    }
}

uint HashTable::getHash(const uint key, const uint attempt) const
{
    return currentHashFunction_->hash(key, static_cast<uint>(tableData_.size()), attempt);
}

bool HashTable::findNode(const uint key, uint& bucketIndex, KeyValuePair** prev, KeyValuePair** found) const
{
    uint N = static_cast<uint>(tableData_.size());
    if (N == 0) return false;

    for (uint attempt = 0; attempt < N; ++attempt)
    {
        uint index = getHash(key, attempt);

        if (!tableData_[index].empty)
        {
            KeyValuePair* cur = tableData_[index].head;
            *prev = nullptr;

            while (cur)
            {
                if (cur->key == key)
                {
                    bucketIndex = index;
                    *found = cur;
                    return true;
                }
                *prev = cur;
                cur = cur->next;
            }
        }
    }

    *found = nullptr;
    return false;
}

// Добавление элемента с заданным ключом в таблицу
bool HashTable::insert(const uint key, const std::string& value)
{
    uint N = static_cast<uint>(tableData_.size());
    if (N == 0) return false;

    for (uint attempt = 0; attempt < N; ++attempt)
    {
        uint index = getHash(key, attempt);

        KeyValuePair* cur = tableData_[index].head;
        while (cur)
        {
            if (cur->key == key)
            {
                cur->value = value;
                return true;
            }
            cur = cur->next;
        }

        KeyValuePair* newNode = new KeyValuePair(key, value);
        newNode->next = tableData_[index].head;
        tableData_[index].head = newNode;
        tableData_[index].empty = false;
        ++keysCount_;
        return true;
    }

    return false;
}

// Удаление элемента из таблицы по ключу
bool HashTable::erase(const uint key)
{
    uint bucketIndex;
    KeyValuePair* prev = nullptr;
    KeyValuePair* found = nullptr;

    if (!findNode(key, bucketIndex, &prev, &found))
    {
        return false;
    }

    if (prev)
    {
        prev->next = found->next;
    }
    else
    {
        tableData_[bucketIndex].head = found->next;
    }

    delete found;
    --keysCount_;

    if (tableData_[bucketIndex].head == nullptr)
    {
        tableData_[bucketIndex].empty = true;
    }

    return true;
}

// Проверка наличия в таблице элемента с заданным ключом
bool HashTable::contains(const uint key) const
{
    uint dummyIndex;
    KeyValuePair* dummyPrev = nullptr;
    KeyValuePair* found = nullptr;
    return const_cast<HashTable*>(this)->findNode(key, dummyIndex, &dummyPrev, &found);
}

// Получение ссылки на значение по ключу (operator [])
std::string& HashTable::operator[](const uint key)
{
    uint N = static_cast<uint>(tableData_.size());
    if (N == 0)
    {
        resize(25);
        N = static_cast<uint>(tableData_.size());
    }

    for (uint attempt = 0; attempt < N; ++attempt)
    {
        uint index = getHash(key, attempt);

        KeyValuePair* cur = tableData_[index].head;
        while (cur)
        {
            if (cur->key == key)
            {
                return cur->value;
            }
            cur = cur->next;
        }

        KeyValuePair* newNode = new KeyValuePair(key, std::string());
        newNode->next = tableData_[index].head;
        tableData_[index].head = newNode;
        tableData_[index].empty = false;
        ++keysCount_;
        return tableData_[index].head->value;
    }

    static std::string dummy;
    return dummy;
}

// Вывод содержимого таблицы в консоль
void HashTable::printTableToConsole() const
{
    size_t tableSize = tableData_.size();

    for (size_t i = 0; i < tableSize; i++)
    {
        std::cout << i << ": ";

        if (!tableData_[i].empty)
        {
            KeyValuePair* cur = tableData_[i].head;
            bool first = true;

            while (cur)
            {
                if (!first)
                {
                    std::cout << " -> ";
                }
                std::cout << "(" << cur->key << ", \"" << cur->value << "\")";
                first = false;
                cur = cur->next;
            }
        }
        else
        {
            std::cout << "None";
        }

        std::cout << std::endl;
    }
}

// Замена хеш-функции (места для уже добавленных элементов должны быть пересчитаны)
void HashTable::setHashFunction(IHashFunction* newFunc)
{
    if (!newFunc) return;

    delete currentHashFunction_;
    currentHashFunction_ = newFunc;
    rehashAll();
}

// Изменение размера хеш-таблицы
void HashTable::resize(const uint newSize)
{
    if (newSize == 0 || newSize == tableData_.size()) return;

    std::vector<TableEntry> oldTable;
    oldTable.swap(tableData_);

    tableData_.resize(newSize);
    keysCount_ = 0;

    for (size_t i = 0; i < oldTable.size(); i++)
    {
        if (!oldTable[i].empty)
        {
            KeyValuePair* cur = oldTable[i].head;
            while (cur)
            {
                insert(cur->key, cur->value);
                cur = cur->next;
            }
        }
    }
}

void HashTable::rehashAll()
{
    std::vector<TableEntry> oldTable;
    oldTable.swap(tableData_);

    tableData_.resize(oldTable.size());
    keysCount_ = 0;

    for (size_t i = 0; i < oldTable.size(); i++)
    {
        if (!oldTable[i].empty)
        {
            KeyValuePair* cur = oldTable[i].head;
            while (cur)
            {
                insert(cur->key, cur->value);
                cur = cur->next;
            }
        }
    }
}