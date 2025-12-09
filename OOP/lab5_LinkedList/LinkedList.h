#pragma once

#include <stdint.h>
#include <iostream>
#include <stdexcept>

//Класс Список
template<typename ItemType>
class LinkedList
{
private:
    class ListNode;

public:
    class iterator;
    class const_iterator;

    LinkedList() = default; //Конструктор по умолчанию
    LinkedList(const ItemType* array, uint32_t size); //Конструктор из массива
    LinkedList(const LinkedList<ItemType>&); //Конструктор копирования
    ~LinkedList(); //Деструктор

    uint32_t getSize() const; //Получение размера массива
    void swap(LinkedList<ItemType>& other) noexcept; //Обмен списков

    ListNode* find(const ItemType& key); //Поиск элемента по ключу
    const ListNode* find(const ItemType& key) const; //Поиск элемента по ключу (константный)
    iterator findIter(const ItemType& key); //Поиск по итератору
    const_iterator findIter(const ItemType& key) const; //Поиск по итератору (константный)

    void addToHead(const ItemType& value); //Добавление в голову
    void addToTail(const ItemType& value); //Добавление в хвост
    bool addAtPosition(const ItemType& value, uint32_t position); //Добавление на позицию
    bool addAfterKey(const ItemType& value, const ItemType& key); //Добавление после ключа
    iterator add(iterator position, const ItemType& value); // Добавление по итератору

    bool removeFromHead(); //Удалить из головы
    bool removeFromTail(); //Удалить с хвоста
    bool removeAtPosition(uint32_t position); //Удалить на позици
    bool removeByKey(const ItemType& key); //Удалить по ключу
    iterator remove(iterator position); //Удаление по итератору на позиции
    iterator remove(iterator first, iterator last); //Удаление в диапазоне по итераторам

    ItemType findMax() const; //Найти макс
    ItemType findMin() const; //Найти мин
    bool isEmpty() const; //Проверка на пустоту
    void clear(); //Очистка списка
    void sort(); //Сортировка (выбором)

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    //Перегрузки
    LinkedList<ItemType>& operator=(const LinkedList<ItemType>&); //Присваивание
    ItemType& operator[](uint32_t index); //Получение ссылки на ключ элемента
    const ItemType& operator[](uint32_t index) const; //Получение ссылки на ключ элемента (константный)
    bool operator==(const LinkedList<ItemType>& other) const; //Сравнение на равенство
    bool operator!=(const LinkedList<ItemType>& other) const; //Сравнение на неравенство
    LinkedList<ItemType> operator+(const LinkedList<ItemType>& other) const; //Конкатенация(+)
    LinkedList<ItemType>& operator+=(const LinkedList<ItemType>& other); //Конкатенация(+=)

private:
    ListNode* headPtr_ = nullptr;
    ListNode* tailPtr_ = nullptr;
    uint32_t size_ = 0;

};

//Класс узла списка
template<typename ItemType>
class LinkedList<ItemType>::ListNode
{
public:
    ListNode(ItemType = ItemType(), ListNode* = nullptr, ListNode* = nullptr);

    ItemType& getValue(); //Получение значения узла
    const ItemType& getValue() const; //Получение значения узла (конст)

    ListNode* getLinkToNextNode(); //Указатель на следующий узел
    const ListNode* getLinkToNextNode() const; //Указатель на следующий узел (конст) 
    ListNode* getLinkToPrevNode(); //Указатель на предыдущий узел
    const ListNode* getLinkToPrevNode() const; //Указатель на предыдущий узел (конст)

    void setLinkToNextNode(ListNode*); // Установка указателя на следующий узел
    void setLinkToPrevNode(ListNode*); // Установка указатедя на предыдущий узел

private:
    ItemType value_;
    ListNode* linkToNextNode_;
    ListNode* linkToPrevNode_;
};

//Класс неконстантного итератора
template<typename ItemType>
class LinkedList<ItemType>::iterator
{
public:
    iterator(ListNode*);

    ListNode* getNode() const { return nodePtr_; };

    bool operator==(const iterator&);
    bool operator!=(const iterator&);
    iterator& operator++();
    iterator operator++(int);
    ItemType& operator*();

private:
    ListNode* nodePtr_;
};

