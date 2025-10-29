#include <iostream>
#include <vector>
#include <random>
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

// Сортировка Шелла с последовательностью Шелла
void shellSort(vector<int>& arr) {
	int n = arr.size();
	//Изменяем шаги
	for (int gap = n / 2; gap > 0; gap /= 2) {
		// Выполняем сортировку вставками для этого шага
		for (int i = gap; i < n; i++) {
			int temp = arr[i];
			int j;
			// Сдвигаем элементы, пока не найдем правильную позицию для arr[i]
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}
int main() 
{
	vector<int> arr1 = generateRandomArray(20, 0, 99);
	outputArray(arr1);

	shellSort(arr1);
	outputArray(arr1);

	

}
