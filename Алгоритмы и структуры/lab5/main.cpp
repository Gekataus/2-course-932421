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

void HoarSort(vector<int>& arr, int n, int min, int max)
{	
	int i = 0, j = n - 1;
	if (i >= j || min == max) exit;
	float xm = (min + max) / 2;
	while (i <= j)
	{
		while (i <= j && arr[i] < xm) i++;
		while (j >= i && arr[j] >= xm) j--;
		if (i < j)
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	HoarSort(arr, n, min, xm-0.5);
	HoarSort(arr, n, xm+0.5, max);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int n, min, max;
	cin >> n >> min >> max;
	vector<int> arr1 = generateRandomArray(n, min, max);
	outputArray(arr1);
	HoarSort(arr1, n, min, max);
	outputArray(arr1);

}