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

	// Вспомогательные методы для сортировки
	ListNode* getMiddle(ListNode* head);
	ListNode* merge(ListNode* left, ListNode* right);
	ListNode* mergeSort(ListNode* head);
public:

	class Iterator;
	class ConstIterator;

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

	//Поиск элемента по ключу (возвращает указатель/итератор на элемент или nullptr, если элемента нет в списке);
	ListNode* find(const ItemType& key);
	const ListNode* find(const ItemType& key) const;
	Iterator findIter(const ItemType& key);
	ConstIterator findIter(const ItemType& key) const;

	//добавление элемента (в голову, хвост, на позицию, после ключа (после первого вхождения), по итератору)
	void addToHead(const ItemType& value);
	void addToTail(const ItemType& value);
	bool addAtPosition(const ItemType& value, uint32_t position);
	bool addAfterKey(const ItemType& value, const ItemType& key);
	Iterator add(Iterator position, const ItemType& value);

	//удаление элемента (из головы, хвоста, позиции, по ключу (первое вхождение), по итератору)
	bool removeFromHead();
	bool removeFromTail();
	bool removeAtPosition(uint32_t position);
	bool removeByKey(const ItemType& key);
	Iterator remove(Iterator position);
	Iterator remove(Iterator first, Iterator last);

	// -поиск максимального / минимального элемента;
	ItemType findMax() const;
	ItemType findMin() const;

	// - isEmpty() - возвращает true, если список пуст;
	bool isEmpty() const;

	//-очистка списка;
	void clear();

	// Сортировка списка
	void sort();

	// Получение итераторов
	Iterator begin();
	ConstIterator begin() const;
	ConstIterator cbegin() const;
	Iterator end();
	ConstIterator end() const;
	ConstIterator cend() const;

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

	// Ввод/вывод в консоль
	template<typename ItemType>
	friend std::ostream& operator<<(std::ostream&, const LinkedList<ItemType>&);
	template<typename ItemType>
	friend std::istream& operator>>(std::istream&, LinkedList<ItemType>&);
};

// Класс обычного итератора
template<typename ItemType>
class LinkedList<ItemType>::Iterator
{
private:
	ListNode* nodePtr_;

public:
	Iterator(ListNode* node = nullptr) : nodePtr_(node) {}
	Iterator(const Iterator& other) : nodePtr_(other.nodePtr_) {}

	// Операторы сравнения
	bool operator==(const Iterator& other) const { return nodePtr_ == other.nodePtr_; }
	bool operator!=(const Iterator& other) const { return nodePtr_ != other.nodePtr_; }

	// Префиксный инкремент
	Iterator& operator++()
	{
		if (nodePtr_)
			nodePtr_ = nodePtr_->getLinkToNextNode();
		return *this;
	}

	// Постфиксный инкремент
	Iterator operator++(int)
	{
		Iterator temp = *this;
		++(*this);
		return temp;
	}

	// Префиксный декремент
	Iterator& operator--()
	{
		if (nodePtr_)
			nodePtr_ = nodePtr_->getLinkToPrevNode();
		return *this;
	}

	// Постфиксный декремент
	Iterator operator--(int)
	{
		Iterator temp = *this;
		--(*this);
		return temp;
	}

	// Оператор разыменования
	ItemType& operator*() const
	{
		if (!nodePtr_)
			throw std::runtime_error("Попытка разыменовать нулевой итератор");
		return nodePtr_->getValue();
	}

	// Оператор доступа к членам
	ItemType* operator->() const
	{
		if (!nodePtr_)
			throw std::runtime_error("Попытка доступа через нулевой итератор");
		return &(nodePtr_->getValue());
	}

	// Получение указателя на узел
	ListNode* getNode() const { return nodePtr_; }

	friend class LinkedList<ItemType>;
};

// Класс константного итератора
template<typename ItemType>
class LinkedList<ItemType>::ConstIterator
{
private:
	const ListNode* nodePtr_;

public:
	ConstIterator(const ListNode* node = nullptr) : nodePtr_(node) {}
	ConstIterator(const Iterator& other) : nodePtr_(other.nodePtr_) {}
	ConstIterator(const ConstIterator& other) : nodePtr_(other.nodePtr_) {}

	// Операторы сравнения
	bool operator==(const ConstIterator& other) const { return nodePtr_ == other.nodePtr_; }
	bool operator!=(const ConstIterator& other) const { return nodePtr_ != other.nodePtr_; }

	// Префиксный инкремент
	ConstIterator& operator++()
	{
		if (nodePtr_)
			nodePtr_ = nodePtr_->getLinkToNextNode();
		return *this;
	}

	// Постфиксный инкремент
	ConstIterator operator++(int)
	{
		ConstIterator temp = *this;
		++(*this);
		return temp;
	}

	// Префиксный декремент
	ConstIterator& operator--()
	{
		if (nodePtr_)
			nodePtr_ = nodePtr_->getLinkToPrevNode();
		return *this;
	}

	// Постфиксный декремент
	ConstIterator operator--(int)
	{
		ConstIterator temp = *this;
		--(*this);
		return temp;
	}

	// Оператор разыменования
	const ItemType& operator*() const
	{
		if (!nodePtr_)
			throw std::runtime_error("Попытка разыменовать нулевой итератор");
		return nodePtr_->getValue();
	}

	// Оператор доступа к членам
	const ItemType* operator->() const
	{
		if (!nodePtr_)
			throw std::runtime_error("Попытка доступа через нулевой итератор");
		return &(nodePtr_->getValue());
	}

	// Получение указателя на узел
	const ListNode* getNode() const { return nodePtr_; }

	friend class LinkedList<ItemType>;
};

// Получение итераторов
template<typename ItemType>
typename LinkedList<ItemType>::Iterator LinkedList<ItemType>::begin()
{
	return Iterator(headPtr_);
}

