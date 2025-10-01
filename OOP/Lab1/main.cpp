#include <iostream>
#include "line.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Line x1, x2;

	x1.input();
	x1.output();

	
	if (x1.PassingOrigins()) std::cout << "ѕр€ма€ проходит через начало координат" << std::endl;
	else std::cout << "ѕр€ма€ не проходит через начало координат" << std::endl;

	double x = 0, y = 0;

	x = x1.getIntercepsOX();
	std::cout << x << std::endl;
	x1.output();

}