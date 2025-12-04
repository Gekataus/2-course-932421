#pragma once

#include <stdint.h>
#include <iostream>
#include <stdexcept>

template<typename ItemType>
class LinkedList
{
private:
	class ListNode;

	ListNode* headPtr_ = nullptr;
	ListNode* tailPtr_ = nullptr;
	uint32_t size_ = 0;
public:
	
	//Конструкторы: по умолчанию, конструктор из обычного массивая, конструктор копирования)
	LinkedList() = default;
	LinkedList(const ItemType* array, uint32_t size);
	LinkedList(const LinkedList<ItemType>&);

	//Деструктор
	~LinkedList();

	//Получение размера списка
	uint32_t getSize() const;

	//Обмен содержимого с другим списком
	void swap(LinkedList<ItemType>& other) noexcept;

	//Поиск элемента по ключу (возвращает указатель на элемент или nullptr, если элемента нет в списке);
	ListNode* find(const ItemType& key);
	const ListNode* find(const ItemType& key) const;

	//добавление элемента (в голову, хвост, на позицию, после ключа (после первого вхождения),)
	void addToHead(const ItemType& value);
	void addToTail(const ItemType& value);
	bool addAtPosition(const ItemType& value, uint32_t position);
	bool addAfterKey(const ItemType& value, const ItemType& key);

	//удаление элемента (из головы, хвоста, позиции, по ключу (первое вхождение))
	bool removeFromHead();
	bool removeFromTail();
	bool removeAtPosition(uint32_t position);
	bool removeByKey(const ItemType& key);

	// -поиск максимального / минимального элемента;
	ItemType findMax() const;
	ItemType findMin() const;

	// - isEmpty() - возвращает true, если список пуст;
	bool isEmpty() const;

	//-очистка списка;
	void clear();

	//Перегрузки
	//- присваивание (=);
	LinkedList<ItemType>& operator=(const LinkedList<ItemType>&);

	//-получение ссылки на ключ элемента([]);
	ItemType& operator[](uint32_t index);
	const ItemType& operator[](uint32_t index) const;
	//-сравнение(== , != );
	bool operator==(const LinkedList<ItemType>& other) const;
	bool operator!=(const LinkedList<ItemType>& other) const;

	//сложение (конкатенация) списков (+, +=)
	LinkedList<ItemType> operator+(const LinkedList<ItemType>& other) const;
	LinkedList<ItemType>& operator+=(const LinkedList<ItemType>& other);
};

// Ввод/вывод в консоль
template<typename ItemType>
std::istream& operator>>(std::istream& is, LinkedList<ItemType>& list);

template<typename ItemType>
std::ostream& operator<<(std::ostream& os, const LinkedList<ItemType>& list);

//LinkedList

// Конструктор из массива
template<typename ItemType>
LinkedList<ItemType>::LinkedList(const ItemType* array, uint32_t size)
{
	for (uint32_t i = 0; i < size; ++i) {
		addToTail(array[i]);
	}
}

// Конструктор копирования
template<typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& other)
{
	const ListNode* current = other.headPtr_;
	while (current != nullptr) {
		addToTail(current->getValue());
		current = current->getLinkToNextNode();
	}
}

// Деструктор
template<typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}

// Получение размера списка
template<typename ItemType>
uint32_t LinkedList<ItemType>::getSize() const
{
	return size_;
}

// Обмен содержимого с другим списком
template<typename ItemType>
void LinkedList<ItemType>::swap(LinkedList<ItemType>& other) noexcept
{
	std::swap(headPtr_, other.headPtr_);
	std::swap(tailPtr_, other.tailPtr_);
	std::swap(size_, other.size_);
}

// Поиск элемента по ключу (неконстантная версия)
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

// Поиск элемента по ключу (константная версия)
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

// Добавление элемента в голову
template<typename ItemType>
void LinkedList<ItemType>::addToHead(const ItemType& value)
{
	ListNode* newNode = new ListNode(value, headPtr_, nullptr);

	if (headPtr_ != nullptr) {
		headPtr_->setLinkToPrevNode(newNode);
	}
	else {
		// Если список был пуст, новый узел - хвост
		tailPtr_ = newNode;
	}

	headPtr_ = newNode;
	++size_;
}

// Добавление элемента в хвост
template<typename ItemType>
void LinkedList<ItemType>::addToTail(const ItemType& value)
{
	ListNode* newNode = new ListNode(value, nullptr, tailPtr_);

	if (tailPtr_ != nullptr) {
		tailPtr_->setLinkToNextNode(newNode);
	}
	else {
		// Если список был пуст, новый узел - голова
		headPtr_ = newNode;
	}

	tailPtr_ = newNode;
	++size_;
}

