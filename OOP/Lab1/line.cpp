#include "line.h"
#include <iostream>
#include <math.h>

// 1) Конструктор
Line::Line() : a_(0), b_(1), c_(0) {}
Line::Line(double a, double b, double c)
    : a_(a), b_(b), c_(c) { if (a_ == 0 && b_ == 0) b_ = 1;}
// 2) Ввод - вывод
void Line::input()
{
	std::cout << "Введите коэффициенты a, b, c прямой " << std::endl;
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
    if (b_ == 0) { std::cout << "Прямая не отсекает на OY отрезков"; return -1; }
    else return -c_ / b_;
}

// 7) Нахождение углового коэффициента прямой
double Line::getSlope() const 
{
    // Угловой коэффициент k = -a/b (при b != 0)
    if (b_ == 0) 
    {
        return -100; // Вертикальная прямая
    }
    return - a_ / b_;
}

// 8) Проверка совпадения двух прямых (через ==)
bool Line::operator==(const Line& other) const 
{
    return (a_ == other.a_) && (b_ == other.b_) && (c_ == other.c_);
}

// 9) Проверка параллельности двух прямых
bool Line::isParallelTo(const Line& other) const {
    // a1/b1 = a2/b2 или a1*b2 = a2*b1
    return (a_ * other.b_ == other.a_ * b_);
}

// 10) Проверка принадлежности точки прямой
bool Line::containsPoint(double x, double y) const {
    // Точка принадлежит прямой, если удовлетворяет уравнению: ax + by + c = 0
    return (a_ * x + b_ * y + c_ == 0);
}

//  11) Нахождение расстояния от точки до прямой
double Line::distanceToPoint(double x, double y) const {

    if (this->containsPoint(x, y)) return 0.0; // Точка лежит на прямой
    // |ax + by + c| / sqrt(a^2 + b^2)
    double numerator = abs(a_ * x + b_ * y + c_);
    double denominator = sqrt(a_ * a_ + b_ * b_);
    return numerator / denominator;
}

// 12) Нахождение точки пересечения двух прямых
bool Line::findIntersection(const Line& other, double& x, double& y) const 
{
    if (this->isParallelTo(other)) 
    {
        return false; // Прямые параллельны, точки пересечения нет
    }
    // a1*x + b1*y + c1 = 0
    // a2*x + b2*y + c2 = 0

    /*
    a1b2x + b1b2y = -c1b2
    a2b1x + b1b2y = -c2b1

    x(a1b2-a2b1) = -c1b2 + c2b1

    x = (c2b1 - c1b2) / (a1b2 - a2b1)
    y = (c1a2 - c2a1) / (a1b2 - a2b1)
    */
    double determinant = a_ * other.b_ - other.a_ * b_;

    x = (b_ * other.c_ - other.b_ * c_) / determinant;
    y = (other.a_ * c_ - a_ * other.c_) / determinant;

    return true;
}

// 13) Нахождение расстояния между двумя параллельными прямыми
double Line::distanceToParallelLine(const Line& other) const 
{
    if (!this->isParallelTo(other)) 
    {
        return -1; // Прямые не параллельны
    }
    // |c2 - c1| / sqrt(a^2 + b^2)
    double diff = abs(other.c_ - c_);
    double denominator = sqrt(a_ * a_ + b_ * b_);
    return diff / denominator;
}
