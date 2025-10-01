#include <iostream>
#include "line.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Line x1, x2, x3; // 1) �����������

	x1.input(); // 2) ���� - �����
	x1.output();

	if (x1.PassingOrigins()) std::cout << "������ �������� ����� ������ ���������" << std::endl; // 4) �������� ����� ������ ���������
	else std::cout << "������ �� �������� ����� ������ ���������" << std::endl;

	// 5) ��������, ����������� �� ������ ��� Ox
	if (x1.isParallelToOX()) std::cout << "������ ����������� OX" << std::endl;
	else  std::cout << "������ �� ����������� OX" << std::endl;

	double x = 0, y = 0;

	x = x1.getIntercepsOX();  // 6) �������, ���������� ������ �� ��� ���������
	std::cout << x << std::endl;

	y = x1.getIntercepsOY();
	std::cout << y << std::endl;

	// 7) ���������� �������� ������������ ������
	double k;
	k = x1.getSlope();
	if (k == -1) std::cout << "������ �����������";
	else std::cout << "������� ����������� ������ �1 = " << k << std::endl;


	x2.input();
	x2.output();

	// 8) �������� ���������� ���� ������
	if (x1 == x2) std::cout << "������ ���������" << std::endl;
	else std::cout << "������ ��  ��������" << std::endl;


	double b;
	x3.setA(5); // 3) ���������
	std::cout << "������ �3, ����� ��������� �������� ������������ a = 5: ";
	x3.output();
	b = x3.getB();
	std::cout << "����������� b = " << b << std::endl;

	return 0;
}