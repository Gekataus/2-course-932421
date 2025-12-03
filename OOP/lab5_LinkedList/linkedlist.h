#pragma once

#include <stdint.h>
#include <iostream>

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

	//добавление элемента (в голову, хвост)
	void addToHead(const ItemType& value);
	void addToTail(const ItemType& value);

	//удаление элемента (из головы, хвоста)
	bool removeFromHead();
	bool removeFromTail();

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

	// Ввод/вывод в консоль
	friend std::ostream& operator<<(std::ostream&, const LinkedList<ItemType>&);
	friend std::istream& operator>>(std::istream&, LinkedList<ItemType>&);
};

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

template<typename ItemType>
std::ostream& operator<<(std::ostream& os, const LinkedList<ItemType>& list) {
	ListNode* current = list.headPtr_;
	while (current) {
		os << current->getValue() << " ";
		current = current->getLinkToNextNode();
	}
	return os;
}
template<typename ItemType>
std::istream& operator>>(std::istream& is, LinkedList<ItemType>& list) {
	ItemType value;
	list.clear(); // Очищаем список перед вводом
	while (is >> value) {
		list.addToTail(value);
	}
	return is;
}
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