//Класс константного итератора
template<typename ItemType>
class LinkedList<ItemType>::const_iterator
{
public:
    const_iterator(const ListNode*);
    const_iterator(const iterator&);

    const ListNode* getNode() const { return nodePtr_; }

    bool operator==(const const_iterator&);
    bool operator!=(const const_iterator&);
    const_iterator& operator++();
    const_iterator operator++(int);
    const ItemType& operator*();

private:
    const ListNode* nodePtr_;
};

// Реализация методов LinkedList
//Конструктор из массива
template<typename ItemType>
LinkedList<ItemType>::LinkedList(const ItemType* array, uint32_t size)
{
    for (uint32_t i = 0; i < size; ++i) {
        addToTail(array[i]);
    }
}


//Конструктор копирования
template<typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& other)
{
    const ListNode* current = other.headPtr_;
    while (current != nullptr) {
        addToTail(current->getValue());
        current = current->getLinkToNextNode();
    }
}

//Деструктор
template<typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clear();
}

//Размер списка
template<typename ItemType>
uint32_t LinkedList<ItemType>::getSize() const
{
    return size_;
}

//Обмен списков
template<typename ItemType>
void LinkedList<ItemType>::swap(LinkedList<ItemType>& other) noexcept
{
    std::swap(headPtr_, other.headPtr_);
    std::swap(tailPtr_, other.tailPtr_);
    std::swap(size_, other.size_);
}

//Поиск элемента по ключу
template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::find(const ItemType& key)
{
    ListNode* current = headPtr_;
    while (current != nullptr) {
        if (current->getValue() == key) {
            return current;
        }
        current = current->getLinkToNextNode();
    }
    return nullptr;
}

//Поиск элемента по ключу (константный)
template<typename ItemType>
const typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::find(const ItemType& key) const
{
    const ListNode* current = headPtr_;
    while (current != nullptr) {
        if (current->getValue() == key) {
            return current;
        }
        current = current->getLinkToNextNode();
    }
    return nullptr;
}

// Поиск элемента по ключу через итераторы (возвращает итератор)
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::findIter(const ItemType& key)
{
    ListNode* current = headPtr_;
    while (current != nullptr) {
        if (current->getValue() == key) {
            return iterator(current);
        }
        current = current->getLinkToNextNode();
    }
    return end();
}

//Константный поиск по ключу через итераторы
template<typename ItemType>
typename LinkedList<ItemType>::const_iterator LinkedList<ItemType>::findIter(const ItemType& key) const
{
    const ListNode* current = headPtr_;
    while (current != nullptr) {
        if (current->getValue() == key) {
            return const_iterator(current);
        }
        current = current->getLinkToNextNode();
    }
    return end();
}

//Добавить в голову
template<typename ItemType>
void LinkedList<ItemType>::addToHead(const ItemType& value)
{
    ListNode* newNode = new ListNode(value, headPtr_, nullptr);

    if (headPtr_) {
        headPtr_->setLinkToPrevNode(newNode);
    }

    headPtr_ = newNode;

    if (!tailPtr_) {
        tailPtr_ = newNode;
    }

    ++size_;
}

//Добавить в хвост
template<typename ItemType>
void LinkedList<ItemType>::addToTail(const ItemType& value)
{
    ListNode* newNode = new ListNode(value, nullptr, tailPtr_);

    if (tailPtr_) {
        tailPtr_->setLinkToNextNode(newNode);
    }

    tailPtr_ = newNode;

    if (!headPtr_) {
        headPtr_ = newNode;
    }

    ++size_;
}

//Добавить на позицию
template<typename ItemType>
bool LinkedList<ItemType>::addAtPosition(const ItemType& value, uint32_t position)
{
    if (position > size_) {
        return false;
    }

    if (position == 0) {
        addToHead(value);
        return true;
    }

    if (position == size_) {
        addToTail(value);
        return true;
    }

    ListNode* current = headPtr_;
    for (uint32_t i = 0; i < position - 1; ++i) {
        current = current->getLinkToNextNode();
    }

    ListNode* newNode = new ListNode(value, current->getLinkToNextNode(), current);
    current->getLinkToNextNode()->setLinkToPrevNode(newNode);
    current->setLinkToNextNode(newNode);

    ++size_;
    return true;
}

