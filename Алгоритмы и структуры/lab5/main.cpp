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

// Функция быстрой сортировки (алгоритм Хоара)
void hoarSort(vector<int>& arr, int l, int r) {
	if (l >= r) return;
	int x = arr[(l + r) / 2];
	int i = l, j = r;
	while (i <= j) {
		while (arr[i] < x) i++;
		while (arr[j] > x) j--;
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	if (l < j) hoarSort(arr, l, j);
	if (i < r) hoarSort(arr, i, r);
}

// Функция для измерения времени выполнения сортировки
double SortingTime(vector<int>& arr, int l, int r) {
	chrono::high_resolution_clock::time_point timeStart = chrono::high_resolution_clock::now();
	hoarSort(arr, l, r);
	chrono::high_resolution_clock::time_point timeEnd = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = (timeEnd - timeStart);
	return duration.count();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int n, min, max;
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

	int x = 0;
	for (;;) {
		cout << "Введите цифру:" << endl << "1.Сортировать рандомный массив" << endl << "2.Сортировать из файлов" << endl << "-1 - Прекратить сортировку" << endl;
		cin >> x;
		if (x == -1) exit();
		
		if (x == 1) {
			cout << "Введите размерность массива, минимальное и максимальное значение" << endl;
			cin >> n >> min >> max;
			vector<int> arrsort = generateRandomArray(n, min, max);
			cout << "Ваш массив: " << endl; outputArray(arrsort);
			cout << "\nСортировка массива..." << endl;
			time = SortingTime(arrsort, 0, n - 1);
			cout << "Массив отсортирован?: " << (isSorted(arrsort) ? "Да" : "Нет") << endl;
			cout << "Время сортировки: " << time << endl << endl;
			cout << "Отсортированный массив: " << endl; outputArray(arrsort);
			cout << endl << endl;
		}
		
		if (x == 2) {
			for (int i = 0; i < filenames.size(); i++) {
				string filename = filenames[i];
				vector<int> arr = loadArrayFromFile(filename);
				n = arr.size();
				cout << "Сортировка массива из файла " << filename << endl;
				time = SortingTime(arr, 0, n - 1);
				cout << "Массив отсортирован?: " << (isSorted(arr) ? "Да" : "Нет") << endl;
				cout << "Время сортировки: " << time << endl << endl;
			}
		}
	}

	return 0;
}