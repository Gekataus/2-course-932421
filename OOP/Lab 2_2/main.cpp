#include <iostream>
#include "DynamicArray.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    // ��� int
    cout << "���� int" << endl << endl;

    // ���� �������������
    cout << "\n1. ���� �������������:" << endl;
    DynamicArray<int> arr1;
    cout << "����������� �� ��������� - �����: " << arr1.getArrayLength() << "  �������: 0" << endl;

    int testData[] = { 1, 2, 3, 4, 5 };
    DynamicArray<int> arr2(testData, 5);
    cout << "����������� �� �������� ������� - �����: " << arr2.getArrayLength() << "  �������: 5" << endl;

    DynamicArray<int> arr3(arr2);
    cout << "����������� ����������� - �����: " << arr3.getArrayLength() << "  �������: 5" << endl;

    // ���� ������� � ��������
    cout << "\n2. ���� ������� � ��������:" << endl;
    int initialData[] = { 10, 20, 30, 40, 50 };
    DynamicArray<int> arr5(initialData, 5);
    int x, y;
    cout << "�������� ������: " << arr5 << endl;
    cout << "������� ������� ��� ������� � ������, ���� �� ����������� ��� ���������: ";
    cin >> x >> y;
    if (!arr5.insertAt(y, x)) cout << "������������ ������" << endl;
    else cout << "������ ����� �������: " << arr5 << endl;

    arr5.removeAt(1);
    cout << "����� �������� ������� ��������: " << arr5 << endl;

    cout << "������� �������� ��� �������� ������� ���������: ";
    cin >> x;
    if (!arr5.removeFirstValue(x)) cout << "������� �� ������" << endl;
    else cout << "����� removeFirstValue(" << x << "): " << arr5 << endl;

    // ���� ������
    cout << "\n3. ���� ������:" << endl;
    int searchData[] = { 5, 3, 8, 3, 1 };
    DynamicArray<int> arr6(searchData, 5);

    cout << "������: " << arr6 << endl;
    cout << "findElement(3): " << arr6.findElement(3) << " (���������: 1)" << endl;
    cout << "findElement(10): " << arr6.findElement(10) << " (���������: -1)" << endl;
    cout << "findMaxEl(): " << arr6.findMaxEl() << " (���������: 8)" << endl;
    cout << "findMinEl(): " << arr6.findMinEl() << " (���������: 1)" << endl;

    // ���� ����������
    cout << "\n4. ���� ����������:" << endl;
    DynamicArray<int> arrsort;
    cout << "������� ����� ������� ��� ����������: ";
    int len;
    cin >> len;
    arrsort.setArrayLength(len);
    cout << "������� " << len << " ���������: ";
    for (int i = 0; i < len; i++) {
        int val;
        cin >> val;
        arrsort.setAt(i, val);
    }
    cout << "�� ����������: " << arrsort << endl;
    arrsort.sort();
    cout << "����� ����������: " << arrsort << endl;

    // ���� ����������
    cout << "\n5. ���� ����������:" << endl;
    int data7[] = { 10, 20 };
    DynamicArray<int> arr7(data7, 2);

    int data8[] = { 30, 40 };
    DynamicArray<int> arr8(data8, 2);

    DynamicArray<int> arrsumm = arr7 + arr8;
    cout << "arr7: " << arr7 << endl;
    cout << "arr8: " << arr8 << endl;
    cout << "arr7 + arr8: " << arrsumm << endl;

    arr7 += arr8;
    cout << "����� arr7 += arr8: " << arr7 << endl;

    cout << "arr7 == arr8: " << (arr7 == arr8) << endl;
    cout << "arr7 != arr8: " << (arr7 != arr8) << endl;

    // ���� ��������� []
    cout << "\n6. ���� ��������� []:" << endl;
    cout << "arr7[0]: " << arr7[0] << " (���������: 10)" << endl;
    cout << "arr7[1]: " << arr7[1] << " (���������: 20)" << endl;
    arr7[0] = 100;
    cout << "����� arr7[0] = 100: " << arr7 << endl;

    // ���� ������������
    cout << "\n7. ������������:" << endl;
    int data9[] = { 100, 200, 300 };
    DynamicArray<int> arr9(data9, 3);
    cout << "������ arr9: " << arr9 << endl;

    DynamicArray<int> arr10;
    arr10 = arr9;
    cout << "����� arr10 = arr9, arr10: " << arr10 << endl;

    // ���� ������
    cout << "\n8. ���� ������:" << endl;
    int data11[] = { 1, 2 };
    DynamicArray<int> arr11(data11, 2);

    int data12[] = { 9, 8 };
    DynamicArray<int> arr12(data12, 2);

    cout << "�� ������ - arr11: " << arr11 << ", arr12: " << arr12 << endl;
    arr11.ArraysSwap(arr12);
    cout << "����� ������ - arr11: " << arr11 << ", arr12: " << arr12 << endl;

    // ���� �������� ���� ��������
    cout << "\n9. ���� �������� ���� ��������:" << endl;
    int data13[] = { 1, 2, 3, 2, 4, 2 };
    DynamicArray<int> arr13(data13, 6);

    cout << "�� removeAllValue(2): " << arr13 << endl;
    arr13.removeAllValue(2);
    cout << "����� removeAllValue(2): " << arr13 << endl;

    // ���� �������� � ��������
    cout << "\n10. ���� �������� � ��������:" << endl;
    DynamicArray<int> arr14;
    arr14.setArrayLength(3);
    arr14.setAt(0, 7);
    arr14.setAt(1, 8);
    arr14.setAt(2, 9);
    cout << "������ ����� set �������: " << arr14 << endl;
    cout << "getAt(1): " << arr14.getAt(1) << " (���������: 8)" << endl;

    const int* rawData = arr14.getArrayData();
    cout << "getArrayData(): [" << rawData[0] << ", " << rawData[1] << ", " << rawData[2] << "]" << endl;

    // ��� float
    cout << "\n\n��� float" << endl << endl;

    // ���� �������������
    cout << "\n1. ���� �������������:" << endl;
    DynamicArray<float> arr1_float;
    cout << "����������� �� ��������� - �����: " << arr1_float.getArrayLength() << "  �������: 0" << endl;

    float testData_float[] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };
    DynamicArray<float> arr2_float(testData_float, 5);
    cout << "����������� �� �������� ������� - �����: " << arr2_float.getArrayLength() << "  �������: 5" << endl;

    DynamicArray<float> arr3_float(arr2_float);
    cout << "����������� ����������� - �����: " << arr3_float.getArrayLength() << "  �������: 5" << endl;

    // ���� ������� � ��������
    cout << "\n2. ���� ������� � ��������:" << endl;
    float initialData_float[] = { 10.5f, 20.5f, 30.5f, 40.5f, 50.5f };
    DynamicArray<float> arr5_float(initialData_float, 5);
    float x_float;
    int y_float;
    cout << "�������� ������: " << arr5_float << endl;
    cout << "������� ������� ��� ������� � ������, ���� �� ����������� ��� ���������: ";
    cin >> x_float >> y_float;
    if (!arr5_float.insertAt(y_float, x_float)) cout << "������������ ������" << endl;
    else cout << "������ ����� �������: " << arr5_float << endl;

    arr5_float.removeAt(1);
    cout << "����� �������� ������� ��������: " << arr5_float << endl;

    cout << "������� �������� ��� �������� ������� ���������: ";
    cin >> x_float;
    if (!arr5_float.removeFirstValue(x_float)) cout << "������� �� ������" << endl;
    else cout << "����� removeFirstValue(" << x_float << "): " << arr5_float << endl;

    // ���� ������
    cout << "\n3. ���� ������:" << endl;
    float searchData_float[] = { 5.5f, 3.3f, 8.8f, 3.3f, 1.1f };
    DynamicArray<float> arr6_float(searchData_float, 5);

    cout << "������: " << arr6_float << endl;
    cout << "findElement(3.3): " << arr6_float.findElement(3.3f) << " (���������: 1)" << endl;
    cout << "findElement(10.0): " << arr6_float.findElement(10.0f) << " (���������: -1)" << endl;
    cout << "findMaxEl(): " << arr6_float.findMaxEl() << " (���������: 8.8)" << endl;
    cout << "findMinEl(): " << arr6_float.findMinEl() << " (���������: 1.1)" << endl;

    // ���� ����������
    cout << "\n4. ���� ����������:" << endl;
    DynamicArray<float> arrsort_float;
    cout << "������� ����� ������� ��� ����������: ";
    int len_float;
    cin >> len_float;
    arrsort_float.setArrayLength(len_float);
    cout << "������� " << len_float << " ���������: ";
    for (int i = 0; i < len_float; i++) {
        float val;
        cin >> val;
        arrsort_float.setAt(i, val);
    }
    cout << "�� ����������: " << arrsort_float << endl;
    arrsort_float.sort();
    cout << "����� ����������: " << arrsort_float << endl;

    // ���� ����������
    cout << "\n5. ���� ����������:" << endl;
    float data7_float[] = { 1.5f, 2.5f };
    DynamicArray<float> arr7_float(data7_float, 2);

    float data8_float[] = { 3.5f, 4.5f };
    DynamicArray<float> arr8_float(data8_float, 2);

    DynamicArray<float> arrsumm_float = arr7_float + arr8_float;
    cout << "arr7: " << arr7_float << endl;
    cout << "arr8: " << arr8_float << endl;
    cout << "arr7 + arr8: " << arrsumm_float << endl;

    arr7_float += arr8_float;
    cout << "����� arr7 += arr8: " << arr7_float << endl;

    cout << "arr7 == arr8: " << (arr7_float == arr8_float) << endl;
    cout << "arr7 != arr8: " << (arr7_float != arr8_float) << endl;

    // ��� Char
    cout << "\n\n���� char" << endl << endl;

    // ���� �������������
    cout << "\n1. ���� �������������:" << endl;
    DynamicArray<char> arr1_char;
    cout << "����������� �� ��������� - �����: " << arr1_char.getArrayLength() << "  �������: 0" << endl;

    char testData_char[] = { 'A', 'B', 'C', 'D', 'E' };
    DynamicArray<char> arr2_char(testData_char, 5);
    cout << "����������� �� �������� ������� - �����: " << arr2_char.getArrayLength() << "  �������: 5" << endl;

    DynamicArray<char> arr3_char(arr2_char);
    cout << "����������� ����������� - �����: " << arr3_char.getArrayLength() << "  �������: 5" << endl;

    // ���� ������� � ��������
    cout << "\n2. ���� ������� � ��������:" << endl;
    char initialData_char[] = { 'H', 'e', 'l', 'l', 'o' };
    DynamicArray<char> arr5_char(initialData_char, 5);
    char x_char;
    int y_char;
    cout << "�������� ������: " << arr5_char << endl;
    cout << "������� ������ ��� ������� � ������, ���� �� ����������� ��� ���������: ";
    cin >> x_char >> y_char;
    if (!arr5_char.insertAt(y_char, x_char)) cout << "������������ ������" << endl;
    else cout << "������ ����� �������: " << arr5_char << endl;

    arr5_char.removeAt(1);
    cout << "����� �������� ������� ��������: " << arr5_char << endl;

    cout << "������� ������ ��� �������� ������� ���������: ";
    cin >> x_char;
    if (!arr5_char.removeFirstValue(x_char)) cout << "������� �� ������" << endl;
    else cout << "����� removeFirstValue(" << x_char << "): " << arr5_char << endl;

    // ���� ������
    cout << "\n3. ���� ������:" << endl;
    char searchData_char[] = { 'A', 'B', 'C', 'D', 'E' };
    DynamicArray<char> arr6_char(searchData_char, 5);

    cout << "������: " << arr6_char << endl;
    cout << "findElement('A'): " << arr6_char.findElement('A') << " (���������: 0)" << endl;
    cout << "findElement('Q'): " << arr6_char.findElement('Q') << " (���������: -1)" << endl;
    cout << "findMaxEl(): " << arr6_char.findMaxEl() << " (���������: E)" << endl;
    cout << "findMinEl(): " << arr6_char.findMinEl() << " (���������: A)" << endl;

    // ���� ����������
    cout << "\n4. ���� ����������:" << endl;
    DynamicArray<char> arrsort_char;
    cout << "������� ����� ������� ��� ����������: ";
    int len_char;
    cin >> len_char;
    arrsort_char.setArrayLength(len_char);
    cout << "������� " << len_char << " ��������: ";
    for (int i = 0; i < len_char; i++) {
        char val;
        cin >> val;
        arrsort_char.setAt(i, val);
    }
    cout << "�� ����������: " << arrsort_char << endl;
    arrsort_char.sort();
    cout << "����� ����������: " << arrsort_char << endl;

    // ���� ����������
    cout << "\n5. ���� ����������:" << endl;
    char data7_char[] = { '+', '+' };
    DynamicArray<char> arr7_char(data7_char, 2);

    char data8_char[] = { '-', '-' };
    DynamicArray<char> arr8_char(data8_char, 2);

    DynamicArray<char> arrsumm_char = arr7_char + arr8_char;
    cout << "arr7: " << arr7_char << endl;
    cout << "arr8: " << arr8_char << endl;
    cout << "arr7 + arr8: " << arrsumm_char << endl;

    arr7_char += arr8_char;
    cout << "����� arr7 += arr8: " << arr7_char << endl;

    cout << "arr7 == arr8: " << (arr7_char == arr8_char) << endl;
    cout << "arr7 != arr8: " << (arr7_char != arr8_char) << endl;

    // ���� �������� ���� ��������
    cout << "\n6. ���� �������� ���� ��������:" << endl;
    char data13_char[] = { 'a', 'b', 'a', 'c', 'a', 'd' };
    DynamicArray<char> arr13_char(data13_char, 6);

    cout << "�� removeAllValue('a'): " << arr13_char << endl;
    arr13_char.removeAllValue('a');
    cout << "����� removeAllValue('a'): " << arr13_char << endl;

    return 0;
}