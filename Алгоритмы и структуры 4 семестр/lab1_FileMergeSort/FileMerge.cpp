#include <random>
#include <fstream>
#include <iostream>

using namespace std;


//Проверка файла на упорядоченность
bool isFileContainsSortedArray(const std::string& fileName)
{
	std::fstream outputFile(fileName);
	int value1 = 0, value2 = 0;

	outputFile >> value1;
	while (outputFile >> value2) {
		if (value1 > value2)
			return false;
		value1 = value2;
	}
	return true;
};

//Прямая сортировка
void StraightMergeSort(const std::string& fileName)
{
	std::fstream f(fileName, ios::out);
	std::fstream fa("fa.txt");
	std::fstream fb("fb.txt");
	std::fstream fc("fc.txt");
	std::fstream fd("fd.txt");
	int p = 1;
	int value = 0;
	while(f >> value)
	for (int i = 0; i < p; i++)
	{

	}
};

//Естественная сортировка
void NaturalMergeSort()
{
};

//Сортировка слиянием
void MergeSort(const std::string& fileName, const int numbersCount, const int maxNumberValue, const int x) {
	switch (x)
	{
	case 1:
		StraightMergeSort(fileName);
		break;
	case 2:
		NaturalMergeSort();
		break;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int x = -1, y = -1;

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

	std::cout << "Сортировка слиянием на четырех файлах" << endl;
	/*while (true)
	{
		std::cout << "\nКакую сортировку выполнить?" << endl;
		std::cout << "1. Прямая сортировка" << endl;
		std::cout << "2. Естественная сортировка" << endl;
		std::cout << "0. Завершить работу" << endl;
		std::cout << "Введите цифру: "; std::cin >> x;
	}*/
}