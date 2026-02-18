#include <random>
#include <fstream>
#include <iostream>

using namespace std;

//Создание файла с рандомными числами
/*bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue)
{
};

//Проверка файла на упорядоченность
bool isFileContainsSortedArray(const std::string& fileName)
{
};*/

//Прямая сортировка
void StraightMergeSort()
{
};

//Естественная сортировка
void NaturalMergeSort()
{
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

	while (true)
	{
		std::cout << "\nКакую сортировку выполнить?" << endl;
		std::cout << "1. Прямая сортировка" << endl;
		std::cout << "2. Естественная сортировка" << endl;
		std::cout << "0. Завершить работу" << endl;
		std::cout << "Введите цифру: "; std::cin >> x;
		
		switch (x) 
		{
			case 1:
				std::cout << "\nПрямая сортировка. Выберите, на каком файле выполнять сортировку:" << endl << endl;
				std::cout << "1. Создать файл со случайными числами" << endl;
				std::cout << "2. Выбрать существующий файл" << endl;
				std::cout << "Введите цифру: "; std::cin >> y;

				switch (y)
				{
					case 1:

						break;
					case 2:

						break;
					default:

						break;
				}
				break;
			case 2:
				std::cout << "\nЕстественная сортировка. Выберите, на каком файле выполнять сортировку:" << endl << endl;
				std::cout << "1. Создать файл со случайными числами" << endl;
				std::cout << "2. Выбрать существующий файл" << endl;
				std::cout << "Введите цифру: "; std::cin >> y;

				switch (y)
				{
				case 1:

					break;
				case 2:

					break;
				default:

					break;
				}
				break;
			case 0:
				exit(0);
			default:
				std::cout << "Некорректный выбор!" << endl;
		}
	}
}