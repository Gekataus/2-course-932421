#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int getHighestBitPosition(int num) {
	if (num == 0) return -1; // нет установленных битов

	unsigned int unsigned_num = static_cast<unsigned int>(num < 0 ? -num : num);
	int position = 0;

	while (unsigned_num > 1) {
		unsigned_num >>= 1;
		position++;
	}

	return position;
}

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

// Функция для получения k-го бита числа
int getBit(int num, int k) {
	return (num >> k) & 1;
}

// Рекурсивная функция побитовой сортировки
void bitwiseSort(vector<int>& arr, int l, int r, int k) {
	// 1.Если l ≥ r или k < 0, то выход
	if (l >= r || k < 0) {
		return;
	}

	// 2. Установка начальных значений
	int i = l;
	int j = r;

	// 3. Разделение элементов по k-му биту
	while (i <= j) {
		// 3.1 Ищем элемент с 0 в k-м разряде слева
		while (i <= j && getBit(arr[i], k) == 0) {
			i++;
		}

		// 3.2 Ищем элемент с 1 в k-м разряде справа
		while (i <= j && getBit(arr[j], k) == 1) {
			j--;
		}

		// 3.3 Меняем местами элементы, если нужно
		if (i < j) {
			std::swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	// 4. Выполняем эту же процедуру для фрагмента [l, j] по k - 1 разряду
	bitwiseSort(arr, l, j, k - 1);

	// 5. Выполняем эту же процедуру для фрагмента [i, r] по k - 1 разряду
	bitwiseSort(arr, i, r, k - 1);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int x, n, min_val, max_val;
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
			bitwiseSort(arr1, 0, n - 1, getHighestBitPosition(max_val));
			cout << "Отсортированный массив: " << endl;
			outputArray(arr1);
			cout << "Массив отсортирован?: " << (isSorted(arr1) ? "Да" : "Нет") << endl << endl;
		}
	}




	return 0;
}