// Добавление элемента на указанную позицию
template<typename ItemType>
bool LinkedList<ItemType>::addAtPosition(const ItemType& value, uint32_t position)
{
	if (position > size_) {
		return false; // Недопустимая позиция
	}

	if (position == 0) {
		addToHead(value);
		return true;
	}

	if (position == size_) {
		addToTail(value);
		return true;
	}

	// Ищем узел перед позицией вставки
	ListNode* current = headPtr_;
	for (uint32_t i = 0; i < position - 1; ++i) {
		current = current->getLinkToNextNode();
	}

	// Создаем новый узел
	ListNode* newNode = new ListNode(value, current->getLinkToNextNode(), current);

	// Обновляем связи
	current->getLinkToNextNode()->setLinkToPrevNode(newNode);
	current->setLinkToNextNode(newNode);

	++size_;
	return true;
}

// Добавление элемента после первого вхождения ключа
template<typename ItemType>
bool LinkedList<ItemType>::addAfterKey(const ItemType& value, const ItemType& key)
{
	ListNode* keyNode = find(key);
	if (keyNode == nullptr) {
		return false; // Ключ не найден
	}

	if (keyNode == tailPtr_) {
		// Если ключ в хвосте, просто добавляем в конец
		addToTail(value);
		return true;
	}

	// Создаем новый узел
	ListNode* newNode = new ListNode(value, keyNode->getLinkToNextNode(), keyNode);

	// Обновляем связи
	keyNode->getLinkToNextNode()->setLinkToPrevNode(newNode);
	keyNode->setLinkToNextNode(newNode);

	++size_;
	return true;
}
// Удаление элемента из головы
template<typename ItemType>
bool LinkedList<ItemType>::removeFromHead()
{
	if (headPtr_ == nullptr) {
		return false; // Список пуст
	}

	ListNode* nodeToDelete = headPtr_;
	headPtr_ = headPtr_->getLinkToNextNode();

	if (headPtr_ != nullptr) {
		headPtr_->setLinkToPrevNode(nullptr);
	}
	else {
		// Если список стал пустым
		tailPtr_ = nullptr;
	}

	delete nodeToDelete;
	--size_;
	return true;
}

// Удаление элемента из хвоста
template<typename ItemType>
bool LinkedList<ItemType>::removeFromTail()
{
	if (tailPtr_ == nullptr) {
		return false; // Список пуст
	}

	ListNode* nodeToDelete = tailPtr_;
	tailPtr_ = tailPtr_->getLinkToPrevNode();

	if (tailPtr_ != nullptr) {
		tailPtr_->setLinkToNextNode(nullptr);
	}
	else {
		// Если список стал пустым
		headPtr_ = nullptr;
	}

	delete nodeToDelete;
	--size_;
	return true;
}

// Удаление элемента из указанной позиции
template<typename ItemType>
bool LinkedList<ItemType>::removeAtPosition(uint32_t position)
{
	if (position >= size_) {
		return false; // Недопустимая позиция
	}

	if (position == 0) {
		return removeFromHead();
	}

	if (position == size_ - 1) {
		return removeFromTail();
	}

	// Ищем узел для удаления
	ListNode* current = headPtr_;
	for (uint32_t i = 0; i < position; ++i) {
		current = current->getLinkToNextNode();
	}

	// Обновляем связи соседних узлов
	current->getLinkToPrevNode()->setLinkToNextNode(current->getLinkToNextNode());
	current->getLinkToNextNode()->setLinkToPrevNode(current->getLinkToPrevNode());

	delete current;
	--size_;
	return true;
}

// Удаление первого вхождения элемента по ключу
template<typename ItemType>
bool LinkedList<ItemType>::removeByKey(const ItemType& key)
{
	ListNode* nodeToDelete = find(key);
	if (nodeToDelete == nullptr) {
		return false; // Ключ не найден
	}

	if (nodeToDelete == headPtr_) {
		return removeFromHead();
	}

	if (nodeToDelete == tailPtr_) {
		return removeFromTail();
	}

	// Обновляем связи
	nodeToDelete->getLinkToPrevNode()->setLinkToNextNode(nodeToDelete->getLinkToNextNode());
	nodeToDelete->getLinkToNextNode()->setLinkToPrevNode(nodeToDelete->getLinkToPrevNode());

	delete nodeToDelete;
	--size_;
	return true;
}

