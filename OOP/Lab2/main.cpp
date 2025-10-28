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

    DynamicArray arr2(5);
    cout << "Конструктор из обычного массива - длина: " << arr2.getArrayLength() << "  Ожидаем: 5" << endl;

    DynamicArray arr3(arr2);
    cout << "Конструктор копирования - длина: " << arr3.getArrayLength() << "  Ожидаем: 5" << endl;

    // Тест вставки и удаления
    cout << "\n3. Тест вставки и удаления:" << endl;
    DynamicArray arr5(5);
    int x, y;
    cin >> arr5;
    cout << "Введите элемент для вставки и индекс, куда вы собираетесь его поставить: ";
    cin >> x >> y;
    if (!arr5.insertAt(y, x)) cout << "Некорректный индекс" << endl;
    else cout << "Массив после вставки: " << arr5 << endl;

    arr5.removeAt(1);
    cout << "После удаления второго элемента: " << arr5 << endl;

    cout << "Введите значение для удаления первого вхождения: ";
    cin >> x;
    arr5.removeFirstValue(x);
    cout << "После removeFirstValue(" << x << "): " << arr5 << endl;

    // Тест поиска
    cout << "\n4. Тест поиска:" << endl;
    DynamicArray arr6(5);
    arr6.setAt(0, 5);
    arr6.setAt(1, 3);
    arr6.setAt(2, 8);
    arr6.setAt(3, 3);
    arr6.setAt(4, 1);

    cout << "Массив: " << arr6 << endl;
    cout << "findElement(3): " << arr6.findElement(3) << " (ожидалось: 1)" << endl;
    cout << "findElement(10): " << arr6.findElement(10) << " (ожидалось: -1)" << endl;
    cout << "findMaxEl(): " << arr6.findMaxEl() << " (ожидалось: 8)" << endl;
    cout << "findMinEl(): " << arr6.findMinEl() << " (ожидалось: 1)" << endl;

    // Тест сортировки
    cout << "\n5. Tест сортировки:" << endl;
    DynamicArray arrsort;
    cout << "Введите массив для сортировки:" << endl;
    cin >> arrsort;
    cout << "До сортировки: " << arrsort << endl;
    arrsort.sort();
    cout << "После сортировки: " << arrsort << endl;

    // Тест операторов
    cout << "\n6. Тест перегрузок:" << endl;
    DynamicArray arr7(2);
    arr7.setAt(0, 10);
    arr7.setAt(1, 20);

    DynamicArray arr8(2);
    arr8.setAt(0, 30);
    arr8.setAt(1, 40);

    DynamicArray arrsumm = arr7 + arr8;
    cout << "arr7: " << arr7 << endl;
    cout << "arr8: " << arr8 << endl;
    cout << "arr7 + arr8: " << arrsumm << endl;

    arr7 += arr8;
    cout << "После arr7 += arr8: " << arr7 << endl;

    cout << "arr7 == arr8: " << (arr7 == arr8) << endl;
    cout << "arr7 != arr8: " << (arr7 != arr8) << endl;

    // Тест присваивания
    cout << "\n7. Присваивание:" << endl;
    DynamicArray arr9(3);
    arr9.setAt(0, 100);
    arr9.setAt(1, 200);
    arr9.setAt(2, 300);
    cout << "Массив arr9: " << arr9 << endl;

    DynamicArray arr10;
    arr10 = arr9;
    cout << "После arr10 = arr9, arr10: " << arr10 << endl;

    // Тест обмена
    cout << "\n8. Тест обмена:" << endl;
    DynamicArray arr11(2);
    arr11.setAt(0, 1);
    arr11.setAt(1, 2);

    DynamicArray arr12(2);
    arr12.setAt(0, 9);
    arr12.setAt(1, 8);

    cout << "До обмена - arr11: " << arr11 << ", arr12: " << arr12 << endl;
    arr11.ArraysSwap(arr12);
    cout << "После обмена - arr11: " << arr11 << ", arr12: " << arr12 << endl;

    // Тест удаления всех значений
    cout << "\n9. Тест удаления всех значений:" << endl;
    DynamicArray arr13(6);
    arr13.setAt(0, 1);
    arr13.setAt(1, 2);
    arr13.setAt(2, 3);
    arr13.setAt(3, 2);
    arr13.setAt(4, 4);
    arr13.setAt(5, 2);

    cout << "До removeAllValue(2): " << arr13 << endl;
    arr13.removeAllValue(2);
    cout << "После removeAllValue(2): " << arr13 << endl;

    return 0;
}