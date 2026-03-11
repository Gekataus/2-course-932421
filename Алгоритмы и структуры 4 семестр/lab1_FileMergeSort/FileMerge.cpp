#include <random>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

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

// Разбиение файла f на fa и fb по p элементов
void split(const std::string& f, const std::string& fa, const std::string& fb, int p) {
    std::ifstream fin(f);
    std::ofstream foutA(fa), foutB(fb);

    int value;
    bool toA = true;
    int count = 0;

    while (fin >> value) {
        if (toA) {
            foutA << value << " ";
        }
        else {
            foutB << value << " ";
        }
        count++;

        if (count == p) {
            toA = !toA;
            count = 0;
        }
    }
}

// Слияние файлов f1 и f2 в g1 и g2 (чередуя) по p элементов
void Merge(const std::string& f1, const std::string& f2, const std::string& g1, const std::string& g2, int p) {
    std::ifstream in1(f1), in2(f2);
    std::ofstream out1(g1), out2(g2);

    bool toFirst = true;
    int count1 = 0, count2 = 0;
    int val1, val2;
    bool has1 = false, has2 = false;

    // Читаем первые элементы
    if (in1 >> val1) has1 = true;
    if (in2 >> val2) has2 = true;

    while (has1 || has2) {
        std::ofstream& current = toFirst ? out1 : out2;
        count1 = 0;
        count2 = 0;

        // Сливаем одну серию
        while (has1 || has2) {
            // Если обе серии закончились - выходим
            if ((count1 >= p && count2 >= p) ||
                (count1 >= p && !has2) ||
                (count2 >= p && !has1)) {
                break;
            }

            // Если из первого нельзя брать (нет данных или серия кончилась)
            if (!has1 || count1 >= p) {
                if (has2 && count2 < p) {
                    current << val2 << " ";
                    count2++;
                    if (!(in2 >> val2)) has2 = false;
                }
            }
            // Если из второго нельзя брать (нет данных или серия кончилась)
            else if (!has2 || count2 >= p) {
                if (has1 && count1 < p) {
                    current << val1 << " ";
                    count1++;
                    if (!(in1 >> val1)) has1 = false;
                }
            }
            // Если можно брать из обоих - берем меньший
            else {
                if (val1 <= val2) {
                    current << val1 << " ";
                    count1++;
                    if (!(in1 >> val1)) has1 = false;
                }
                else {
                    current << val2 << " ";
                    count2++;
                    if (!(in2 >> val2)) has2 = false;
                }
            }
        }

        toFirst = !toFirst;
    }
}

// Прямая сортировка слиянием
void StraightMergeSort(const std::string& input) {
    const std::string fa = "fa.txt", fb = "fb.txt", fc = "fc.txt", fd = "fd.txt";

    int p = 1;
    bool stage2 = true; // true - шаг 2, false - шаг 3
    split(input, fa, fb, p);

    while (true) {
        if (stage2) {
            // Шаг 2: Слияние из fa и fb в fc и fd
            Merge(fa, fb, fc, fd, p);

            // Проверка условия окончания
            if (IsFileEmpty(fb)) {
                // Результат в fc
                CopyFile(fc, fa);
                break;
            }

            p *= 2;
            stage2 = false;
        }
        else {
            // Шаг 3: Слияние из fc и fd в fa и fb
            Merge(fc, fd, fa, fb, p);

            // Проверка условия окончания
            if (IsFileEmpty(fd)) {
                // Результат в fa
                break;
            }

            p *= 2;
            stage2 = true;
        }
    }
}

// Разбиение файла f на fa и fb по естественным упорядоченным отрезкам
void NaturalSplit(const std::string& f, const std::string& fa, const std::string& fb) {
    std::ifstream fin(f);
    std::ofstream foutA(fa), foutB(fb);

    int curr, prev;
    bool writeToA = true;
    bool first = true;

    if (!(fin >> curr)) return; // Пустой файл

    prev = curr;
    foutA << curr << " ";

    while (fin >> curr) {
        // Если нарушается упорядоченность - переключаем файл
        if (curr < prev) {
            writeToA = !writeToA;
        }

        if (writeToA)
            foutA << curr << " ";
        else
            foutB << curr << " ";

        prev = curr;
    }
}

