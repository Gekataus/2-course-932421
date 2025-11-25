#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

//создание массива случайных чисел (Библиотека random)
vector<int> generateRandomArray(int size, int min_val, int max_val) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(min_val, max_val);

	vector<int> arr(size);
	for (int i = 0; i < size; i++) {
		arr[i] = distrib(gen);
	}
	return arr;
}

// Вывод массива
void outputArray(const vector<int>& arr) {
	for (int num : arr) {
		cout << num << " ";
	}
	cout << endl;
}

// Проверка на отсортированность
bool isSorted(vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		if (arr[i] < arr[i - 1]) {
			return false;
		}
	}
	return true;
}

// Загрузка массива из файла
vector<int> loadArrayFromFile(const string& filename) {
	vector<int> arr;
	ifstream file(filename);
	int value;

	if (file.is_open()) {
		while (file >> value) {
			arr.push_back(value);
		}
		file.close();
	}

	return arr;
}

// Получение k-го бита числа
int getBit(int num, int k) {
	unsigned int unsigned_num = static_cast<unsigned int>(num);
	return (unsigned_num >> k) & 1;
}

// Рекурсивная функция побитовой сортировки
void bitwiseSort(vector<int>& arr, int l, int r, int k) {
	if (l >= r || k < 0) {
		return;
	}

	int i = l;
	int j = r;

	// Разделяем отрицательные и положительные числа (отриц - влево, положит - вправо)
	if (k == sizeof(int) * 8 - 1) {
		// отрицательное число - бит = 1
		// положительное число - бит = 0
		while (i <= j) {
			while (i <= j && getBit(arr[i], k) == 1) { // отрицательные
				i++;
			}
			while (i <= j && getBit(arr[j], k) == 0) { // положительные
				j--;
			}
			if (i < j) {
				std::swap(arr[i], arr[j]);
				i++;
				j--;
			}
		}
	}
	else {
		// Для остальных битов - обычный алгоритм
		while (i <= j) {
			while (i <= j && getBit(arr[i], k) == 0) {
				i++;
			}

			while (i <= j && getBit(arr[j], k) == 1) {
				j--;
			}

			if (i < j) {
				std::swap(arr[i], arr[j]);
				i++;
				j--;
			}
		}
	}

	// Рекурсивные вызовы
	bitwiseSort(arr, l, j, k - 1);
	bitwiseSort(arr, i, r, k - 1);
}

// Функция для измерения времени выполнения сортировки
double SortingTime(vector<int>& arr, int l, int r, int k) {
	chrono::high_resolution_clock::time_point timeStart = chrono::high_resolution_clock::now();
	bitwiseSort(arr, l, r, k);
	chrono::high_resolution_clock::time_point timeEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = (timeEnd - timeStart);
	return duration.count();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int max_bit = sizeof(int) * 8 - 1;
	int x, n, min_val, max_val;
	double time = 0;
	vector<string> filenames = {
		"array_10000_-10_10.txt",
		"array_10000_-1000_1000.txt",
		"array_10000_-100000_100000.txt",
		"array_100000_-10_10.txt",
		"array_100000_-1000_1000.txt",
		"array_100000_-100000_100000.txt",
		"array_1000000_-10_10.txt",
		"array_1000000_-1000_1000.txt",
		"array_1000000_-100000_100000.txt"
	};
	for (;;) {
		cout << "Над каким массивом выполнять сортировку? Введите цифру: " << endl;
		cout << "1. Создать рандомный массив" << endl;
		cout << "2. Выполнить сортировку тестовых массивов из файлов" << endl;
		cout << "-1. Прекратить сортировку" << endl;
		cin >> x;
		if (x == -1) exit(0);
		if (x == 1)
		{
			vector<int> arr1;
			cout << "Введите длинну массива, минимальное и максимальное значение: ";
			cin >> n >> min_val >> max_val;
			arr1 = generateRandomArray(n, min_val, max_val);
			cout << "Ваш массив:" << endl;
			outputArray(arr1);
			bitwiseSort(arr1, 0, n - 1, max_bit);
			cout << "Отсортированный массив: " << endl;
			outputArray(arr1);
			cout << "Массив отсортирован?: " << (isSorted(arr1) ? "Да" : "Нет") << endl << endl;
		}
		if (x == 2) {
			for (int i = 0; i < filenames.size(); i++) {
				string filename = filenames[i];
				vector<int> arr = loadArrayFromFile(filename);
				n = arr.size();
				cout << "Сортировка массива из файла " << filename << endl;
				time = SortingTime(arr, 0, n - 1, max_bit);
				cout << "Массив отсортирован?: " << (isSorted(arr) ? "Да" : "Нет") << endl;
				cout << "Время сортировки: " << time << endl << endl;
			}
		}
	}
	return 0;
}