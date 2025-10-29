#include <iostream>
#include "DynamicArray.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    // Для int
    cout << "Тест int" << endl << endl;

    // Тест конструкторов
    cout << "\n1. Тест конструкторов:" << endl;
    DynamicArray<int> arr1;
    cout << "Конструктор по умолчанию - длина: " << arr1.getArrayLength() << "  Ожидаем: 0" << endl;

    int testData[] = { 1, 2, 3, 4, 5 };
    DynamicArray<int> arr2(testData, 5);
    cout << "Конструктор из обычного массива - длина: " << arr2.getArrayLength() << "  Ожидаем: 5" << endl;

    DynamicArray<int> arr3(arr2);
    cout << "Конструктор копирования - длина: " << arr3.getArrayLength() << "  Ожидаем: 5" << endl;

    // Тест вставки и удаления
    cout << "\n2. Тест вставки и удаления:" << endl;
    int initialData[] = { 10, 20, 30, 40, 50 };
    DynamicArray<int> arr5(initialData, 5);
    int x, y;
    cout << "Исходный массив: " << arr5 << endl;
    cout << "Введите элемент для вставки и индекс, куда вы собираетесь его поставить: ";
    cin >> x >> y;
    if (!arr5.insertAt(y, x)) cout << "Некорректный индекс" << endl;
    else cout << "Массив после вставки: " << arr5 << endl;

    arr5.removeAt(1);
    cout << "После удаления второго элемента: " << arr5 << endl;

    cout << "Введите значение для удаления первого вхождения: ";
    cin >> x;
    if (!arr5.removeFirstValue(x)) cout << "Элемент не найден" << endl;
    else cout << "После removeFirstValue(" << x << "): " << arr5 << endl;

    // Тест поиска
    cout << "\n3. Тест поиска:" << endl;
    int searchData[] = { 5, 3, 8, 3, 1 };
    DynamicArray<int> arr6(searchData, 5);

    cout << "Массив: " << arr6 << endl;
    cout << "findElement(3): " << arr6.findElement(3) << " (ожидалось: 1)" << endl;
    cout << "findElement(10): " << arr6.findElement(10) << " (ожидалось: -1)" << endl;
    cout << "findMaxEl(): " << arr6.findMaxEl() << " (ожидалось: 8)" << endl;
    cout << "findMinEl(): " << arr6.findMinEl() << " (ожидалось: 1)" << endl;

    // Тест сортировки
    cout << "\n4. Тест сортировки:" << endl;
    DynamicArray<int> arrsort;
    cout << "Введите длину массива для сортировки: ";
    int len;
    cin >> len;
    arrsort.setArrayLength(len);
    cout << "Введите " << len << " элементов: ";
    for (int i = 0; i < len; i++) {
        int val;
        cin >> val;
        arrsort.setAt(i, val);
    }
    cout << "До сортировки: " << arrsort << endl;
    arrsort.sort();
    cout << "После сортировки: " << arrsort << endl;

    // Тест операторов
    cout << "\n5. Тест перегрузок:" << endl;
    int data7[] = { 10, 20 };
    DynamicArray<int> arr7(data7, 2);

    int data8[] = { 30, 40 };
    DynamicArray<int> arr8(data8, 2);

    DynamicArray<int> arrsumm = arr7 + arr8;
    cout << "arr7: " << arr7 << endl;
    cout << "arr8: " << arr8 << endl;
    cout << "arr7 + arr8: " << arrsumm << endl;

    arr7 += arr8;
    cout << "После arr7 += arr8: " << arr7 << endl;

    cout << "arr7 == arr8: " << (arr7 == arr8) << endl;
    cout << "arr7 != arr8: " << (arr7 != arr8) << endl;

    // Тест оператора []
    cout << "\n6. Тест оператора []:" << endl;
    cout << "arr7[0]: " << arr7[0] << " (ожидалось: 10)" << endl;
    cout << "arr7[1]: " << arr7[1] << " (ожидалось: 20)" << endl;
    arr7[0] = 100;
    cout << "После arr7[0] = 100: " << arr7 << endl;

    // Тест присваивания
    cout << "\n7. Присваивание:" << endl;
    int data9[] = { 100, 200, 300 };
    DynamicArray<int> arr9(data9, 3);
    cout << "Массив arr9: " << arr9 << endl;

    DynamicArray<int> arr10;
    arr10 = arr9;
    cout << "После arr10 = arr9, arr10: " << arr10 << endl;

    // Тест обмена
    cout << "\n8. Тест обмена:" << endl;
    int data11[] = { 1, 2 };
    DynamicArray<int> arr11(data11, 2);

    int data12[] = { 9, 8 };
    DynamicArray<int> arr12(data12, 2);

    cout << "До обмена - arr11: " << arr11 << ", arr12: " << arr12 << endl;
    arr11.ArraysSwap(arr12);
    cout << "После обмена - arr11: " << arr11 << ", arr12: " << arr12 << endl;

    // Тест удаления всех значений
    cout << "\n9. Тест удаления всех значений:" << endl;
    int data13[] = { 1, 2, 3, 2, 4, 2 };
    DynamicArray<int> arr13(data13, 6);

    cout << "До removeAllValue(2): " << arr13 << endl;
    arr13.removeAllValue(2);
    cout << "После removeAllValue(2): " << arr13 << endl;

    // Тест геттеров и сеттеров
    cout << "\n10. Тест геттеров и сеттеров:" << endl;
    DynamicArray<int> arr14;
    arr14.setArrayLength(3);
    arr14.setAt(0, 7);
    arr14.setAt(1, 8);
    arr14.setAt(2, 9);
    cout << "Массив после set методов: " << arr14 << endl;
    cout << "getAt(1): " << arr14.getAt(1) << " (ожидалось: 8)" << endl;

    const int* rawData = arr14.getArrayData();
    cout << "getArrayData(): [" << rawData[0] << ", " << rawData[1] << ", " << rawData[2] << "]" << endl;

    // Для float
    cout << "\n\nТип float" << endl << endl;

    // Тест конструкторов
    cout << "\n1. Тест конструкторов:" << endl;
    DynamicArray<float> arr1_float;
    cout << "Конструктор по умолчанию - длина: " << arr1_float.getArrayLength() << "  Ожидаем: 0" << endl;

    float testData_float[] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    DynamicArray<float> arr2_float(testData_float, 5);
    cout << "Конструктор из обычного массива - длина: " << arr2_float.getArrayLength() << "  Ожидаем: 5" << endl;

    DynamicArray<float> arr3_float(arr2_float);
    cout << "Конструктор копирования - длина: " << arr3_float.getArrayLength() << "  Ожидаем: 5" << endl;

    // Тест вставки и удаления
    cout << "\n2. Тест вставки и удаления:" << endl;
    float initialData_float[] = { 10.5f, 20.5f, 30.5f, 40.5f, 50.5f };
    DynamicArray<float> arr5_float(initialData_float, 5);
    float x_float;
    int y_float;
    cout << "Исходный массив: " << arr5_float << endl;
    cout << "Введите элемент для вставки и индекс, куда вы собираетесь его поставить: ";
    cin >> x_float >> y_float;
    if (!arr5_float.insertAt(y_float, x_float)) cout << "Некорректный индекс" << endl;
    else cout << "Массив после вставки: " << arr5_float << endl;

    arr5_float.removeAt(1);
    cout << "После удаления второго элемента: " << arr5_float << endl;

    cout << "Введите значение для удаления первого вхождения: ";
    cin >> x_float;
    if (!arr5_float.removeFirstValue(x_float)) cout << "Элемент не найден" << endl;
    else cout << "После removeFirstValue(" << x_float << "): " << arr5_float << endl;

    // Тест поиска
    cout << "\n3. Тест поиска:" << endl;
    float searchData_float[] = { 5.5f, 3.3f, 8.8f, 3.3f, 1.1f };
    DynamicArray<float> arr6_float(searchData_float, 5);

    cout << "Массив: " << arr6_float << endl;
    cout << "findElement(3.3): " << arr6_float.findElement(3.3f) << " (ожидалось: 1)" << endl;
    cout << "findElement(10.0): " << arr6_float.findElement(10.0f) << " (ожидалось: -1)" << endl;
    cout << "findMaxEl(): " << arr6_float.findMaxEl() << " (ожидалось: 8.8)" << endl;
    cout << "findMinEl(): " << arr6_float.findMinEl() << " (ожидалось: 1.1)" << endl;

    // Тест сортировки
    cout << "\n4. Тест сортировки:" << endl;
    DynamicArray<float> arrsort_float;
    cout << "Введите длину массива для сортировки: ";
    int len_float;
    cin >> len_float;
    arrsort_float.setArrayLength(len_float);
    cout << "Введите " << len_float << " элементов: ";
    for (int i = 0; i < len_float; i++) {
        float val;
        cin >> val;
        arrsort_float.setAt(i, val);
    }
    cout << "До сортировки: " << arrsort_float << endl;
    arrsort_float.sort();
    cout << "После сортировки: " << arrsort_float << endl;

    // Тест операторов
    cout << "\n5. Тест перегрузок:" << endl;
    float data7_float[] = { 1.5f, 2.5f };
    DynamicArray<float> arr7_float(data7_float, 2);

    float data8_float[] = { 3.5f, 4.5f };
    DynamicArray<float> arr8_float(data8_float, 2);

    DynamicArray<float> arrsumm_float = arr7_float + arr8_float;
    cout << "arr7: " << arr7_float << endl;
    cout << "arr8: " << arr8_float << endl;
    cout << "arr7 + arr8: " << arrsumm_float << endl;

    arr7_float += arr8_float;
    cout << "После arr7 += arr8: " << arr7_float << endl;

    cout << "arr7 == arr8: " << (arr7_float == arr8_float) << endl;
    cout << "arr7 != arr8: " << (arr7_float != arr8_float) << endl;

    // Для Char
    cout << "\n\nТест char" << endl << endl;

    // Тест конструкторов
    cout << "\n1. Тест конструкторов:" << endl;
    DynamicArray<char> arr1_char;
    cout << "Конструктор по умолчанию - длина: " << arr1_char.getArrayLength() << "  Ожидаем: 0" << endl;

    char testData_char[] = { 'A', 'B', 'C', 'D', 'E' };
    DynamicArray<char> arr2_char(testData_char, 5);
    cout << "Конструктор из обычного массива - длина: " << arr2_char.getArrayLength() << "  Ожидаем: 5" << endl;

    DynamicArray<char> arr3_char(arr2_char);
    cout << "Конструктор копирования - длина: " << arr3_char.getArrayLength() << "  Ожидаем: 5" << endl;

    // Тест вставки и удаления
    cout << "\n2. Тест вставки и удаления:" << endl;
    char initialData_char[] = { 'H', 'e', 'l', 'l', 'o' };
    DynamicArray<char> arr5_char(initialData_char, 5);
    char x_char;
    int y_char;
    cout << "Исходный массив: " << arr5_char << endl;
    cout << "Введите символ для вставки и индекс, куда вы собираетесь его поставить: ";
    cin >> x_char >> y_char;
    if (!arr5_char.insertAt(y_char, x_char)) cout << "Некорректный индекс" << endl;
    else cout << "Массив после вставки: " << arr5_char << endl;

    arr5_char.removeAt(1);
    cout << "После удаления второго элемента: " << arr5_char << endl;

    cout << "Введите символ для удаления первого вхождения: ";
    cin >> x_char;
    if (!arr5_char.removeFirstValue(x_char)) cout << "Элемент не найден" << endl;
    else cout << "После removeFirstValue(" << x_char << "): " << arr5_char << endl;

    // Тест поиска
    cout << "\n3. Тест поиска:" << endl;
    char searchData_char[] = { 'A', 'B', 'C', 'D', 'E' };
    DynamicArray<char> arr6_char(searchData_char, 5);

    cout << "Массив: " << arr6_char << endl;
    cout << "findElement('A'): " << arr6_char.findElement('A') << " (ожидалось: 0)" << endl;
    cout << "findElement('Q'): " << arr6_char.findElement('Q') << " (ожидалось: -1)" << endl;
    cout << "findMaxEl(): " << arr6_char.findMaxEl() << " (ожидалось: E)" << endl;
    cout << "findMinEl(): " << arr6_char.findMinEl() << " (ожидалось: A)" << endl;

    // Тест сортировки
    cout << "\n4. Тест сортировки:" << endl;
    DynamicArray<char> arrsort_char;
    cout << "Введите длину массива для сортировки: ";
    int len_char;
    cin >> len_char;
    arrsort_char.setArrayLength(len_char);
    cout << "Введите " << len_char << " символов: ";
    for (int i = 0; i < len_char; i++) {
        char val;
        cin >> val;
        arrsort_char.setAt(i, val);
    }
    cout << "До сортировки: " << arrsort_char << endl;
    arrsort_char.sort();
    cout << "После сортировки: " << arrsort_char << endl;

    // Тест операторов
    cout << "\n5. Тест перегрузок:" << endl;
    char data7_char[] = { '+', '+' };
    DynamicArray<char> arr7_char(data7_char, 2);

    char data8_char[] = { '-', '-' };
    DynamicArray<char> arr8_char(data8_char, 2);

    DynamicArray<char> arrsumm_char = arr7_char + arr8_char;
    cout << "arr7: " << arr7_char << endl;
    cout << "arr8: " << arr8_char << endl;
    cout << "arr7 + arr8: " << arrsumm_char << endl;

    arr7_char += arr8_char;
    cout << "После arr7 += arr8: " << arr7_char << endl;

    cout << "arr7 == arr8: " << (arr7_char == arr8_char) << endl;
    cout << "arr7 != arr8: " << (arr7_char != arr8_char) << endl;

    // Тест удаления всех значений
    cout << "\n6. Тест удаления всех значений:" << endl;
    char data13_char[] = { 'a', 'b', 'a', 'c', 'a', 'd' };
    DynamicArray<char> arr13_char(data13_char, 6);

    cout << "До removeAllValue('a'): " << arr13_char << endl;
    arr13_char.removeAllValue('a');
    cout << "После removeAllValue('a'): " << arr13_char << endl;

    return 0;
}