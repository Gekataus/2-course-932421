#include "booleanmatrix.h"

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        // Тест конструкторов
        cout << "1. Тест конструкторов BooleanMatrix" << endl;
        BooleanMatrix defaultMatrix;
        BooleanMatrix sizedMatrix(3, 4, true);

        const char* charMatrix[] = {"101", "010", "111", "001"};
        BooleanMatrix charBasedMatrix(charMatrix, 4);
        BooleanMatrix copiedMatrix(charBasedMatrix);

        cout << "Конструктор с параметрами (3x4, true):" << endl;
        cout << sizedMatrix << endl;

        cout << "Конструктор из массива char:" << endl;
        cout << charBasedMatrix << endl;

        cout << "Конструктор копирования:" << endl;
        cout << copiedMatrix << endl;

        // Тест получения размеров и веса
        cout << "2. Тест методов получения размеров и веса матрицы." << endl;
        BooleanMatrix test1;
        cin >> test1;
        cout << "Матрица из char: " << test1.getRows() << "x" << test1.getCols() << endl;
        cout << "Вес матрицы: " << test1.getWeight() << endl << endl;

        // Тест веса строки
        cout << "3. Тест веса строки" << endl;
        try {
            BooleanMatrix test2;
            cin >> test2;
            int x;
            cout << "У какой строки посчитать вес? (от 0 до " << test2.getCols() - 1 << "): "; cin >> x;
            cout << "Вес строки " << x << ": " << test2.getRowWeight(x) << endl << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка получения веса строки: " << e.what() << endl;
        }

        // Обмен содержимого с другой матрицей (swap)
        cout << "4. Тест обмена с другой матрицей (swap)" << endl;
        BooleanMatrix swap1;
        BooleanMatrix swap2;
        cout << "Введите матрицу 1:" << endl;
        cin >> swap1;
        cout << "Введите матрицу 2:" << endl;
        cin >> swap2;
        cout << "Матрица 1:" << endl << swap1;
        cout << "Матрица 2:" << endl << swap2;

        swap1.swap(swap2);

        cout << "После обмена матриц:" << endl;
        cout << "Матрица 1:" << endl << swap1;
        cout << "Матрица 2:" << endl << swap2 << endl << endl;

        // Установка битов
        cout << "5. Тест установки битов" << endl;
        BooleanMatrix testSetBit(2, 2, false);
        cout << "Исходная матрица:" << endl << testSetBit;

        try {
            cout << "Введите в какой строке и столбце поменять бит: ";
            int x, y;
            cin >> x >> y;
            testSetBit.setBit(x, y, true);
            cout << "Матрица после установки бита:" << endl << testSetBit << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка установки бита: " << e.what() << endl << endl;
        }

        // Инверсия битов
        cout << "6. Тест инверсии битов" << endl;
        BooleanMatrix testInvertBit = testSetBit;
        cout << "Исходная матрица:" << endl << testInvertBit;

        try {
            cout << "Введите в какой строке и столбце инвертировать бит: ";
            int x, y;
            cin >> x >> y;
            testInvertBit.invertBit(x, y);
            cout << "Матрица после инверсии битов:" << endl << testInvertBit << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка инверсии бита: " << e.what() << endl << endl;
        }

        // Инверсия k компонент
        cout << "7. Тест инверсии k компонент" << endl;
        BooleanMatrix testInvertK;
        cout << "Введите исходную матрицу:" << endl;
        cin >> testInvertK;
        cout << "Исходная матрица: " << endl << testInvertK << endl;

        try {
            int x, y, k;
            cout << "Введите строку, с какой позиции инвертировать и сколько: ";
            cin >> x >> y >> k;
            testInvertK.invertBits(x, y, k);
            cout << "После инверсии:" << endl << testInvertK;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка инверсии k битов: " << e.what() << endl;
        }

        // Установка k компонент
        cout << "8. Тест установки k компонент" << endl;
        BooleanMatrix testSetK;
        cout << "Введите исходную матрицу:" << endl;
        cin >> testSetK;
        cout << "Исходная матрица: " << endl << testSetK << endl;

        try {
            int x, y, z, k;
            cout << "Введите строку, с какой позиции установить, сколько битов и во сколько (0 или 1): ";
            cin >> x >> y >> z >> k;
            testSetK.setBits(x, y, z, k);
            cout << "После установки 4 битов в строке 1:" << endl << testSetK;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка установки k битов: " << e.what() << endl;
        }

        // Тест оператора []
        cout << "9. Тест оператора []" << endl;
        BooleanMatrix testop;
        cout << "Введите матрицу: " << endl;
        cin >> testop;
        try {
            cout << "Строка 0: " << testop[0] << endl;

            // Тест изменения через оператор []
            BooleanMatrix testIndex = testop;
            testIndex[0].setBit(0, false);
            testIndex[1].setBit(1, true);
            cout << "Матрица после изменения через оператор []:" << endl << testIndex << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка доступа по индексу: " << e.what() << endl;
        }

        // Конъюнкция всех строк
        cout << "10. Тест конъюнкции всех строк" << endl;
        try {
            BooleanVector conjResult = testop.conjunctionAllRows();
            cout << "Матрица:" << endl << testop;
            cout << "Конъюнкция всех строк: " << conjResult << endl << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка конъюнкции: " << e.what() << endl << endl;
        }

        // Дизъюнкция всех строк
        cout << "11. Тест дизъюнкции всех строк" << endl;
        try {
            BooleanVector disjResult = testop.disjunctionAllRows();
            cout << "Матрица:" << endl << testop;
            cout << "Дизъюнкция всех строк: " << disjResult << endl << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка дизъюнкции: " << e.what() << endl << endl;
        }

        // Тест побитовых операций
        cout << "12. Тест побитовых операций" << endl;
        const char* matrixA_data[] = { "101", "010", "110" };
        const char* matrixB_data[] = { "110", "011", "101" };

        BooleanMatrix matrixA(matrixA_data, 3);
        BooleanMatrix matrixB(matrixB_data, 3);

        cout << "Матрица A:" << endl << matrixA;
        cout << "Матрица B:" << endl << matrixB;

        // Побитовое И
        try {
            BooleanMatrix andResult = matrixA & matrixB;
            cout << "A & B:" << endl << andResult;
        }
        catch (const exception& e) {
            cout << "Ошибка операции &: " << e.what() << endl;
        }

        // Побитовое ИЛИ
        try {
            BooleanMatrix orResult = matrixA | matrixB;
            cout << "A | B:" << endl << orResult;
        }
        catch (const exception& e) {
            cout << "Ошибка операции |: " << e.what() << endl;
        }

        // Побитовое XOR
        try {
            BooleanMatrix xorResult = matrixA ^ matrixB;
            cout << "A ^ B:" << endl << xorResult;
        }
        catch (const exception& e) {
            cout << "Ошибка операции ^: " << e.what() << endl;
        }

        // Побитовая инверсия
        try {
            BooleanMatrix notResult = ~matrixA;
            cout << "~A:" << endl << notResult;
        }
        catch (const exception& e) {
            cout << "Ошибка операции ~: " << e.what() << endl;
        }

        // присваивания
        cout << "13. Тест присваиваний" << endl;
        BooleanMatrix tempA = matrixA;
        BooleanMatrix tempB = matrixB;

        try {
            tempA &= matrixB;
            cout << "A &= B:" << endl << tempA;
        }
        catch (const exception& e) {
            cout << "Ошибка операции &=: " << e.what() << endl;
        }

        tempA = matrixA;
        try {
            tempA |= matrixB;
            cout << "A |= B:" << endl << tempA;
        }
        catch (const exception& e) {
            cout << "Ошибка операции |=: " << e.what() << endl;
        }

        tempA = matrixA;
        try {
            tempA ^= matrixB;
            cout << "A ^= B:" << endl << tempA;
        }
        catch (const exception& e) {
            cout << "Ошибка операции ^=: " << e.what() << endl;
        }

        // Тест оператора присваивания
        cout << "15. Тест оператора присваивания" << endl;
        BooleanMatrix assignedMatrix;
        assignedMatrix = matrixA;
        cout << "После присваивания A:" << endl << assignedMatrix;
        cout << "A == assignedMatrix: " << (matrixA == assignedMatrix) << " (ожидается: 1)" << endl << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка в программе: " << e.what() << endl;
        return 1;
    }

    return 0;
}