template<typename ItemType>
typename LinkedList<ItemType>::ConstIterator LinkedList<ItemType>::begin() const
{
	return ConstIterator(headPtr_);
}

template<typename ItemType>
typename LinkedList<ItemType>::ConstIterator LinkedList<ItemType>::cbegin() const
{
	return ConstIterator(headPtr_);
}

template<typename ItemType>
typename LinkedList<ItemType>::Iterator LinkedList<ItemType>::end()
{
	return Iterator(nullptr);
}

template<typename ItemType>
typename LinkedList<ItemType>::ConstIterator LinkedList<ItemType>::end() const
{
	return ConstIterator(nullptr);
}

template<typename ItemType>
typename LinkedList<ItemType>::ConstIterator LinkedList<ItemType>::cend() const
{
	return ConstIterator(nullptr);
}

// Поиск элемента по ключу (возвращает итератор)
template<typename ItemType>
typename LinkedList<ItemType>::Iterator LinkedList<ItemType>::findIter(const ItemType& key)
{
	ListNode* current = headPtr_;
	while (current != nullptr) {
		if (current->getValue() == key) {
			return Iterator(current);
		}
		current = current->getLinkToNextNode();
	}
	return end();
}

template<typename ItemType>
typename LinkedList<ItemType>::ConstIterator LinkedList<ItemType>::findIter(const ItemType& key) const
{
	const ListNode* current = headPtr_;
	while (current != nullptr) {
		if (current->getValue() == key) {
			return ConstIterator(current);
		}
		current = current->getLinkToNextNode();
	}
	return cend();
}

// Добавление элемента по итератору
template<typename ItemType>
typename LinkedList<ItemType>::Iterator LinkedList<ItemType>::add(Iterator position, const ItemType& value)
{
	if (position == begin()) {
		addToHead(value);
		return begin();
	}

	if (position == end()) {
		addToTail(value);
		return Iterator(tailPtr_);
	}

	ListNode* posNode = position.getNode();
	if (!posNode) {
		throw std::invalid_argument("Недопустимый итератор");
	}

	ListNode* newNode = new ListNode(value, posNode, posNode->getLinkToPrevNode());

	if (posNode->getLinkToPrevNode()) {
		posNode->getLinkToPrevNode()->setLinkToNextNode(newNode);
	}
	posNode->setLinkToPrevNode(newNode);

	// Если вставляем перед головой
	if (posNode == headPtr_) {
		headPtr_ = newNode;
	}

	++size_;
	return Iterator(newNode);
}

// Удаление элемента по итератору
template<typename ItemType>
typename LinkedList<ItemType>::Iterator LinkedList<ItemType>::remove(Iterator position)
{
	if (position == end()) {
		return end();
	}

	ListNode* nodeToDelete = position.getNode();
	if (!nodeToDelete) {
		return end();
	}

	Iterator nextIter(nodeToDelete->getLinkToNextNode());

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
typename LinkedList<ItemType>::Iterator LinkedList<ItemType>::remove(Iterator first, Iterator last)
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

// Сортировка списка (сортировка слиянием)
template<typename ItemType>
void LinkedList<ItemType>::sort()
{
	if (size_ <= 1) return;

	headPtr_ = mergeSort(headPtr_);

	// Обновляем tailPtr_ и связи между узлами
	ListNode* current = headPtr_;
	ListNode* prev = nullptr;
	while (current) {
		current->setLinkToPrevNode(prev);
		prev = current;
		current = current->getLinkToNextNode();
	}
	tailPtr_ = prev;
}

// Вспомогательные методы для сортировки слиянием

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::getMiddle(ListNode* head)
{
	if (!head) return nullptr;

	ListNode* slow = head;
	ListNode* fast = head->getLinkToNextNode();

	while (fast && fast->getLinkToNextNode()) {
		slow = slow->getLinkToNextNode();
		fast = fast->getLinkToNextNode()->getLinkToNextNode();
	}

	return slow;
}

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::merge(ListNode* left, ListNode* right)
{
	if (!left) return right;
	if (!right) return left;

	ListNode* result = nullptr;

	if (left->getValue() <= right->getValue()) {
		result = left;
		result->setLinkToNextNode(merge(left->getLinkToNextNode(), right));
	}
	else {
		result = right;
		result->setLinkToNextNode(merge(left, right->getLinkToNextNode()));
	}

	return result;
}

template<typename ItemType>
typename LinkedList<ItemType>::ListNode* LinkedList<ItemType>::mergeSort(ListNode* head)
{
	if (!head || !head->getLinkToNextNode()) {
		return head;
	}

	ListNode* middle = getMiddle(head);
	ListNode* nextToMiddle = middle->getLinkToNextNode();

	middle->setLinkToNextNode(nullptr);

	ListNode* left = mergeSort(head);
	ListNode* right = mergeSort(nextToMiddle);

	return merge(left, right);
}

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
	os << "[";
	typename LinkedList<ItemType>::ListNode* current = list.headPtr_;
	while (current != nullptr) {
		os << current->getValue();
		current = current->getLinkToNextNode();
		if (current != nullptr) {
			os << ", ";
		}
	}
	os << "]";
	return os;
}

// Реализация оператора ввода
template<typename ItemType>
std::istream& operator>>(std::istream& is, LinkedList<ItemType>& list)
{
	// Очищаем существующий список
	list.clear();

	// Читаем количество элементов
	uint32_t count;
	std::cout << "Введите количество элементов: ";
	is >> count;

	// Читаем каждый элемент
	for (uint32_t i = 0; i < count; ++i) {
		ItemType value;
		std::cout << "Элемент " << i + 1 << ": ";
		is >> value;
		list.addToTail(value);
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
