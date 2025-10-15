#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <chrono>

// Загрузка массива из файла
std::vector<int> loadArrayFromFile(const std::string& filename) {
	std::vector<int> arr;
	std::ifstream file(filename);
	int value;

	if (file.is_open()) {
		while (file >> value) {
			arr.push_back(value);
		}
		file.close();
	}

	return arr;
}

// Сохранение массива в файл
void saveArrayToFile(const std::vector<int>& arr, const std::string& filename) {
	std::ofstream outfile(filename);
	if (!outfile.is_open()) {
		std::cerr << "Не удалось открыть файл " << filename << " на запись\n";
		return;
	}

	// Записываем элементы массива
	for (size_t i = 0; i < arr.size(); i++) {
		outfile << arr[i];
		if (i < arr.size() - 1) {
			outfile << " ";
		}
	}
	outfile << std::endl;
	outfile.close();
	std::cout << "Массив сохранен в файл: " << filename << std::endl;
}



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
void sift(std::vector<int>& arr, int start, int end) 
{
	int root = start;
	while (2 * root + 1 <= end) {  // Пока есть хотя бы левый потомок
		int leftChild = 2 * root + 1;
		int rightChild = 2 * root + 2;
		int swapIndex = root;              // начинаем обменивать с корня

		// Сравниваем с левым потомком
		if (arr[swapIndex] < arr[leftChild])
			swapIndex = leftChild;

		// Сравниваем с правым потомком (если он существует)
		if (rightChild <= end && arr[swapIndex] < arr[rightChild])
			swapIndex = rightChild;

		if (swapIndex == root)
			return;

		std::swap(arr[root], arr[swapIndex]);
		root = swapIndex;
	}
}
	// Этап 1: построение пирамиды
	void buildHeap(std::vector<int>&arr)
	{
		int n = arr.size();
		// просеивание половины массива
		for (int i = n / 2 - 1; i >= 0; i--) 
		{
			sift(arr, i, n - 1);
		}
	}

	// Этап 2: сортировка 
	void heapSort(std::vector<int>&arr) {
		int n = arr.size();
		buildHeap(arr);
		for (int i = n - 1; i > 0; i--) {        // i - индекс последнего элемента в еще не отсортированной части массива 
			std::swap(arr[0], arr[i]);
			sift(arr, 0, i - 1);
		}
	}

// Проверка на отсортированность
bool isSorted(std::vector<int>& arr) {
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
	//Сохранение массивов в файлы
	/*
	int n = 0, a = 0, b = 0;
	int fileCounter = 1;
	std::vector<int> arr;
	for (;;)
	{
		std::cout << "\n\nВведите размерность массива: "; std::cin >> n;
		if (n == -1) break;
		std::cout << "Введите min границу диапазона: "; std::cin >> a;
		std::cout << "Введите max границу диапазона: "; std::cin >> b;
		arr = generateRandomArray(n, a, b);
		
		std::string filename = "array_" + std::to_string(fileCounter) + ".txt";
		fileCounter++;
		
		//std::cout << "Сгенерированный массив: " << std::endl;
		//outputArray(arr);
		saveArrayToFile(arr, filename);
	}
	*/

	//Чтение из файла
	int left = 0, right = 0, n = 0;
	std::string filename;

	for (;;)
	{
		std::cout << "Введите размер массива (10000 || 100000 || 1000000): "; std::cin >> n;
		if (n == -1) break;
		std::cout << "Введите диапазон массива (-10/10 || -1000/1000 || -100000/100000): "; std::cin >> left >> right;
		filename = "array_" + std::to_string(n) + "_" + std::to_string(left) + "_" + std::to_string(right) + ".txt";
		std::cout << "Сортировка массива из файла " << filename << std::endl;
		std::vector<int> arr = loadArrayFromFile(filename);

		std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
		buildHeap(arr);
		heapSort(arr);
		std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = timeEnd - timeStart;

		if (isSorted(arr)) std::cout << "Массив отсортирован" << std::endl;
		std::cout << "Время сортировки = " << duration.count() << " с." << std::endl;
		std::cout << std::endl;

	}


}