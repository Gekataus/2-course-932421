#include "booleanmatrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>
#include <vector>

using namespace std;
using namespace std::chrono;

class TopologicalSorter {
private:
    BooleanMatrix matrix_;
    vector<int> order_; // Здесь храним правильный порядок вершин

public:
    TopologicalSorter(const BooleanMatrix& adjacencyMatrix) : matrix_(adjacencyMatrix) {
        if (matrix_.getRows() != matrix_.getCols()) {
            throw invalid_argument("Матрица смежности должна быть квадратной");
        }
    }

    // Топологическая сортировка - возвращает вектор с порядком вершин
    vector<int> topologicalSort() {
        order_.clear();
        int n = matrix_.getRows();

        BooleanMatrix workMatrix = matrix_;
        BooleanVector unprocessedVertices(n, true);

        while (unprocessedVertices.getWeight() > 0) {
            BooleanVector columnsWithoutOnes = findEmptyColumns(workMatrix, unprocessedVertices);

            if (columnsWithoutOnes.getWeight() == 0) {
                throw runtime_error("Граф содержит цикл, топологическая сортировка невозможна");
            }

            // Добавляем найденные вершины в правильном порядке
            for (int i = 0; i < n; ++i) {
                if (columnsWithoutOnes[i]) {
                    order_.push_back(i + 1); // Сохраняем номер вершины (начиная с 1)
                    unprocessedVertices.setBit(i, false);
                }
            }

            clearRows(workMatrix, columnsWithoutOnes);
        }

        return order_;
    }

private:
    BooleanVector findEmptyColumns(const BooleanMatrix& matrix, const BooleanVector& unprocessedVertices) {
        int n = matrix.getRows();
        BooleanVector result(n, false);

        for (int col = 0; col < n; ++col) {
            if (!unprocessedVertices[col]) continue; // Если вершина уже обработана - пропускаем

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
};

// Построение матрицы из файла
BooleanMatrix buildAdjacencyMatrixFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл: " + filename);
    }

    // Сначала находим максимальный номер вершины
    int maxVertex = 0;
    int u, v;

    while (file >> u >> v) {
        if (u == 0 && v == 0) {
            break;
        }

        if (u > maxVertex) maxVertex = u;
        if (v > maxVertex) maxVertex = v;
    }

    if (maxVertex == 0) {
        file.close();
        throw runtime_error("Файл не содержит данных или содержит только нули");
    }

    // Создаем матрицу и заполняем ее нулями
    BooleanMatrix adjacencyMatrix(maxVertex, maxVertex, false);

    // Возвращаемся в начало файла
    file.clear();
    file.seekg(0);

    while (file >> u >> v) {
        if (u == 0 && v == 0) {
            break;
        }

        int from = u - 1;
        int to = v - 1;

        if (from >= 0 && from < maxVertex && to >= 0 && to < maxVertex) {
            adjacencyMatrix.setBit(from, to, true);
        }
    }

    file.close();
    return adjacencyMatrix;
}

// Функция для ввода графа с клавиатуры
BooleanMatrix inputGraph() {
    cout << "Введите рёбра графа (from to). Для завершения введите 0 0:" << endl;

    // Сначала собираем информацию о максимальной вершине
    int maxVertex = 0;

    // Временное хранилище для рёбер
    struct Edge { int from, to; };
    vector<Edge> edges;

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
    BooleanMatrix adjacencyMatrix(maxVertex, maxVertex, false);

    for (const auto& edge : edges) {
        int from = edge.from - 1;
        int to = edge.to - 1;

        if (from >= 0 && from < maxVertex && to >= 0 && to < maxVertex) {
            adjacencyMatrix.setBit(from, to, true);
        }
    }

    cout << "Граф создан. Количество вершин: " << maxVertex << endl;
    return adjacencyMatrix;
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
        cout << "2. Загрузить граф из файла (graph1.txt, graph2.txt или graph3.txt)" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "Выход из программы." << endl;
            break;
        }

        try {
            BooleanMatrix adjacencyMatrix;
            if (choice == 1) {
                adjacencyMatrix = inputGraph();
            }
            else if (choice == 2) {
                string filename;
                cout << "Введите имя файла: ";
                cin >> filename;
                adjacencyMatrix = buildAdjacencyMatrixFromFile(filename);
                cout << "Граф загружен из файла." << endl;
            }
            else {
                cout << "Неверный выбор!" << endl;
                continue;
            }

            cout << "Матрица смежности:" << endl;
            cout << adjacencyMatrix;

            cout << "\nСортировка: " << endl;

            auto start = high_resolution_clock::now();

            TopologicalSorter sorter(adjacencyMatrix);
            vector<int> result = sorter.topologicalSort();

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);

            // Выводим результат
            cout << "Результат сортировки: ";
            resultOutput(result);
            cout << "Время сортировки: " << duration.count() / 1000000.0 << " секунд" << endl;

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