//Добавить после ключа
template<typename ItemType>
bool LinkedList<ItemType>::addAfterKey(const ItemType& value, const ItemType& key)
{
    ListNode* keyNode = find(key);
    if (keyNode == nullptr) {
        return false;
    }

    if (keyNode == tailPtr_) {
        addToTail(value);
        return true;
    }

    ListNode* newNode = new ListNode(value, keyNode->getLinkToNextNode(), keyNode);
    keyNode->getLinkToNextNode()->setLinkToPrevNode(newNode);
    keyNode->setLinkToNextNode(newNode);

    ++size_;
    return true;
}

/// Добавление элемента по итератору
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::add(iterator position, const ItemType& value)
{
    if (position == begin()) {
        addToHead(value);
        return begin();
    }

    if (position == end()) {
        addToTail(value);
        return iterator(tailPtr_);
    }

    ListNode* posNode = position.getNode();
    if (!posNode) {
        throw std::invalid_argument("Недопустимый итератор");
    }

    // Создаем новый узел
    ListNode* newNode = new ListNode(value, posNode, posNode->getLinkToPrevNode());

    // Обновляем связи
    if (posNode->getLinkToPrevNode()) {
        posNode->getLinkToPrevNode()->setLinkToNextNode(newNode);
    }

    // Всегда обновляем связь текущего узла
    posNode->setLinkToPrevNode(newNode);

    // Если вставляем в начало (перед головой)
    if (posNode == headPtr_) {
        headPtr_ = newNode;
    }

    ++size_;
    return iterator(newNode);
}

//Удалить из головы
template<typename ItemType>
bool LinkedList<ItemType>::removeFromHead()
{
    if (headPtr_ == nullptr) {
        return false;
    }

    ListNode* nodeToDelete = headPtr_;
    headPtr_ = headPtr_->getLinkToNextNode();

    if (headPtr_) {
        headPtr_->setLinkToPrevNode(nullptr);
    }
    else {
        tailPtr_ = nullptr;
    }

    delete nodeToDelete;
    --size_;
    return true;
}

//Удалить с хвоста
template<typename ItemType>
bool LinkedList<ItemType>::removeFromTail()
{
    if (tailPtr_ == nullptr) {
        return false;
    }

    ListNode* nodeToDelete = tailPtr_;
    tailPtr_ = tailPtr_->getLinkToPrevNode();

    if (tailPtr_) {
        tailPtr_->setLinkToNextNode(nullptr);
    }
    else {
        headPtr_ = nullptr;
    }

    delete nodeToDelete;
    --size_;
    return true;
}

//Удалить на позиции
template<typename ItemType>
bool LinkedList<ItemType>::removeAtPosition(uint32_t position)
{
    if (position >= size_) {
        return false;
    }

    if (position == 0) {
        return removeFromHead();
    }

    if (position == size_ - 1) {
        return removeFromTail();
    }

    ListNode* current = headPtr_;
    for (uint32_t i = 0; i < position; ++i) {
        current = current->getLinkToNextNode();
    }

    current->getLinkToPrevNode()->setLinkToNextNode(current->getLinkToNextNode());
    current->getLinkToNextNode()->setLinkToPrevNode(current->getLinkToPrevNode());

    delete current;
    --size_;
    return true;
}

//Удалить по ключу
template<typename ItemType>
bool LinkedList<ItemType>::removeByKey(const ItemType& key)
{
    ListNode* nodeToDelete = find(key);
    if (nodeToDelete == nullptr) {
        return false;
    }

    if (nodeToDelete == headPtr_) {
        return removeFromHead();
    }

    if (nodeToDelete == tailPtr_) {
        return removeFromTail();
    }

    nodeToDelete->getLinkToPrevNode()->setLinkToNextNode(nodeToDelete->getLinkToNextNode());
    nodeToDelete->getLinkToNextNode()->setLinkToPrevNode(nodeToDelete->getLinkToPrevNode());

    delete nodeToDelete;
    --size_;
    return true;
}

