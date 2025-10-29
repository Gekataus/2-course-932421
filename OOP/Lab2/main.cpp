#include <iostream>
#include "DynamicArray.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    // Тест конструкторов
    cout << "\n1. Тест конструкторов:" << endl;
    DynamicArray arr1;
    cout << "Конструктор по умолчанию - длина: " << arr1.getArrayLength() << "  Ожидаем: 0" << endl;

    int testData[] = { 1, 2, 3, 4, 5 };
    DynamicArray arr2(testData, 5);
    cout << "Конструктор из обычного массива - длина: " << arr2.getArrayLength() << "  Ожидаем: 5" << endl;

    DynamicArray arr3(arr2);
    cout << "Конструктор копирования - длина: " << arr3.getArrayLength() << "  Ожидаем: 5" << endl;

    // Тест вставки и удаления
    cout << "\n3. Тест вставки и удаления:" << endl;
    int initialData[] = { 10, 20, 30, 40, 50 };
    DynamicArray arr5(initialData, 5);
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
    cout << "\n4. Тест поиска:" << endl;
    int searchData[] = { 5, 3, 8, 3, 1 };
    DynamicArray arr6(searchData, 5);

    cout << "Массив: " << arr6 << endl;
    cout << "findElement(3): " << arr6.findElement(3) << " (ожидалось: 1)" << endl;
    cout << "findElement(10): " << arr6.findElement(10) << " (ожидалось: -1)" << endl;
    cout << "findMaxEl(): " << arr6.findMaxEl() << " (ожидалось: 8)" << endl;
    cout << "findMinEl(): " << arr6.findMinEl() << " (ожидалось: 1)" << endl;

    // Тест сортировки
    cout << "\n5. Тест сортировки:" << endl;
    DynamicArray arrsort;
    cout << "Введите массив для сортировки:" << endl;
    cin >> arrsort;
    cout << "До сортировки: " << arrsort << endl;
    arrsort.sort();
    cout << "После сортировки: " << arrsort << endl;

    // Тест операторов
    cout << "\n6. Тест перегрузок:" << endl;
    int data7[] = { 10, 20 };
    DynamicArray arr7(data7, 2);

    int data8[] = { 30, 40 };
    DynamicArray arr8(data8, 2);

    DynamicArray arrsumm = arr7 + arr8;
    cout << "arr7: " << arr7 << endl;
    cout << "arr8: " << arr8 << endl;
    cout << "arr7 + arr8: " << arrsumm << endl;

    arr7 += arr8;
    cout << "После arr7 += arr8: " << arr7 << endl;

    cout << "arr7 == arr8: " << (arr7 == arr8) << endl;
    cout << "arr7 != arr8: " << (arr7 != arr8) << endl;

    // Тест оператора []
    cout << "\nТест оператора []:" << endl;
    cout << "arr7[0]: " << arr7[0] << " (ожидалось: 40)" << endl;
    cout << "arr7[1]: " << arr7[1] << " (ожидалось: 60)" << endl;
    arr7[0] = 100;
    cout << "После arr7[0] = 100: " << arr7 << endl;

    // Тест присваивания
    cout << "\n7. Присваивание:" << endl;
    int data9[] = { 100, 200, 300 };
    DynamicArray arr9(data9, 3);
    cout << "Массив arr9: " << arr9 << endl;

    DynamicArray arr10;
    arr10 = arr9;
    cout << "После arr10 = arr9, arr10: " << arr10 << endl;

    // Тест обмена
    cout << "\n8. Тест обмена:" << endl;
    int data11[] = { 1, 2 };
    DynamicArray arr11(data11, 2);

    int data12[] = { 9, 8 };
    DynamicArray arr12(data12, 2);

    cout << "До обмена - arr11: " << arr11 << ", arr12: " << arr12 << endl;
    arr11.ArraysSwap(arr12);
    cout << "После обмена - arr11: " << arr11 << ", arr12: " << arr12 << endl;

    // Тест удаления всех значений
    cout << "\n9. Тест удаления всех значений:" << endl;
    int data13[] = { 1, 2, 3, 2, 4, 2 };
    DynamicArray arr13(data13, 6);

    cout << "До removeAllValue(2): " << arr13 << endl;
    arr13.removeAllValue(2);
    cout << "После removeAllValue(2): " << arr13 << endl;

    // Тест геттеров и сеттеров
    cout << "\n10. Тест геттеров и сеттеров:" << endl;
    DynamicArray arr14;
    arr14.setArrayLength(3);
    arr14.setAt(0, 7);
    arr14.setAt(1, 8);
    arr14.setAt(2, 9);
    cout << "Массив после set методов: " << arr14 << endl;
    cout << "getAt(1): " << arr14.getAt(1) << " (ожидалось: 8)" << endl;

    const int* rawData = arr14.getArrayData();
    cout << "getArrayData(): [" << rawData[0] << ", " << rawData[1] << ", " << rawData[2] << "]" << endl;

    return 0;
}