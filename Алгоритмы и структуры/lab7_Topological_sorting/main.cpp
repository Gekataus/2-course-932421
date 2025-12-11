#include "booleanmatrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>
#include <vector>

using namespace std;
using namespace std::chrono;

// Функция для поиска столбцов без единиц (вершин без входящих рёбер)
BooleanVector findEmptyColumns(const BooleanMatrix& matrix, const BooleanVector& processedVertices) {
    int n = matrix.getRows();
    BooleanVector result(n, false);

    for (int col = 0; col < n; ++col) {
        if (processedVertices[col]) continue; // Если вершина уже обработана - пропускаем

        bool hasOnes = false;
        for (int row = 0; row < n; ++row) {
            if (matrix[row][col]) {
                hasOnes = true;
                break;
            }
        }

        if (!hasOnes) {
            result.setBit(col, true); // Не нашли единиц в столбце
        }
    }

    return result;
}

// Функция для очистки строк (удаление исходящих рёбер обработанных вершин)
void clearRows(BooleanMatrix& matrix, const BooleanVector& rowsToClear) {
    int n = matrix.getRows();

    for (int i = 0; i < n; ++i) {
        if (rowsToClear[i]) {
            for (int j = 0; j < n; ++j) {
                matrix.setBit(i, j, false);
            }
        }
    }
}

// Топологическая сортировка
vector<int> topologicalSort(const BooleanMatrix& Matrix) {
    vector<int> order;
    int n = Matrix.getRows();

    BooleanMatrix workMatrix = Matrix;
    BooleanVector processedVertices(n, false);

    while (order.size() < static_cast<size_t>(n)) {
        BooleanVector columnsWithoutOnes = findEmptyColumns(workMatrix, processedVertices);

        if (columnsWithoutOnes.getWeight() == 0) {
            throw runtime_error("Граф содержит цикл, топологическая сортировка невозможна");
        }

        // Добавляем найденные вершины в правильном порядке
        for (int i = 0; i < n; ++i) {
            if (columnsWithoutOnes[i]) {
                order.push_back(i + 1); // Сохраняем номер вершины (начиная с 1)
                processedVertices.setBit(i, true); // Помечаем вершину как пройденную
            }
        }

        clearRows(workMatrix, columnsWithoutOnes);
    }

    return order;
}

// Структура для хранения дуги графа
struct Edge {
    int from;
    int to;
};

// Построение матрицы из файла
BooleanMatrix buildMatrixFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    // Вектор для хранения рёбер
    vector<Edge> edges;
    int maxVertex = 0;
    int u, v;

    // Читаем все рёбра из файла
    while (file >> u >> v) {
        if (u == 0 && v == 0) {
            break;
        }
        if (u < 0 || v < 0) {
            file.close();
            throw runtime_error("Номера вершин должны быть положительными");
        }

        edges.push_back({ u, v });
        if (u > maxVertex) maxVertex = u;
        if (v > maxVertex) maxVertex = v;
    }

    file.close();

    if (maxVertex == 0) {
        throw runtime_error("Ошибка считывания данных из файла");
    }

    // Создаем матрицу и заполняем ее нулями
    BooleanMatrix Matrix(maxVertex, maxVertex, false);

    // Заполняем матрицу смежности
    for (const auto& edge : edges) {
        int from = edge.from - 1;
        int to = edge.to - 1;
        Matrix.setBit(from, to, true);
    }

    return Matrix;
}

// Функция для ввода графа с клавиатуры
BooleanMatrix inputGraph() {
    cout << "Введите рёбра графа (from to). Для завершения введите 0 0:" << endl;

    // Вектор для хранения рёбер
    vector<Edge> edges;
    int maxVertex = 0;

    while (true) {
        int u, v;
        cout << "Ребро: ";
        cin >> u >> v;

        if (u == 0 && v == 0) {
            break;
        }

        if (u < 0 || v < 0) {
            cout << "Ошибка: номера вершин должны быть положительными!" << endl;
            continue;
        }

        edges.push_back({ u, v });
        if (u > maxVertex) maxVertex = u;
        if (v > maxVertex) maxVertex = v;
    }

    if (maxVertex == 0) {
        throw runtime_error("Не введено ни одного ребра");
    }

    // Создаем матрицу смежности
    BooleanMatrix Matrix(maxVertex, maxVertex, false);

    for (const auto& edge : edges) {
        int from = edge.from - 1;
        int to = edge.to - 1;

        if (from >= 0 && from < maxVertex && to >= 0 && to < maxVertex) {
            Matrix.setBit(from, to, true);
        }
    }

    cout << "Граф создан. Количество вершин: " << maxVertex << endl;
    return Matrix;
}

// Вывод результата
void resultOutput(const vector<int>& order) {
    for (size_t i = 0; i < order.size(); ++i) {
        cout << order[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    while (true) {
        cout << "\nТопологическая сортировка графов.\n" << endl;
        cout << "1. Ввести граф с клавиатуры" << endl;
        cout << "2. Загрузить граф из файла" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "Выход из программы." << endl;
            break;
        }

        try {
            BooleanMatrix Matrix;
            if (choice == 1) {
                Matrix = inputGraph();
            }
            else if (choice == 2) {
                vector<string> filenames = { "graph1.txt", "graph2.txt", "graph3.txt", "graph4.txt" };
                int filenameChoice;
                cout << "С какого файла взять графы?: " << endl;
                cout << "1. graph1.txt" << endl;
                cout << "2. graph2.txt" << endl;
                cout << "3. graph3.txt (Граф из презентации)" << endl;
                cout << "4. graph4.txt (Граф с циклом)" << endl;
                cout << "Выберите номер файла: ";
                cin >> filenameChoice;

                if (filenameChoice < 1 || filenameChoice > static_cast<int>(filenames.size())) {
                    throw out_of_range("Неверный выбор! Доступные номера: 1- 4");
                }

                Matrix = buildMatrixFromFile(filenames[filenameChoice - 1]);
                cout << "Граф загружен из файла " << filenames[filenameChoice - 1] << endl;
            }
            else {
                cout << "Неверный выбор!" << endl;
                continue;
            }

            cout << "Матрица смежности:" << endl;
            cout << Matrix;

            cout << "\nСортировка: " << endl;

            auto start = high_resolution_clock::now();

            vector<int> result = topologicalSort(Matrix);

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);

            cout << "Результат сортировки: ";
            resultOutput(result);
            cout << "Время сортировки: " << duration.count() / 1000000.0 << " секунд" << endl;

        }
        catch (const out_of_range& e) {
            cout << "\nОШИБКА ВЫБОРА: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "\nОШИБКА: " << e.what() << endl;
        }

        cout << "\nХотите продолжить? (1 - да, 0 - нет): ";
        int continueChoice;
        cin >> continueChoice;
        if (continueChoice == 0) break;
    }

    return 0;
}