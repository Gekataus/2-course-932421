#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
#include <chrono>
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
// Функция для измерения времени выполнения сортировки
double SortingTime(vector<int> arr, const vector<int>& gaps) {
    chrono::high_resolution_clock::time_point timeStart = chrono::high_resolution_clock::now();
    shellSort(arr, gaps);
    chrono::high_resolution_clock::time_point timeEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = (timeEnd - timeStart);
    return duration.count();
}

//Тестирование сортировки на трёх алгоритмах сортировки шагов
void testArray(const vector<int>& original_arr) {

    // Генерируем последовательности шагов
    vector<int> gaps_shell = generateShell(original_arr.size());
    vector<int> gaps_two = generateTwo(original_arr.size());
    vector<int> gaps_knuth = generateKnuth(original_arr.size());

    // Тестируем каждый метод
    vector<int> arr1 = original_arr;
    vector<int> arr2 = original_arr;
    vector<int> arr3 = original_arr;

    // Метод 1: Последовательность Шелла (n/2, n/4, ..., 1)
    double time1 = SortingTime(original_arr, gaps_shell);
    shellSort(arr1, gaps_shell);
    bool sorted1 = isSorted(arr1);

    // Метод 2: Последовательность 2^m - 1
    double time2 = SortingTime(original_arr, gaps_two);
    shellSort(arr2, gaps_two);
    bool sorted2 = isSorted(arr2);

    // Метод 3: Последовательность Кнута
    double time3 = SortingTime(original_arr, gaps_knuth);
    shellSort(arr3, gaps_knuth);
    bool sorted3 = isSorted(arr3);

    // Выводим результаты
    cout << "Метод 1 (Шелл): " << time1 << " с, отсортирован: " << (sorted1 ? "да" : "нет") << endl;
    cout << "Метод 2 (2^m-1): " << time2 << " с, отсортирован: " << (sorted2 ? "да" : "нет") << endl;
    cout << "Метод 3 (Кнут): " << time3 << " с, отсортирован: " << (sorted3 ? "да" : "нет") << endl;
    cout << endl;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int x;
    vector<int> arr1;
    vector<int> h;
    cout << "Брать массив с файла или сгенерировать вручную с консоли? Введите:" << endl << "С консоли - 1" << endl << "С файла - 2" << endl;
    cin >> x;
    if (x == 1) {
        while (true) {
            if (x == -1) break;
            int n, min, max;
            cout << "Введите длинну массива, минимальную и максимальную границу" << endl;
            cin >> n >> min >> max;
            arr1 = generateRandomArray(n, min, max);
            cout << "Ваш массив:" << endl;
            outputArray(arr1);

            cout << "Как формировать шаги?" << endl << "1. Последовательность Шелла" << endl << "2. Возведение 2 в степень m" << endl << "3.Последовательность Кнута" << endl;
            cin >> x;
            if (x == 1) h = generateShell(n);
            if (x == 2) h = generateTwo(n);
            if (x == 3) h = generateKnuth(n);
            std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
            shellSort(arr1, h);
            std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = timeEnd - timeStart;

            if (isSorted(arr1)) {
                cout << "Массив отсортирован" << endl;
                if (n < 100) {
                    cout << "Отсортированный массив:" << endl;
                    outputArray(arr1);
                }
                cout << "\nВремя сортировки : " << duration.count() << " с." << std::endl;
            }
            cout << "Если хотите создать новый массив и отсортировать его, введите 1, если хотите завершить, введите -1" << endl;
            cin >> x;
        }
    }
    if (x == 2) {
        vector<string> filenames = { "array_10000_-10_10.txt", "array_10000_-1000_1000.txt", "array_10000_-100000_100000.txt", "array_100000_-10_10.txt", "array_100000_-1000_1000.txt", "array_100000_-100000_100000.txt", "array_1000000_-10_10.txt", "array_1000000_-1000_1000.txt", "array_1000000_-100000_100000.txt"};
        for (int i = 0; i < filenames.size(); i++) {
            string filename = filenames[i];
            cout << "Сортировка массива из файла " << filename << endl;
            vector<int> arr = loadArrayFromFile(filename);
            testArray(arr);
        }
    }
}