// Слияние по естественным упорядоченным отрезкам
void NaturalMerge(const std::string& in1, const std::string& in2,
    const std::string& out1, const std::string& out2) {
    std::ifstream f1(in1), f2(in2);
    std::ofstream fout1(out1), fout2(out2);

    bool writeToFirst = true;
    int a, b;
    bool hasA = false, hasB = false;

    // Флаги: true = серия закончилась
    bool seriesEndedA = false, seriesEndedB = false;
    int prevA, prevB;

    // Читаем первые элементы
    if (f1 >> a) {
        hasA = true;
        prevA = a;
    }
    if (f2 >> b) {
        hasB = true;
        prevB = b;
    }

    while (hasA || hasB) {
        std::ofstream& current = writeToFirst ? fout1 : fout2;

        // Сливаем одну серию
        while (hasA || hasB) {
            // Если обе серии закончились - выходим
            if (seriesEndedA && seriesEndedB) {
                break;
            }

            // Случай 1: можно брать только из A
            if (hasA && !seriesEndedA && (!hasB || seriesEndedB)) {
                current << a << " ";
                prevA = a;

                if (f1 >> a) {
                    hasA = true;
                    if (a < prevA) seriesEndedA = true;
                }
                else {
                    hasA = false;
                    seriesEndedA = true;
                }
            }
            // Случай 2: можно брать только из B
            else if (hasB && !seriesEndedB && (!hasA || seriesEndedA)) {
                current << b << " ";
                prevB = b;

                if (f2 >> b) {
                    hasB = true;
                    if (b < prevB) seriesEndedB = true;
                }
                else {
                    hasB = false;
                    seriesEndedB = true;
                }
            }
            // Случай 3: можно брать из обоих - берем меньший
            else if (hasA && !seriesEndedA && hasB && !seriesEndedB) {
                if (a <= b) {
                    current << a << " ";
                    prevA = a;

                    if (f1 >> a) {
                        hasA = true;
                        if (a < prevA) seriesEndedA = true;
                    }
                    else {
                        hasA = false;
                        seriesEndedA = true;
                    }
                }
                else {
                    current << b << " ";
                    prevB = b;

                    if (f2 >> b) {
                        hasB = true;
                        if (b < prevB) seriesEndedB = true;
                    }
                    else {
                        hasB = false;
                        seriesEndedB = true;
                    }
                }
            }
            else {
                break; // Не можем взять ниоткуда
            }
        }

        // Переключаем выходной файл для следующей серии
        writeToFirst = !writeToFirst;
        seriesEndedA = false;
        seriesEndedB = false;
    }
}

//Сортировка естественным слиянием
void NaturalMergeSort(const std::string& input) {
    const std::string fa = "fa.txt", fb = "fb.txt", fc = "fc.txt", fd = "fd.txt";

    // Шаг 1: разбиение исходного файла естественными сериями
    NaturalSplit(input, fa, fb);

    bool useAB = true;

    while (true) {
        if (useAB) {
            NaturalMerge(fa, fb, fc, fd);

            if (IsFileEmpty(fb)) {
                CopyFile(fc, fa);
                break;
            }
            useAB = false;
        }
        else {
            NaturalMerge(fc, fd, fa, fb);

            if (IsFileEmpty(fd)) {
                break;
            }
            useAB = true;
        }
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
    std::string filename = "custom_array.txt"; // Фиксированное имя файла
    int length, minVal, maxVal;

    std::cout << "\n    Создание файла со случайным массивом    " << std::endl;
    std::cout << "Файл будет сохранен как: " << filename << std::endl;
    std::cout << "Введите длину массива: ";
    std::cin >> length;
    std::cout << "Введите минимальное значение: ";
    std::cin >> minVal;
    std::cout << "Введите максимальное значение: ";
    std::cin >> maxVal;

    if (length <= 0) {
        std::cout << "Ошибка: длина массива должна быть положительной" << std::endl;
        return;
    }

    if (minVal > maxVal) {
        std::cout << "Ошибка: минимальное значение не может быть больше максимального" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);

    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cout << "Error: couldn't create file" << std::endl;
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

    std::vector<std::string> filenames = {
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

    std::cout << "Сортировка слиянием на четырех файлах\n" << std::endl;
    while (true)
    {
        std::cout << "\n1. Прямая сортировка" << std::endl;
        std::cout << "2. Естественная сортировка" << std::endl;
        std::cout << "0. Завершить работу" << std::endl;
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
                auto start = std::chrono::high_resolution_clock::now();
                MergeSort(filenames[y - 1], x);
                auto stop = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = stop - start;
                std::cout << (isFileContainsSortedArray("fa.txt") ?
                    "Файл отсортирован, результат в 'fa.txt'\n" :
                    "Файл не отсортирован, произошла ошибка\n");
                std::cout << "Время сортировки: " << duration.count() << " сек." << std::endl;
            }
            else if (y == 10) {
                CreateRandomArrayFile();
                std::string customFile = "custom_array.txt";
                auto start = std::chrono::high_resolution_clock::now();
                MergeSort(customFile, x);
                auto stop = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = stop - start;
                std::cout << (isFileContainsSortedArray("fa.txt") ?
                    "Файл отсортирован, результат в 'fa.txt'\n" :
                    "Файл не отсортирован, произошла ошибка\n");
                std::cout << "Время сортировки: " << duration.count() << " сек." << std::endl;
            }
            else {
                std::cout << "Неверный ввод" << std::endl;
            }
            break;

        case 0:
            std::cout << "Программа завершена." << std::endl;
            exit(0);

        default:
            std::cout << "Неверный ввод" << std::endl;
            break;
        }
    }
}