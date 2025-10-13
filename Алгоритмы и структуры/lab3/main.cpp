#include <iostream>
#include <vector>
#include <random>

//создание массива случайных чисел (Библиотека random)
std::vector<int> generateRandomArray(int size, int min_val, int max_val) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(min_val, max_val);

	std::vector<int> arr(size);
	for (int i = 0; i < size; i++) {
		arr[i] = distrib(gen);
	}
	return arr;
}

// Просеивание
void sift(std::vector<int>& arr, int n, int i) {
	int max = i;// Инициализируем наибольший элемент как корень
	int left = 2 * i + 1;   // Левый потомок
	int right = 2 * i + 2;  // Правый потомок

	// Если левый потомок существует и больше корня
	if (left < n && arr[left] > arr[max])
		max = left;

	// Если правый потомок существует и больше наибольшего элемента
	if (right < n && arr[right] > arr[max])
		max = right;

	// Если наибольший элемент не корень
	if (max != i) 
	{
		std::swap(arr[i], arr[max]);

		// Рекурсивно просеиваем вниз для затронутой подпирамиды
		sift(arr, n, max);
	}
}

// Пирамидальная сортировка
void pyramidSort(std::vector<int>& arr) {
	int n = arr.size();

	// Построение пирамиды
	// Для i от [n/2]-1 до 0 просеять элемент a[i] через пирамиду
	// из элементов a[2i+1],..., a[n-1]
	for (int i = n / 2 - 1; i >= 0; i--)
		sift(arr, n, i);

	// для i от до 1;
	for (int i = n - 1; i > 0; i--) {
		// a[0] <-> a[i];
		std::swap(arr[0], arr[i]);

		// просеять a[0] через a[1],...a[i-1]
		sift(arr, i, 0);
	}
}

// Проверка на отсортированность
bool isSorted(const std::vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		if (arr[i] < arr[i - 1]) {
			return false;
		}
	}
	return true;
}

// Вывод массива
void outputArray(const std::vector<int>& arr) {
	for (int num : arr) {
		std::cout << num << " ";
	}
	std::cout << std::endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	const int n = 10;
	std::vector<int> arr = generateRandomArray(n, 0, 100);
	outputArray(arr);


	pyramidSort(arr);
	outputArray(arr);
}