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

// Функция слияния двух файлов в два выходных файла
void MergeFiles(const std::string & input1, const std::string & input2, const std::string & output1, const std::string & output2, int p) {
    std::ifstream fin1(input1);
    std::ifstream fin2(input2);
    std::ofstream fout1(output1);
    std::ofstream fout2(output2);

    if (!fin1.is_open() || !fin2.is_open() || !fout1.is_open() || !fout2.is_open()) {
        std::cout << "Error: couldn't open files for merging" << std::endl;
        return;
    }

    bool writeToFirst = true;
    std::vector<int> buffer;

    // Пока есть данные хотя бы в одном файле
    while (!fin1.eof() || !fin2.eof()) {
        buffer.clear();

        // Читаем p чисел из первого файла
        int val;
        int count = 0;
        while (count < p && fin1 >> val) {
            buffer.push_back(val);
            count++;
        }

        // Читаем p чисел из второго файла
        count = 0;
        while (count < p && fin2 >> val) {
            buffer.push_back(val);
            count++;
        }

        // Если буфер пуст, выходим
        if (buffer.empty()) {
            break;
        }

        // Сортируем буфер (2*p элементов или меньше в конце)
        std::sort(buffer.begin(), buffer.end());

        // Записываем в соответствующий выходной файл
        if (writeToFirst) {
            for (int num : buffer) {
                fout1 << num << " ";
            }
        }
        else {
            for (int num : buffer) {
                fout2 << num << " ";
            }
        }

        // Переключаем выходной файл для следующей серии
        writeToFirst = !writeToFirst;
    }

    fin1.close();
    fin2.close();
    fout1.close();
    fout2.close();
}

// Пустой ли файл
bool IsFileEmpty(const std::string& filename) {
    std::ifstream file(filename);
    bool empty = file.peek() == std::ifstream::traits_type::eof();
    file.close();
    return empty;
}

// Копирование файла
void CopyFile(const std::string& source, const std::string& destination) {
    std::ifstream src(source);
    std::ofstream dst(destination);
    int val;
    while (src >> val) {
        dst << val << " ";
    }
    src.close();
    dst.close();
}

//Прямая сортировка
void StraightMergeSort(const std::string& fileName) {
    std::ifstream fin(fileName);
    std::ofstream foutA("fa.txt");
    std::ofstream foutB("fb.txt");

    if (!fin.is_open()) {
        std::cout << "Error: couldn't read from file" << std::endl;
        return;
    }
    if (!foutA.is_open() || !foutB.is_open()) {
        std::cout << "Error: couldn't open files" << std::endl;
        return;
    }

    // 1. Разбиение
    int value = 0;
    bool writeInA = true;
    while (fin >> value) {
        if (writeInA) {
            foutA << value << " ";
            writeInA = !writeInA;
        }
        else {
            foutB << value << " ";
            writeInA = !writeInA;
        }
    }
    fin.close();
    foutA.close();
    foutB.close();

    // Слияние
    int p = 1;
    bool useAB = true;

    while (true) {
        if (useAB) {
            // 2. Слияние из fa и fb в fc и fd
            MergeFiles("fa.txt", "fb.txt", "fc.txt", "fd.txt", p);

            // Проверяем, закончили ли сортировку (пустой ли fb.txt?)
            if (IsFileEmpty("fb.txt")) {
                // Результат в fa.txt - копируем из fc.txt
                CopyFile("fc.txt", "fa.txt");
                break;
            }
        }
        else {
            // 3. Слияние из fc и fd в fa и fb
            MergeFiles("fc.txt", "fd.txt", "fa.txt", "fb.txt", p);

            // Проверяем, закончили ли сортировку (пустой ли fd.txt?)
            if (IsFileEmpty("fd.txt")) {
                // Результат в fc.txt - копируем в fa.txt
                CopyFile("fc.txt", "fa.txt");
                break;
            }
        }

        p *= 2;
        useAB = !useAB; // Переключаем пары файлов
    }
}

//Естественная сортировка
void NaturalMergeSort()
{
};

//Сортировка слиянием
void MergeSort(const std::string& fileName, const int x) {
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

    MergeSort(filenames[1], 1);
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