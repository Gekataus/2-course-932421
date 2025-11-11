#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <iostream>
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

void HoarSort(vector<int>& arr, int l, int r, int xl, int xr) {
	if (l >= r || xl == xr) return;
	int i = l, j = r;
	float xm = (xl + xr) / 2.0f;
	while (i <= j) {
		// Ищем элемент слева, который >= xm
		while (i <= j && arr[i] < xm) i++;
		// Ищем элемент справа, который < xm
		while (j >= i && arr[j] >= xm) j--;
		// Если нашли пару для обмена
		if (i < j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	// от xl до xm
	if (l <= j) {
		HoarSort(arr, l, j, xl, (int)xm);
	}
	// от xm до xr
	if (i <= r) {
		HoarSort(arr, i, r, (int)(xm + 0.5), xr);
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int n, min, max;
	cin >> n >> min >> max;
	vector<int> arr1 = generateRandomArray(n, min, max);
	
	vector<string> filenames = {
		"array_10000_-10_10",
		"array_10000_-1000_1000",
		"array_10000_-100000_100000",
		"array_100000_-10_10",
		"array_100000_-1000_1000",
		"array_100000_-100000_100000",
		"array_1000000_-10_10",
		"array_1000000_-1000_1000",
		"array_1000000_-100000_100000"
	};
	for (int i = 0; i < filenames.size(); i++) {
		string filename = filenames[i];

	}
	return 0;
}