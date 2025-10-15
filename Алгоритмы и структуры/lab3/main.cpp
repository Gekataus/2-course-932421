#include <iostream>
#include <vector>
#include <random>
#include <fstream>


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
	int max = i;// считаем элемент наиб
	int left = 2 * i + 1;   // Левый потомок
	int right = 2 * i + 2;  // Правый потомок

	// Если левый потомок существует и больше max
	if (left < n && arr[left] > arr[max])
		max = left;

	// Если правый потомок существует и больше max
	if (right < n && arr[right] > arr[max])
		max = right;

	// Если max не корень
	if (max != i) 
	{
		std::swap(arr[i], arr[max]);

		//Просеиваем
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
	int n = 0, a = 0, b = 0;
	std::vector<int> arr;
	for( ; ; )
	{
		std::cout << "Введите размерность массива: "; std::cin >> n; std::cout << std::endl;
		if (n == -1) break;
		std::cout << "Введите min границу диапазона: "; std::cin >> a; std::cout << std::endl;
		std::cout << "Введите max границу диапазона: "; std::cin >> b; std::cout << std::endl;
		arr = generateRandomArray(n, a, b);
		std::cout << "Сгенерированный массив: " << std::endl;
		outputArray(arr);
		pyramidSort(arr);
		std::cout << "Отсортированный массив: " << std::endl;
		outputArray(arr);
	}

}