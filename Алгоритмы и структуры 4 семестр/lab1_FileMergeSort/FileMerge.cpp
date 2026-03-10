#include <random>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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

// Разбиение для естественного слияния
void NaturalSplit(const std::string& f, const std::string& fa, const std::string& fb) {
    std::ifstream fin(f);
    std::ofstream foutA(fa), foutB(fb);

    if (!fin.is_open() || !foutA.is_open() || !foutB.is_open()) {
        std::cout << "Error: cannot open files for natural split\n";
        return;
    }

    int current, prev;
    bool writeToA = true;
    bool first = true;

    while (fin >> current) {
        if (first) {
            // Первый элемент всегда идёт в текущий файл
            first = false;
        }
        else {
            // Если нарушается упорядоченность — переключаем файл
            if (current < prev) {
                writeToA = !writeToA;
            }
        }

        if (writeToA)
            foutA << current << " ";
        else
            foutB << current << " ";

        prev = current;
    }

    fin.close();
    foutA.close();
    foutB.close();
}

// Слияние двух файлов в два выходных естественными сериями
void NaturalMerge(const std::string& in1, const std::string& in2,
    const std::string& out1, const std::string& out2) {
    std::ifstream f1(in1), f2(in2);
    std::ofstream fout1(out1), fout2(out2);

    if (!f1.is_open() || !f2.is_open() || !fout1.is_open() || !fout2.is_open()) {
        std::cout << "Error: cannot open files for natural merge\n";
        return;
    }

    bool writeToFirst = true;
    int a, b;
    bool hasA = false, hasB = false;
    bool endA = false, endB = false; // флаги конца текущей серии

    // Читаем первые элементы
    if (f1 >> a) hasA = true;
    if (f2 >> b) hasB = true;

    while (hasA || hasB) {
        std::vector<int> merged;
        int lastA, lastB;
        bool firstA = true, firstB = true;

        // Сливаем одну серию
        while (hasA || hasB) {
            // Выбираем откуда брать элемент
            if (hasA && (!hasB || a <= b)) {
                // Берем из первого файла
                merged.push_back(a);
                lastA = a;

                // Читаем следующий из первого файла
                if (f1 >> a) {
                    // Проверяем, кончилась ли серия в первом файле
                    if (a < lastA) {
                        hasA = false;
                        endA = true;
                    }
                }
                else {
                    hasA = false;
                }
            }
            else if (hasB) {
                // Берем из второго файла
                merged.push_back(b);
                lastB = b;

                // Читаем следующий из второго файла
                if (f2 >> b) {
                    // Проверяем, кончилась ли серия во втором файле
                    if (b < lastB) {
                        hasB = false; // временно убираем второй файл из обработки
                        endB = true;
                    }
                }
                else {
                    hasB = false;
                }
            }

            // Если оба файла временно недоступны (кончились серии) - выходим
            if ((!hasA || endA) && (!hasB || endB)) {
                break;
            }
        }

        // Дозаписываем остатки
        while (hasA && !endA) {
            merged.push_back(a);
            if (f1 >> a) {
                if (a < merged.back()) {
                    hasA = false;
                    endA = true;
                }
            }
            else {
                hasA = false;
            }
        }

        while (hasB && !endB) {
            merged.push_back(b);
            if (f2 >> b) {
                if (b < merged.back()) {
                    hasB = false;
                    endB = true;
                }
            }
            else {
                hasB = false;
            }
        }

        // Записываем серию в соответствующий выходной файл
        if (writeToFirst) {
            for (int x : merged) fout1 << x << " ";
        }
        else {
            for (int x : merged) fout2 << x << " ";
        }

        writeToFirst = !writeToFirst;

        // Восстанавливаем флаги для следующей итерации
        if (endA) {
            endA = false;
            hasA = true; // a уже считан и хранится
        }
        if (endB) {
            endB = false;
            hasB = true; // b уже считан и хранится
        }
    }

    f1.close();
    f2.close();
    fout1.close();
    fout2.close();
}

