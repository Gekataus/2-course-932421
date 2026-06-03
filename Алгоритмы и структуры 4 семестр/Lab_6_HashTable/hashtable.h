#pragma once

#include <string>
#include <vector>

using uint = unsigned int;

class IHashFunction
{
public:
    virtual uint hash(const uint key, const uint tableSize, const uint attempt) const = 0;
    virtual IHashFunction* clone() const = 0;
    virtual ~IHashFunction() = default;
};

// Первая хеш-функция: hi(K) = [hi-1(K) × a × N] mod N; a = (√5 - 1)/2
class HashFunction1 : public IHashFunction
{
public:
    virtual uint hash(const uint key, const uint tableSize, const uint attempt) const override;
    virtual IHashFunction* clone() const override;
};

// Вторая хеш-функция: hi(K) = ((K mod N) + i × (1 + K mod (N-2))) mod N
class HashFunction2 : public IHashFunction
{
public:
    virtual uint hash(const uint key, const uint tableSize, const uint attempt) const override;
    virtual IHashFunction* clone() const override;
};

class HashTable
{
public:
    // Конструктор по умолчанию
    HashTable(const uint = 25);

    // Конструктор копирования
    HashTable(const HashTable& other);

    // Деструктор
    ~HashTable();

    // Оператор присваивания
    HashTable& operator=(const HashTable& other);

    // Добавление элемента с заданным ключом в таблицу
    bool insert(const uint, const std::string&);

    // Удаление элемента из таблицы по ключу
    bool erase(const uint);

    // Проверка наличия в таблице элемента с заданным ключом
    bool contains(const uint) const;

    // Получение ссылки на значение по ключу (operator [])
    std::string& operator[](const uint);

    // Обмен содержимым с другой таблицей (swap)
    void swap(HashTable& other);

    // Вывод содержимого таблицы в консоль
    void printTableToConsole() const;

    // Замена хеш-функции (места для уже добавленных элементов должны быть пересчитаны)
    void setHashFunction(IHashFunction* newFunc);

    // Изменение размера хеш-таблицы
    void resize(const uint newSize);

private:
    struct KeyValuePair
    {
        uint key;
        std::string value;
        KeyValuePair* next;

        KeyValuePair(uint k, const std::string& v) : key(k), value(v), next(nullptr) {}
    };

    struct TableEntry
    {
        KeyValuePair* head;
        bool empty;

        TableEntry() : head(nullptr), empty(true) {}
    };

    std::vector<TableEntry> tableData_;
    uint keysCount_ = 0;
    IHashFunction* currentHashFunction_ = nullptr;

    uint getHash(const uint key, const uint attempt) const;
    bool findNode(const uint key, uint& bucketIndex, KeyValuePair** prev, KeyValuePair** found) const;
    void rehashAll();
    void clearTable();
    void copyFrom(const HashTable& other);
};