#include "line.h"
#include <math.h>
#include <iostream>

Line::Line() { a = 0; b = 0; c = 0; }
void Line::input()
{
	std::cout << "input a,b,c: ";
	std::cin >> a >> b >> c;
}

void Line::output() const
{
	std::cout << a << "x + " << b << "y + " << c << " = 0";
}