// Естественная сортировка слиянием
void NaturalMergeSort(const std::string& inputFile) {
    const std::string fa = "fa.txt", fb = "fb.txt", fc = "fc.txt", fd = "fd.txt";

    // Шаг 1: разбиение исходного файла естественными сериями
    NaturalSplit(inputFile, fa, fb);

    bool useAB = true;  // true: сливаем fa и fb в fc и fd; false: сливаем fc и fd в fa и fb

    while (true) {
        if (useAB) {
            // Шаг 2: слияние из fa и fb в fc и fd
            NaturalMerge(fa, fb, fc, fd);

            // Если fb оказался пустым — сортировка завершена, результат в fa
            if (IsFileEmpty(fb)) {
                break;
            }
        }
        else {
            // Шаг 3: слияние из fc и fd в fa и fb
            NaturalMerge(fc, fd, fa, fb);
            // Если fd пуст — результат в fc, копируем в fa
            if (IsFileEmpty(fd)) {
                CopyFile(fc, fa);
                break;
            }
        }
        // Переключаем пары для следующего прохода
        useAB = !useAB;
    }
}

//Сортировка слиянием
void MergeSort(const std::string& fileName, const int x) {
	switch (x)
	{
	case 1:
		StraightMergeSort(fileName);
		break;
	case 2:
		NaturalMergeSort(fileName);
		break;
	}
};

// Функция для создания файла со случайными числами (всегда с одним именем)
void CreateRandomArrayFile() {
    string filename = "custom_array.txt"; // Фиксированное имя файла
    int length, minVal, maxVal;

    cout << "\n    Создание файла со случайным массивом    " << endl;
    cout << "Файл будет сохранен как: " << filename << endl;
    cout << "Введите длину массива: ";
    cin >> length;
    cout << "Введите минимальное значение: ";
    cin >> minVal;
    cout << "Введите максимальное значение: ";
    cin >> maxVal;

    if (length <= 0) {
        cout << "Ошибка: длина массива должна быть положительной" << endl;
        return;
    }

    if (minVal > maxVal) {
        cout << "Ошибка: минимальное значение не может быть больше максимального" << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);

    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Error: couldn't create file" << endl;
        return;
    }

    for (int i = 0; i < length; i++) {
        fout << dist(gen);
        if (i < length - 1) {
            fout << " ";
        }
    }

    fout.close();
}

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
        std::cout << "\nМеню:" << endl;
        std::cout << "1. Прямая сортировка" << endl;
        std::cout << "2. Естественная сортировка" << endl;
        std::cout << "0. Завершить работу" << endl;
        std::cout << "Введите цифру: ";
        std::cin >> x;

        switch (x) {
        case 1:
        case 2:
            std::cout << "\n" << (x == 1 ? "Прямая" : "Естественная") << " сортировка. Из какого файла сортировать массив?:" << std::endl;
            std::cout << "1. 'array_10000_-10_10.txt'" << std::endl;
            std::cout << "2. 'array_10000_-1000_1000.txt'" << std::endl;
            std::cout << "3. 'array_10000_-100000_100000.txt'" << std::endl;
            std::cout << "4. 'array_100000_-10_10.txt'" << std::endl;
            std::cout << "5. 'array_100000_-1000_1000.txt'" << std::endl;
            std::cout << "6. 'array_100000_-100000_100000.txt'" << std::endl;
            std::cout << "7. 'array_1000000_-10_10.txt'" << std::endl;
            std::cout << "8. 'array_1000000_-1000_1000.txt'" << std::endl;
            std::cout << "9. 'array_1000000_-100000_100000.txt'" << std::endl;
            std::cout << "10. Свой файл (custom_array.txt)" << std::endl;
            std::cout << "Введите: ";
            std::cin >> y;

            if (y >= 1 && y <= 9) {
                MergeSort(filenames[y - 1], x);
                std::cout << (isFileContainsSortedArray("fa.txt") ?
                    "Файл отсортирован, результат в 'fa.txt'\n" :
                    "Файл не отсортирован, произошла ошибка\n");
            }
            else if (y == 10) {
                CreateRandomArrayFile();
                string customFile = "custom_array.txt";
                MergeSort(customFile, x);
                std::cout << (isFileContainsSortedArray("fa.txt") ?
                    "Файл отсортирован, результат в 'fa.txt'\n" :
                    "Файл не отсортирован, произошла ошибка\n");
            }
            else {
                std::cout << "Неверный ввод" << std::endl;
            }
            break;

        case 0:
            cout << "Программа завершена." << endl;
            exit(0);

        default:
            std::cout << "Неверный ввод" << std::endl;
            break;
        }
    }
}