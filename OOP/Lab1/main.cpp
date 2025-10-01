#include <iostream>
#include "line.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Line x1, x2, x3; // 1) Конструктор

	x1.input(); // 2) Ввод - вывод
	x1.output();

	if (x1.PassingOrigins()) std::cout << "Прямая проходит через начало координат" << std::endl; // 4) Проходит через начало координат
	else std::cout << "Прямая не проходит через начало координат" << std::endl;

	// 5) проверка, параллельна ли прямая оси Ox
	if (x1.isParallelToOX()) std::cout << "Прямая параллельна OX" << std::endl;
	else  std::cout << "Прямая не параллельна OX" << std::endl;

	double x = 0, y = 0;

	x = x1.getIntercepsOX();  // 6) Отрезки, отсекаемые прямой на оси координат
	std::cout << x << std::endl;

	y = x1.getIntercepsOY();
	std::cout << y << std::endl;

	// 7) нахождение углового коэффициента прямой
	double k;
	k = x1.getSlope();
	if (k == -1) std::cout << "Прямая вертикальна";
	else std::cout << "Угловой коэффициент прямой х1 = " << k << std::endl;


	x2.input();
	x2.output();

	// 8) Проверка совпадения двух прямых
	if (x1 == x2) std::cout << "Прямые совпадают" << std::endl;
	else std::cout << "Прямые не  совадают" << std::endl;


	double b;
	x3.setA(5); // 3) Аксессоры
	std::cout << "Прямая х3, после установки сеттером коэффициента a = 5: ";
	x3.output();
	b = x3.getB();
	std::cout << "Коэффициент b = " << b << std::endl;

	return 0;
}