#include "booleanmatrix.h"

int main()
{

    setlocale(LC_ALL, "Russian");

    try {
        // Тест конструкторов
        cout << "1. Тест конструкторов BooleanMatrix" << endl;
        BooleanMatrix defaultMatrix;
        BooleanMatrix sizedMatrix(3, 4, true);

        const char* charMatrix[] = {
            "101",
            "010",
            "111",
            "001"
        };
        BooleanMatrix charBasedMatrix(charMatrix, 4);
        BooleanMatrix copiedMatrix(charBasedMatrix);

        cout << "Конструктор с параметрами (3x4, true):" << endl;
        cout << sizedMatrix << endl;

        cout << "Конструктор из массива char:" << endl;
        cout << charBasedMatrix << endl;

        cout << "Конструктор копирования:" << endl;
        cout << copiedMatrix << endl;

        // Тест получения размеров и веса
        cout << "2. Тест методов получения размеров и веса матрицы" << endl;
        cout << "Матрица из char: " << charBasedMatrix.getRows() << "x" << charBasedMatrix.getCols() << endl;
        cout << "Вес матрицы: " << charBasedMatrix.getWeight() << endl << endl;

        // Обмен содержимого с другой матрицей (swap)
        cout << "3. Тест обмена с другой матрицей (swap)" << endl;
        BooleanMatrix swap1(2, 3, true);
        BooleanMatrix swap2(3, 2, false);

        cout << "Матрица 1 (2x3):" << endl << swap1;
        cout << "Матрица 2 (3x2):" << endl << swap2;

        swap1.swap(swap2);

        cout << "После обмена матриц:" << endl;
        cout << "Матрица 1:" << endl << swap1;
        cout << "Матрица 2:" << endl << swap2 << endl;

        // Установка битов
        cout << "4. Тест установки битов" << endl;
        BooleanMatrix testSetBit;
        cout << "Введите матрицу:" << endl;
        try {
            cin >> testSetBit;
        }
        catch (const runtime_error& e) {
            cout << "Ошибка ввода: " << e.what() << endl;
            cout << "Введите матрицу заново:" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> testSetBit;
        }

        int row, col, value;
        cout << "Введите строку, столбец и значение (0/1) для установки: ";
        cin >> row >> col >> value;

        try {
            testSetBit.setBit(row, col, value);
            cout << "Матрица после установки бита:" << endl << testSetBit << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка установки бита: " << e.what() << endl << endl;
        }

        // Конъюнкция всех строк
        cout << "5. Тест конъюнкции всех строк" << endl;
        BooleanMatrix testConj;
        cout << "Введите матрицу для конъюнкции:" << endl;
        try {
            cin >> testConj;
        }
        catch (const runtime_error& e) {
            cout << "Ошибка ввода: " << e.what() << endl;
            cout << "Введите матрицу заново:" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> testConj;
        }

        try {
            BooleanVector conjResult = testConj.conjunctionAllRows();
            cout << "Матрица:" << endl << testConj;
            cout << "Конъюнкция всех строк: " << conjResult << endl << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка конъюнкции: " << e.what() << endl << endl;
        }

        // Дизъюнкция всех строк
        cout << "6. Тест дизъюнкции всех строк" << endl;
        BooleanMatrix testDisj;
        cout << "Введите матрицу для дизъюнкции:" << endl;
        try {
            cin >> testDisj;
        }
        catch (const runtime_error& e) {
            cout << "Ошибка ввода: " << e.what() << endl;
            cout << "Введите матрицу заново:" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> testDisj;
        }

        try {
            BooleanVector disjResult = testDisj.disjunctionAllRows();
            cout << "Матрица:" << endl << testDisj;
            cout << "Дизъюнкция всех строк: " << disjResult << endl << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка дизъюнкции: " << e.what() << endl << endl;
        }

        // Тест операций с несколькими матрицами
        cout << "7. Тест операций с несколькими матрицами" << endl;
        BooleanMatrix matrixA, matrixB;

        cout << "Введите матрицу A:" << endl;
        try {
            cin >> matrixA;
        }
        catch (const runtime_error& e) {
            cout << "Ошибка ввода матрицы A: " << e.what() << endl;
            cout << "Введите матрицу A заново:" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> matrixA;
        }

        cout << "Введите матрицу B:" << endl;
        try {
            cin >> matrixB;
        }
        catch (const runtime_error& e) {
            cout << "Ошибка ввода матрицы B: " << e.what() << endl;
            cout << "Введите матрицу B заново:" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> matrixB;
        }

        // Сравнение размеров и весов
        cout << "Матрица A (" << matrixA.getRows() << "x" << matrixA.getCols()
            << "), вес: " << matrixA.getWeight() << endl;
        cout << "Матрица B (" << matrixB.getRows() << "x" << matrixB.getCols()
            << "), вес: " << matrixB.getWeight() << endl;

        // Конъюнкция и дизъюнкция для обеих матриц
        try {
            BooleanVector conjA = matrixA.conjunctionAllRows();
            BooleanVector disjA = matrixA.disjunctionAllRows();
            cout << "Конъюнкция A: " << conjA << endl;
            cout << "Дизъюнкция A: " << disjA << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка операций с матрицей A: " << e.what() << endl;
        }

        try {
            BooleanVector conjB = matrixB.conjunctionAllRows();
            BooleanVector disjB = matrixB.disjunctionAllRows();
            cout << "Конъюнкция B: " << conjB << endl;
            cout << "Дизъюнкция B: " << disjB << endl << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка операций с матрицей B: " << e.what() << endl << endl;
        }

        return 0;
    }

    catch (const std::exception& e) {
        cout << "Ошибка в программе: " << e.what() << endl;
        return 1;
    }
}