// Удаление элемента по итератору
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::remove(iterator position)
{
    if (position == end()) {
        return end();
    }

    ListNode* nodeToDelete = position.getNode();
    if (!nodeToDelete) {
        return end();
    }

    iterator nextIter(nodeToDelete->getLinkToNextNode());

    if (nodeToDelete == headPtr_) {
        removeFromHead();
        return nextIter;
    }

    if (nodeToDelete == tailPtr_) {
        removeFromTail();
        return end();
    }

    // Обновляем связи соседних узлов
    if (nodeToDelete->getLinkToPrevNode()) {
        nodeToDelete->getLinkToPrevNode()->setLinkToNextNode(nodeToDelete->getLinkToNextNode());
    }
    if (nodeToDelete->getLinkToNextNode()) {
        nodeToDelete->getLinkToNextNode()->setLinkToPrevNode(nodeToDelete->getLinkToPrevNode());
    }

    delete nodeToDelete;
    --size_;
    return nextIter;
}

// Удаление диапазона элементов
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::remove(iterator first, iterator last)
{
    if (first == last) {
        return last;
    }

    // Находим узел после последнего удаляемого
    ListNode* afterLast = (last == end()) ? nullptr : last.getNode();

    // Находим узел перед первым удаляемым
    ListNode* beforeFirst = (first == begin()) ? nullptr : first.getNode()->getLinkToPrevNode();

    // Удаляем все узлы в диапазоне
    ListNode* current = first.getNode();
    while (current != afterLast && current != nullptr) {
        ListNode* next = current->getLinkToNextNode();

        // Если удаляем голову
        if (current == headPtr_) {
            headPtr_ = next;
        }
        // Если удаляем хвост
        if (current == tailPtr_) {
            tailPtr_ = current->getLinkToPrevNode();
        }

        delete current;
        --size_;
        current = next;
    }

    // Обновляем связи
    if (beforeFirst && afterLast) {
        beforeFirst->setLinkToNextNode(afterLast);
        afterLast->setLinkToPrevNode(beforeFirst);
    }
    else if (beforeFirst) {
        beforeFirst->setLinkToNextNode(nullptr);
        tailPtr_ = beforeFirst;
    }
    else if (afterLast) {
        afterLast->setLinkToPrevNode(nullptr);
        headPtr_ = afterLast;
    }
    else {
        headPtr_ = tailPtr_ = nullptr;
    }

    return last;
}

//Найти макс
template<typename ItemType>
ItemType LinkedList<ItemType>::findMax() const
{
    if (isEmpty()) {
        throw std::runtime_error("Список пуст");
    }

    const ListNode* current = headPtr_;
    ItemType maxVal = current->getValue();
    current = current->getLinkToNextNode();

    while (current != nullptr) {
        if (current->getValue() > maxVal) {
            maxVal = current->getValue();
        }
        current = current->getLinkToNextNode();
    }

    return maxVal;
}

//Найти мин
template<typename ItemType>
ItemType LinkedList<ItemType>::findMin() const
{
    if (isEmpty()) {
        throw std::runtime_error("Список пуст");
    }

    const ListNode* current = headPtr_;
    ItemType minVal = current->getValue();
    current = current->getLinkToNextNode();

    while (current != nullptr) {
        if (current->getValue() < minVal) {
            minVal = current->getValue();
        }
        current = current->getLinkToNextNode();
    }

    return minVal;
}

//Проверка на пустоту
template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
    return size_ == 0;
}

//Очистка списка
template<typename ItemType>
void LinkedList<ItemType>::clear()
{
    while (headPtr_ != nullptr) {
        ListNode* temp = headPtr_;
        headPtr_ = headPtr_->getLinkToNextNode();
        delete temp;
    }
    tailPtr_ = nullptr;
    size_ = 0;
}

