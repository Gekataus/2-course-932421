#include <iostream>
#include "line.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Line x1(0,0,0), x2, x3; // 1) Конструктор
	x1.output();
	x1.input(); // 2) Ввод - вывод
	std::cout << "Прямая x1: "; x1.output();

	// 4) Проходит через начало координат
	if (x1.PassingOrigins()) std::cout << "Прямая x1 проходит через начало координат" << std::endl;
	else std::cout << "Прямая не проходит через начало координат" << std::endl;

	// 5) проверка, параллельна ли прямая оси Ox
	if (x1.isParallelToOX()) std::cout << "Прямая параллельна OX" << std::endl;
	else  std::cout << "Прямая не параллельна OX" << std::endl;
	
	double x = 0.0, y = 0.0;

	// 6) Отрезки, отсекаемые прямой на оси координат
	x = x1.getIntercepsOX();
	std::cout << "Прямая x1 на оси OX отсекает отрезок длинной = " << x << std::endl;

	y = x1.getIntercepsOY();
	std::cout << "Прямая x1 на оси OY отсекает отрезок длинной = " << y << std::endl;

	// 7) нахождение углового коэффициента прямой
	double k;
	k = x1.getSlope();
	if (k == -100) std::cout << "Прямая вертикальна";
	else std::cout << "Угловой коэффициент прямой х1 = " << k << std::endl;

	// 8) Проверка совпадения двух прямых

	std::cout << "\nПроверка совпадения двух прямых. Введите данные для x2" << std::endl;
	x2.input();
	std::cout << "Прямая x2: "; x2.output();
	if (x1 == x2) std::cout << "Прямые совпадают" << std::endl;
	else std::cout << "Прямые не  совадают" << std::endl;

	// 3) Аксессоры
	std::cout << "\nАксессоры." << std::endl;
	double b;
	x3.setA(5);
	std::cout << "Прямая х3, после установки сеттером коэффициента a = 5: ";
	x3.output();
	b = x3.getB();
	std::cout << "Коэффициент b = " << b << std::endl;

	// 9) Проверка параллельности двух прямых
	Line x4, x5;
	std::cout << "\nПроверка параллельности двух прямых. Введите данные для прямых" << std::endl;
	x4.input();
	x5.input();
	std::cout << "Прямая x4: "; x4.output();
	std::cout << "Прямая x5: "; x5.output();

	if (x4.isParallelTo(x5)) std::cout << "Прямые параллельны" << std::endl;
	else std::cout << "Прямые не параллельны" << std::endl;

	// 10) Проверка принадлежности точки прямой
	Line x6;
	std::cout << "\nПроверка принадлежности точки прямой." << std::endl;
	std::cout << "Введите данные для прямой: " << std::endl;
	x6.input();
	std::cout << "Прямая x6: "; x6.output();
	std::cout << "Введите координаты точки (x и y): " << std::endl;
	std::cin >> x >> y;

	if(x6.containsPoint(x, y)) std::cout << "Точка A(" << x << ", " << y << ") принадлежит прямой x6" << std::endl;
	else std::cout << "Точка A(" << x << ", " << y << ") не принадлежит прямой x6" << std::endl;

	// 11) Нахождение расстояния от точки до прямой
	Line x7;
	double distance;
	std::cout << "\nНахождение расстояния от точки до прямой" << std::endl;
	std::cout << "Введите данные для прямой: " << std::endl;
	x7.input();
	std::cout << "Прямая x7: "; x7.output();
	std::cout << "Введите координаты точки (x и y): " << std::endl;
	std::cin >> x >> y;

	distance = x7.distanceToPoint(x, y);
	if (distance == 0.0) std::cout << "Точка A(" << x << ", " << y << ") принадлежит прямой x7" << std::endl;
	else std::cout << "Расстояние от точки до прямой = " << distance << std::endl;

	// 12) Нахождение точки пересечения двух прямых
	Line x8, x9;
	std::cout << "\nНахождение точки пересечения двух прямых. Введите данные для прямых" << std::endl;
	x8.input();
	x9.input();
	std::cout << "Прямая x8: "; x8.output();
	std::cout << "Прямая x9: "; x9.output();
	if (x8.findIntersection(x9, x, y)) std::cout << "Точка пересечения прямых = C(" << x << ", " << y << ")" << std::endl;
	else std::cout << "Прямые параллельны, точки пересечения нет" << std::endl;

	// 13) Нахождение расстояния между двумя параллельными прямыми
	Line x10, x11;
	std::cout << "\nНахождение расстояния между двумя параллельными прямыми. Введите данные для прямых" << std::endl;
	x10.input();
	x11.input();
	std::cout << "Прямая x10: "; x10.output();
	std::cout << "Прямая x11: "; x11.output();
	distance = x10.distanceToParallelLine(x11);
	if (distance == -1) std::cout << "Прямые не параллельны" << std::endl;
	else std::cout << "Расстояние между этими прямыми = " << distance << std::endl;

	return 0;
}