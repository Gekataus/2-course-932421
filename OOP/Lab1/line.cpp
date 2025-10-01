#include "line.h"
#include <iostream>
#include <math.h>

// 1) Конструктор
Line::Line() : a_(0), b_(1), c_(0) {}
// 2) Ввод - вывод
void Line::input()
{
	std::cout << "Введите коэффициенты a, b, c прямой ax + by + c = 0 " << std::endl;
	std::cin >> a_ >> b_ >> c_;
}

void Line::output() const
{
    std::cout << a_ << "x + " << b_ << "y + " << c_ << " = 0" << std::endl;
}
// 3) Аксессоры
// Геттеры
double Line::getA() const { return a_; }
double Line::getB() const { return b_; }
double Line::getC() const { return c_; }

// Сеттеры
void Line::setA(double a) 
{
    a_ = a;
    if (a_ == 0 && b_ == 0) 
    {
        std::cout << "Предупреждение: коэффициенты a и b стали одновременно нулевыми, установлены значение по умолчанию: a = 0, b = 1" << std::endl;
        b_ = 1;
    }
}

void Line::setB(double b) 
{
    b_ = b;
    if (a_ == 0 && b_ == 0) 
    {
        std::cout << "Предупреждение: коэффициенты a и b стали одновременно нулевыми, установлены значение по умолчанию: a = 0, b = 1" << std::endl;
        b_ = 1;
    }
}

void Line::setC(double c) { c_ = c; }

// 4) Проходит начало координат
bool Line::PassingOrigins() const 
{
    if (c_ == 0) return true;
    return false;
}

// 5) Проверка, параллельна ли прямая оси Ox
bool Line::isParallelToOX() const 
{
    // Прямая параллельна Ox, если a = 0 и b != 0
    if (a_ == 0 && b_ != 0) return true;
    return false;
}

// 6) Нахождение отрезков, отсекаемых прямой на координатных осях
double Line::getIntercepsOX() const 
{
    if (a_ == 0) { std::cout << "Прямая не отсекает на OX отрезков"; return -1; }
    else return - c_ / a_;
}

double Line::getIntercepsOY() const
{
    if (b_ == 0) { std::cout << "Прямая не отсекает на OX отрезков"; return -1; }
    else return -c_ / b_;
}

// 7) Нахождение углового коэффициента прямой
double Line::getSlope() const 
{
    // Угловой коэффициент k = -a/b (при b != 0)
    if (b_ == 0) 
    {
        return -1; // Вертикальная прямая
    }
    return - a_ / b_;
}

// 8) Проверка совпадения двух прямых (через ==)
bool Line::operator==(const Line& other) const 
{
    return (a_ == other.a_) && (b_ == other.b_) && (c_ == other.c_);
}