// Сортировка (выбором)
template<typename ItemType>
void LinkedList<ItemType>::sort()
{
    if (size_ <= 1) return;

    ListNode* current = headPtr_;

    while (current) {
        // Ищем минимальный элемент в оставшейся части списка
        ListNode* minNode = current;
        ListNode* temp = current->getLinkToNextNode();

        while (temp) {
            if (temp->getValue() < minNode->getValue()) {
                minNode = temp;
            }
            temp = temp->getLinkToNextNode();
        }

        // Меняем местами значения текущего узла и минимального
        if (minNode != current) {
            ItemType tempValue = current->getValue();
            current->getValue() = minNode->getValue();
            minNode->getValue() = tempValue;
        }

        current = current->getLinkToNextNode();
    }
}

//Итератор на начало
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::begin()
{
    return iterator(headPtr_);
}

//Итератор на начало (конст)
template<typename ItemType>
typename LinkedList<ItemType>::const_iterator LinkedList<ItemType>::begin() const
{
    return const_iterator(headPtr_);
}

//Итератор на конец
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::end()
{
    return iterator(nullptr);
}

//Итератор на конец (конст)
template<typename ItemType>
typename LinkedList<ItemType>::const_iterator LinkedList<ItemType>::end() const
{
    return const_iterator(nullptr);
}

//Перегрузка присваивания
template<typename ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& other)
{
    if (this != &other) {
        LinkedList<ItemType> temp(other);
        swap(temp);
    }
    return *this;
}

//Перегрузка получения ссылки на ключ элемента
template<typename ItemType>
ItemType& LinkedList<ItemType>::operator[](uint32_t index)
{
    if (index >= size_) {
        throw std::out_of_range("Индекс выходит за границы");
    }

    ListNode* current = headPtr_;
    for (uint32_t i = 0; i < index; ++i) {
        current = current->getLinkToNextNode();
    }

    return current->getValue();
}

//Перегрузка получения ссылки на ключ элемента(конст)
template<typename ItemType>
const ItemType& LinkedList<ItemType>::operator[](uint32_t index) const
{
    if (index >= size_) {
        throw std::out_of_range("Индекс выходит за границы");
    }

    const ListNode* current = headPtr_;
    for (uint32_t i = 0; i < index; ++i) {
        current = current->getLinkToNextNode();
    }

    return current->getValue();
}

//Перегрузка сравнения на равенство
template<typename ItemType>
bool LinkedList<ItemType>::operator==(const LinkedList<ItemType>& other) const
{
    if (size_ != other.size_) {
        return false;
    }

    const ListNode* current1 = headPtr_;
    const ListNode* current2 = other.headPtr_;

    while (current1 != nullptr && current2 != nullptr) {
        if (current1->getValue() != current2->getValue()) {
            return false;
        }
        current1 = current1->getLinkToNextNode();
        current2 = current2->getLinkToNextNode();
    }

    return true;
}

//Перегрузка сравнения на неравенство
template<typename ItemType>
bool LinkedList<ItemType>::operator!=(const LinkedList<ItemType>& other) const
{
    return !(*this == other);
}

//Перегрузка конкатенации (+)
template<typename ItemType>
LinkedList<ItemType> LinkedList<ItemType>::operator+(const LinkedList<ItemType>& other) const
{
    LinkedList<ItemType> result(*this);
    result += other;
    return result;
}

//Перегрузка конкатенации (+=)
template<typename ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator+=(const LinkedList<ItemType>& other)
{
    const ListNode* current = other.headPtr_;
    while (current != nullptr) {
        addToTail(current->getValue());
        current = current->getLinkToNextNode();
    }
    return *this;
}

// Реализация методов ListNode
//Конструктор
template<typename ItemType>
LinkedList<ItemType>::ListNode::ListNode(ItemType value, ListNode* linkToNextNode, ListNode* linkToPrevNode) :
    value_(value), linkToNextNode_(linkToNextNode), linkToPrevNode_(linkToPrevNode) {
}

//Получение значения узла
template<typename ItemType>
ItemType& LinkedList<ItemType>::ListNode::getValue() { return value_; }

//Получение значения узла (конст)
template<typename ItemType>
const ItemType& LinkedList<ItemType>::ListNode::getValue() const { return value_; }

//Ссылка на следующий узел
template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNextNode() { return linkToNextNode_; }

//Ссылка на следующий узел (конст)
template<typename ItemType>
const typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNextNode() const { return linkToNextNode_; }

//Ссылка на предыдущий узел
template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrevNode() { return linkToPrevNode_; }

