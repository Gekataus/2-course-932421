#include "booleanmatrix.h"

int main() {
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

        // Тест веса строки
        cout << "3. Тест веса строки" << endl;
        try {
            cout << "Вес строки 0: " << charBasedMatrix.getRowWeight(0) << " (ожидается: 2)" << endl;
            cout << "Вес строки 1: " << charBasedMatrix.getRowWeight(1) << " (ожидается: 1)" << endl;
            cout << "Вес строки 2: " << charBasedMatrix.getRowWeight(2) << " (ожидается: 3)" << endl;
            cout << "Вес строки 3: " << charBasedMatrix.getRowWeight(3) << " (ожидается: 1)" << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка получения веса строки: " << e.what() << endl;
        }

        // Обмен содержимого с другой матрицей (swap)
        cout << "4. Тест обмена с другой матрицей (swap)" << endl;
        BooleanMatrix swap1(2, 3, true);
        BooleanMatrix swap2(3, 2, false);

        cout << "Матрица 1 (2x3):" << endl << swap1;
        cout << "Матрица 2 (3x2):" << endl << swap2;

        swap1.swap(swap2);

        cout << "После обмена матриц:" << endl;
        cout << "Матрица 1:" << endl << swap1;
        cout << "Матрица 2:" << endl << swap2 << endl;

        // Установка битов
        cout << "5. Тест установки битов" << endl;
        BooleanMatrix testSetBit(2, 2, false);
        cout << "Исходная матрица:" << endl << testSetBit;

        try {
            testSetBit.setBit(0, 0, true);
            testSetBit.setBit(1, 1, true);
            cout << "Матрица после установки битов:" << endl << testSetBit << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка установки бита: " << e.what() << endl << endl;
        }

        // Инверсия битов
        cout << "6. Тест инверсии битов" << endl;
        BooleanMatrix testInvertBit = testSetBit;
        cout << "Исходная матрица:" << endl << testInvertBit;

        try {
            testInvertBit.invertBit(0, 1);
            testInvertBit.invertBit(1, 0);
            cout << "Матрица после инверсии битов [0,1] и [1,0]:" << endl << testInvertBit << endl;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка инверсии бита: " << e.what() << endl << endl;
        }

        // Инверсия k компонент
        cout << "7. Тест инверсии k компонент" << endl;
        BooleanMatrix testInvertK(2, 5, true);
        cout << "Исходная матрица:" << endl << testInvertK;

        try {
            testInvertK.invertBits(0, 1, 3); // Инвертировать 3 бита в строке 0, начиная с позиции 1
            cout << "После инверсии 3 битов в строке 0:" << endl << testInvertK;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка инверсии k битов: " << e.what() << endl;
        }

        // Установка k компонент
        cout << "8. Тест установки k компонент" << endl;
        BooleanMatrix testSetK(2, 5, false);
        cout << "Исходная матрица:" << endl << testSetK;

        try {
            testSetK.setBits(1, 0, 4, true); // Установить 4 бита в строке 1 в true
            cout << "После установки 4 битов в строке 1:" << endl << testSetK;
        }
        catch (const out_of_range& e) {
            cout << "Ошибка установки k битов: " << e.what() << endl;
        }

        // Тест оператора []
        cout << "9. Тест оператора []" << endl;
        try {
            cout << "Строка 0: " << charBasedMatrix[0] << endl;
            cout << "Строка 1: " << charBasedMatrix[1] << endl;

            // Тест изменения через оператор []
            BooleanMatrix testIndex = charBasedMatrix;
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
            BooleanVector conjResult = charBasedMatrix.conjunctionAllRows();
            cout << "Матрица:" << endl << charBasedMatrix;
            cout << "Конъюнкция всех строк: " << conjResult << endl << endl;
        }
        catch (const exception& e) {
            cout << "Ошибка конъюнкции: " << e.what() << endl << endl;
        }

        // Дизъюнкция всех строк
        cout << "11. Тест дизъюнкции всех строк" << endl;
        try {
            BooleanVector disjResult = charBasedMatrix.disjunctionAllRows();
            cout << "Матрица:" << endl << charBasedMatrix;
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

        // Тест сравнения
        cout << "14. Тест сравнения матриц" << endl;
        BooleanMatrix matrixA_copy = matrixA;
        BooleanMatrix matrixC(matrixB_data, 3);

        cout << "A == A_copy: " << (matrixA == matrixA_copy) << " (ожидается: 1)" << endl;
        cout << "A == B: " << (matrixA == matrixB) << " (ожидается: 0)" << endl;
        cout << "A != B: " << (matrixA != matrixB) << " (ожидается: 1)" << endl;
        cout << "B == C: " << (matrixB == matrixC) << " (ожидается: 1)" << endl << endl;

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