#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
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

// 1. Последовательность Шелла (h[0]0 = n/2, h[i] = h[i-1]/2, ..., h[t] = 1)
vector<int> generateShell(int n) {
    vector<int> gaps;
    int h = n / 2;

    while (h > 0) {
        gaps.push_back(h);
        h /= 2;
    }

    return gaps;
}

// 2. Последовательность вида h[m] = 2^m - 1 при m = 1, 2, ..., t = log2(n)
vector<int> generateTwo(int n) {
    vector<int> gaps;
    int t = log2(n);

    // m = 1, 2, ..., t (в порядке убывания)
    for (int m = t; m >= 1; m--) {
        int h_m = pow(2, m) - 1;
        gaps.push_back(h_m);
    }

    return gaps;
}

// 3. Последовательность Кнута: h[i] = 1, h[j+1] = 3h[j] + 1 для j = 1, 2, ..., t-1
vector<int> generateKnuth(int n) {
    vector<int> gaps;

    // Начинаем с h[i] = 1
    int h_j = 1;
    gaps.push_back(h_j);

    // Вычисляем h[j+1] = 3h[j] + 1 пока h[j+1] < n
    // j = 1, 2, ..., t-1 (t - количество элементов в последовательности)
    while (true) {
        int h_j_plus_1 = 3 * h_j + 1;  // h[j+1] = 3h[j] + 1
        if (h_j_plus_1 >= n) {
            break;
        }
        gaps.push_back(h_j_plus_1);
        h_j = h_j_plus_1;
    }

    // Реверсируем для использования от большего к меньшему
    reverse(gaps.begin(), gaps.end());

    return gaps;
}

//Сортировка Шелла
void shellSort(vector<int>& arr, const vector<int>& gaps) {
    int n = arr.size();

    for (int gap : gaps) {
        // Сортировка вставками с данным шагом
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            // Сдвигаем элементы, пока не найдем правильную позицию
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
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
int main()
{
    setlocale(LC_ALL, "Russian");
    int x;
    vector<int> arr1;
    cout << "Брать массив с файла или сгенерировать вручную с консоли?" << endl << "С консоли - 1" << endl << "С файла - 2" << endl;
    cin >> x;
    if (x == 1) {
        while (true) {
            if (x == -1) break;
            int n, min, max;
            cout << "Введите длинну массива, минимальную и максимальную границу" << endl;
            cin >> n >> min >> max;
            vector<int> arr1 = generateRandomArray(n, min, max);
            cout << "Ваш массив:" << endl;
            outputArray(arr1);

            vector<int> h;
            cout << "Как формировать шаги?" << endl << "1. Последовательность Шелла" << endl << "2. Возведение 2 в степень m" << endl << "3.Последовательность Кнута" << endl;
            cin >> x;
            if (x == 1) h = generateShell(n);
            if (x == 2) h = generateTwo(n);
            if (x == 3) h = generateKnuth(n);
            shellSort(arr1, h);

            if (isSorted(arr1)) {
                cout << "Массив отсортирован" << endl;
                if (n < 100) {
                    cout << "Отсортированный массив:" << endl;
                    outputArray(arr1);
                }
            }
            cout << "Если хотите создать новый массив и отсортировать его, введите 1, если хотите завершить, введите -1" << endl;
            cin >> x;
        }
    }
    if (x == 2) {
        while (true) {
            int y;
            cout << "Из какого файла брать массив?" << endl;
            cout << "1. array_10000_-10_10.txt" << endl;
            cout << "2. array_10000_-1000_1000.txt" << endl;
            cout << "3. array_10000_-100000_1000000.txt" << endl;
            cout << "4. array_100000_-10_10.txt" << endl;
            cout << "5. array_100000_-1000_1000.txt" << endl;
            cout << "6. array_100000_-100000_1000000.txt" << endl;
            cout << "7. array_1000000_-10_10.txt" << endl;
            cout << "8. array_1000000_-1000_1000.txt" << endl;
            cout << "9. array_1000000_-100000_1000000.txt" << endl;
            cout << "Если хотите прекратить, введите -1" << endl;
            cin >> y;
            if (y == -1) break;
        }

    }
}