//Ссылка на предыдущий узел (конст)
template<typename ItemType>
const typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrevNode() const { return linkToPrevNode_; }

//Установить указатель на следующий узел
template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToNextNode(ListNode* newLink) { linkToNextNode_ = newLink; }

//Установить указатель на предыдущий узел
template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToPrevNode(ListNode* newLink) { linkToPrevNode_ = newLink; }

// Реализация методов iterator
template<typename ItemType>
LinkedList<ItemType>::iterator::iterator(ListNode* nodePtr) : nodePtr_(nodePtr) {}

//Сравнение
template<typename ItemType>
bool LinkedList<ItemType>::iterator::operator==(const iterator& other)
{
    return nodePtr_ == other.nodePtr_;
}
//Неравенство
template<typename ItemType>
bool LinkedList<ItemType>::iterator::operator!=(const iterator& other)
{
    return nodePtr_ != other.nodePtr_;
}

//постфиксный инкремент
template<typename ItemType>
typename LinkedList<ItemType>::iterator& LinkedList<ItemType>::iterator::operator++()
{
    if (nodePtr_) {
        nodePtr_ = nodePtr_->getLinkToNextNode();
    }
    return *this;
}

//префиксный инкремент
template<typename ItemType>
typename LinkedList<ItemType>::iterator LinkedList<ItemType>::iterator::operator++(int)
{
    iterator oldIterator(*this);
    if (nodePtr_) {
        nodePtr_ = nodePtr_->getLinkToNextNode();
    }
    return oldIterator;
}

//Разыменование
template<typename ItemType>
ItemType& LinkedList<ItemType>::iterator::operator*()
{
    if (!nodePtr_) {
        throw std::runtime_error("Попытка разыменовать нулевой итератор");
    }
    return nodePtr_->getValue();
}


// Реализация методов const_iterator
template<typename ItemType>
LinkedList<ItemType>::const_iterator::const_iterator(const ListNode* nodePtr) : nodePtr_(nodePtr) {}

template<typename ItemType>
LinkedList<ItemType>::const_iterator::const_iterator(const iterator& other) : nodePtr_(other.nodePtr_) {}

template<typename ItemType>
bool LinkedList<ItemType>::const_iterator::operator==(const const_iterator& other)
{
    return nodePtr_ == other.nodePtr_;
}

template<typename ItemType>
bool LinkedList<ItemType>::const_iterator::operator!=(const const_iterator& other)
{
    return nodePtr_ != other.nodePtr_;
}

// префиксный инкремент (конст)
template<typename ItemType>
typename LinkedList<ItemType>::const_iterator& LinkedList<ItemType>::const_iterator::operator++()
{
    if (nodePtr_) {
        nodePtr_ = nodePtr_->getLinkToNextNode();
    }
    return *this;
}

// постфиксный инкремент (конст)
template<typename ItemType>
typename LinkedList<ItemType>::const_iterator LinkedList<ItemType>::const_iterator::operator++(int)
{
    const_iterator oldIterator(*this);
    if (nodePtr_) {
        nodePtr_ = nodePtr_->getLinkToNextNode();
    }
    return oldIterator;
}

//Разыменование (конст)
template<typename ItemType>
const ItemType& LinkedList<ItemType>::const_iterator::operator*()
{
    if (!nodePtr_) {
        throw std::runtime_error("Попытка разыменовать нулевой итератор");
    }
    return nodePtr_->getValue();
}

// Оператор вывода
template<typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list)
{
    os << "[";

    for (typename LinkedList<T>::const_iterator it = list.begin(); it != list.end(); ++it) {
        os << *it;
        typename LinkedList<T>::const_iterator next = it;
        ++next;
        if (next != list.end()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

// Оператор ввода
template<typename T>
std::istream& operator>>(std::istream& is, LinkedList<T>& list)
{
    list.clear();

    uint32_t count;
    std::cout << "Введите количество элементов: ";
    is >> count;

    for (uint32_t i = 0; i < count; ++i) {
        T value;
        std::cout << "Элемент " << i + 1 << ": ";
        is >> value;
        list.addToTail(value);
    }

    return is;
}