#include <iostream>
#include "line.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Line x1, x2, x3; // 1) �����������

	x1.input(); // 2) ���� - �����
	std::cout << "������ x1: "; x1.output();

	// 4) �������� ����� ������ ���������
	if (x1.PassingOrigins()) std::cout << "������ x1 �������� ����� ������ ���������" << std::endl;
	else std::cout << "������ �� �������� ����� ������ ���������" << std::endl;

	// 5) ��������, ����������� �� ������ ��� Ox
	if (x1.isParallelToOX()) std::cout << "������ ����������� OX" << std::endl;
	else  std::cout << "������ �� ����������� OX" << std::endl;
	
	double x = 0.0, y = 0.0;

	// 6) �������, ���������� ������ �� ��� ���������
	x = x1.getIntercepsOX();
	std::cout << "������ x1 �� ��� OX �������� ������� ������� = " << x << std::endl;

	y = x1.getIntercepsOY();
	std::cout << "������ x1 �� ��� OY �������� ������� ������� = " << y << std::endl;

	// 7) ���������� �������� ������������ ������
	double k;
	k = x1.getSlope();
	if (k == -100) std::cout << "������ �����������";
	else std::cout << "������� ����������� ������ �1 = " << k << std::endl;

	// 8) �������� ���������� ���� ������

	std::cout << "\n�������� ���������� ���� ������. ������� ������ ��� x2" << std::endl;
	x2.input();
	std::cout << "������ x2: "; x2.output();
	if (x1 == x2) std::cout << "������ ���������" << std::endl;
	else std::cout << "������ ��  ��������" << std::endl;

	// 3) ���������
	std::cout << "\n���������." << std::endl;
	double b;
	x3.setA(5);
	std::cout << "������ �3, ����� ��������� �������� ������������ a = 5: ";
	x3.output();
	b = x3.getB();
	std::cout << "����������� b = " << b << std::endl;

	// 9) �������� �������������� ���� ������
	Line x4, x5;
	std::cout << "\n�������� �������������� ���� ������. ������� ������ ��� ������" << std::endl;
	x4.input();
	x5.input();
	std::cout << "������ x4: "; x4.output();
	std::cout << "������ x5: "; x5.output();

	if (x4.isParallelTo(x5)) std::cout << "������ �����������" << std::endl;
	else std::cout << "������ �� �����������" << std::endl;

	// 10) �������� �������������� ����� ������
	Line x6;
	std::cout << "\n�������� �������������� ����� ������." << std::endl;
	std::cout << "������� ������ ��� ������: " << std::endl;
	x6.input();
	std::cout << "������ x6: "; x6.output();
	std::cout << "������� ���������� ����� (x � y): " << std::endl;
	std::cin >> x >> y;

	if(x6.containsPoint(x, y)) std::cout << "����� A(" << x << ", " << y << ") ����������� ������ x6" << std::endl;
	else std::cout << "����� A(" << x << ", " << y << ") �� ����������� ������ x6" << std::endl;

	// 11) ���������� ���������� �� ����� �� ������
	Line x7;
	double distance;
	std::cout << "\n���������� ���������� �� ����� �� ������" << std::endl;
	std::cout << "������� ������ ��� ������: " << std::endl;
	x7.input();
	std::cout << "������ x7: "; x7.output();
	std::cout << "������� ���������� ����� (x � y): " << std::endl;
	std::cin >> x >> y;

	distance = x7.distanceToPoint(x, y);
	if (distance == 0.0) std::cout << "����� A(" << x << ", " << y << ") ����������� ������ x7" << std::endl;
	else std::cout << "���������� �� ����� �� ������ = " << distance << std::endl;

	// 12) ���������� ����� ����������� ���� ������
	Line x8, x9;
	std::cout << "\n���������� ����� ����������� ���� ������. ������� ������ ��� ������" << std::endl;
	x8.input();
	x9.input();
	std::cout << "������ x8: "; x8.output();
	std::cout << "������ x9: "; x9.output();
	if (x8.findIntersection(x9, x, y)) std::cout << "����� ����������� ������ = C(" << x << ", " << y << ")" << std::endl;
	else std::cout << "������ �����������, ����� ����������� ���" << std::endl;

	// 13) ���������� ���������� ����� ����� ������������� �������
	Line x10, x11;
	std::cout << "\n���������� ���������� ����� ����� ������������� �������. ������� ������ ��� ������" << std::endl;
	x10.input();
	x11.input();
	std::cout << "������ x10: "; x10.output();
	std::cout << "������ x11: "; x11.output();
	distance = x10.distanceToParallelLine(x11);
	if (distance == -1) std::cout << "������ �� �����������" << std::endl;
	else std::cout << "���������� ����� ����� ������� = " << distance << std::endl;

	return 0;
}