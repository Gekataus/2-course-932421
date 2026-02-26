#include <random>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


//Проверка файла на упорядоченность
int isFileContainsSortedArray(const std::string& fileName)
{
	std::fstream outputFile(fileName);
	if (!outputFile.is_open()) {
		std::cout << "Error: couldn't read from file in function 'isFileContainsSortedArray." << std::endl;
		return -1;
	}
	int value1 = 0, value2 = 0;

	outputFile >> value1;
	while (outputFile >> value2) {
		if (value1 > value2)
			return 0;
		value1 = value2;
	}
	return 1;
};

//Разбиение
void split(const std::string& readingFile, const std::string& firstFile, const std::string& secondFile, const int p) {
	std::ifstream outputFile(readingFile);
	std::ofstream fileA(firstFile), fileB(secondFile);
	
	if (!outputFile.is_open() || !fileA.is_open() || !fileB.is_open()) {
		std::cout << "Error: couldn't read from files in function 'split'." << std::endl;
		return;
	}
	int value;
	bool writeToA = true;

	while (outputFile >> value) {
		for (int i = 0; i < p && outputFile; i++) {
			if (writeToA) fileA << value << " ";
			else fileB << value << " ";
			writeToA = !writeToA;
			if (i < p - 1)
				if (!(outputFile >> value)) 
					break;
		}
	}
}

//Слияние
void merge(const std::string& readingFile1, const std::string& readingFile2, const std::string& writingFile1, const std::string& writingFile2, const int p) {
	std::ifstream file1(readingFile1), file2(readingFile2);
	std::ofstream file3(writingFile1), file4(writingFile2);

	int value1, value2;
	while (file1 >> value1 && file2 >> value2) {
		std::vector<int> mas;
		for (int i = 0; i < p; i++)
		{
			mas.push_back(value1);
			mas.push_back(value2);
		}
		sort(mas.begin(), mas.end());

	}
}

//Прямая сортировка
void StraightMergeSort(const std::string& fileName)
{
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