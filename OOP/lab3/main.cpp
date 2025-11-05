#include <iostream>
#include "booleanvector.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	//Тест конструкторов
	cout << "1. Тест конструкторов" << endl;
	BooleanVector defaultt;
	BooleanVector normal(7, 1);
	BooleanVector char_v("10101001");
	BooleanVector copy_v(char_v);

	cout << "Конструктор с параметрами:" << endl;
	cout << normal << "  Ожидалось: 1111111" << endl;

	cout << "Конструктор из массива char:" << endl;
	cout << char_v << "  Ожидалось: 10101001" << endl;

	cout << "Конструктор копирования:" << endl;
	cout << copy_v << "  Ожидалось: 10101001" << endl << endl;

	//Тест длины и веса вектора
	cout << "2. Тест методов нахождения длины и веса вектора" << endl;
	BooleanVector testLength;
	int length, weight;
	cout << "Введите вектор: "; cin >> testLength;
	length = testLength.getLength();
	weight = testLength.getWeight();
	cout << "Длина вектора = " << length << endl;
	cout << "Вес вектора = " << weight << endl << endl;

	//обмен содержимого с другим вектором (swap)
	cout << "3. Тест обмена с другим вектором (swap)" << endl;
	BooleanVector swap1("1011101"), swap2("0100110");
	cout << "Вектор 1: " << swap1 << endl;
	cout << "Вектор 2: " << swap2 << endl;
	swap1.swap(swap2);
	cout << "После обмена векторов:" << endl;
	cout << "Вектор 1: " << swap1 << endl;
	cout << "Вектор 2: " << swap2 << endl;
	cout << endl;

	//Инверсия всех компонент вектора
	cout << "4. Тест инверсии всех компонент вектора" << endl;
	BooleanVector invert;
	cout << "Введите вектор: "; cin >> invert;
	invert.invert();
	cout << "Инвертированный вектор: " << invert << endl << endl;

	//Инверсия i-ой компоненты
	cout << "5. Тест инверсии i-ой компоненты" << endl;
	BooleanVector testBit;
	cout << "Введите вектор: "; cin >> testBit;
	int x;
	cout << "Введите индекс, который хотите инвертировать: "; cin >> x;
	testBit.invertBit(x);
	cout << "Вектор с инвертированной компонентой " << x << ": " << testBit << endl << endl;

	//Установка в 0/1 i-ой компоненты
	cout << "6. Тест установки в 0/1 i-ой компоненты" << endl;
	BooleanVector testSetBit;
	cout << "Введите вектор: "; cin >> testSetBit;
	int bool_el, el;
	cout << "Введите компоненту, которую хотите установить, и во что хотите установить (0 или 1): ";
	cin >> el >> bool_el;
	testSetBit.setBit(el, bool_el);
	cout << "Новый вектор: " << testSetBit << endl << endl;

	//Перегрузка операций
	cout << "7. Тест перегрузки операций" << endl;
	BooleanVector operations1, operations2;
	cout << "Введите вектор1: "; cin >> operations1;
	cout << "Введите вектор2: "; cin >> operations2;
	int index;
	cout << "Введите индекс: "; cin >> index;
	cout << "вектор1[" << index << "] = " << operations1[index] << endl;
	cout << "вектор2[" << index << "] = " << operations2[index] << endl;
	
	BooleanVector multiplication = operations1 & operations2;
	BooleanVector summ = operations1 | operations2;
	BooleanVector XOR = operations1 ^ operations2;
	BooleanVector invertion = ~operations1;
	BooleanVector equal = operations2;

	cout << "8. Побитовые сдвиги" << endl;

}