// Поиск максимального элемента
template<typename ItemType>
ItemType LinkedList<ItemType>::findMax() const
{
	if (isEmpty()) {
		throw std::runtime_error("Список пуст, невозможно найти максимальный элемент");
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

// Поиск минимального элемента
template<typename ItemType>
ItemType LinkedList<ItemType>::findMin() const
{
	if (isEmpty()) {
		throw std::runtime_error("Список пуст, невозможно найти минимальный элемент");
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

// Проверка на пустоту списка
template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return size_ == 0;
}

// Очистка списка
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

// Оператор присваивания
template<typename ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType>& other)
{
	if (this != &other) {
		LinkedList<ItemType> temp(other);
		swap(temp);
	}
	return *this;
}


// Оператор доступа по индексу (неконстантная версия)
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

// Оператор доступа по индексу (константная версия)
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


// Оператор сравнения на равенство
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

// Оператор сравнения на неравенство
template<typename ItemType>
bool LinkedList<ItemType>::operator!=(const LinkedList<ItemType>& other) const
{
	return !(*this == other);
}

// Оператор сложения (конкатенация)
template<typename ItemType>
LinkedList<ItemType> LinkedList<ItemType>::operator+(const LinkedList<ItemType>& other) const
{
	LinkedList<ItemType> result(*this);
	result += other;
	return result;
}

// Оператор сложения с присваиванием (конкатенация)
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

// Реализация оператора вывода
template<typename ItemType>
std::ostream& operator<<(std::ostream& os, const LinkedList<ItemType>& list)
{
    // Так как это не дружественная функция, у нас нет прямого доступа к private полям
    // Мы будем использовать публичные методы
    if (list.isEmpty()) {
        os << "(пустой список)";
        return os;
    }

    for (uint32_t i = 0; i < list.getSize(); ++i) {
        os << list[i];
        if (i < list.getSize() - 1) {
            os << " ";
        }
    }
    return os;
}

// Реализация оператора ввода
template<typename ItemType>
std::istream& operator>>(std::istream& is, LinkedList<ItemType>& list)
{
    list.clear(); // Очищаем список перед вводом
    
    ItemType value;
    while (is >> value) {
        list.addToTail(value);
        // Проверяем следующий символ, если это конец строки - выходим
        if (is.peek() == '\n' || is.peek() == EOF) {
            break;
        }
    }
    
    // Сбрасываем флаги ошибок, если мы достигли конца ввода
    if (is.eof()) {
        is.clear();
    }
    
    return is;
}

template<typename ItemType>
class LinkedList<ItemType>::ListNode
{
public:
	ListNode(ItemType value = ItemType(), ListNode* next = nullptr, ListNode* prev = nullptr);

	// Получение значения узла
	ItemType& getValue();
	const ItemType& getValue() const;

	// Получение указателя на следующий узел
	ListNode* getLinkToNextNode();
	const ListNode* getLinkToNextNode() const;

	// Получение указателя на предыдущий узел
	ListNode* getLinkToPrevNode();
	const ListNode* getLinkToPrevNode() const;

	// Установка указателя на следующий узел
	void setLinkToNextNode(ListNode* next);

	// Установка указателя на предыдущий узел
	void setLinkToPrevNode(ListNode* prev);

private:
	ItemType value_;
	ListNode* linkToNextNode_;
	ListNode* linkToPrevNode_;
};



//ListNode
template<typename ItemType>
LinkedList<ItemType>::ListNode::ListNode(ItemType value, ListNode* next, ListNode* prev)
	: value_(value), linkToNextNode_(next), linkToPrevNode_(prev) {
}

template<typename ItemType>
ItemType& LinkedList<ItemType>::ListNode::getValue()
{
	return value_;
}

template<typename ItemType>
const ItemType& LinkedList<ItemType>::ListNode::getValue() const
{
	return value_;
}

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNextNode()
{
	return linkToNextNode_;
}

template<typename ItemType>
const typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToNextNode() const
{
	return linkToNextNode_;
}

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrevNode()
{
	return linkToPrevNode_;
}

template<typename ItemType>
const typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::ListNode::getLinkToPrevNode() const
{
	return linkToPrevNode_;
}

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToNextNode(ListNode* next)
{
	linkToNextNode_ = next;
}

template<typename ItemType>
void LinkedList<ItemType>::ListNode::setLinkToPrevNode(ListNode* prev)
{
	linkToPrevNode_ = prev;
}
