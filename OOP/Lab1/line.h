#pragma once
#include "line.h"
#include <iostream>
#include <math.h>

class Line
{
private:
    double a_, b_, c_;

public:
    // 1)  онструктор
    Line(); // с аргументами по умолчанию

    // 2) ¬вод/вывод уравнени€ пр€мой
    void input();
    void output() const;

    // 3) јксессоры
    double getA() const;
    double getB() const;
    double getC() const;

    void setA(double a);
    void setB(double b);
    void setC(double c);

    //4) ѕроходит ли пр€ма€ через начало координат
    bool PassingOrigins() const;

    // 5) проверка, параллельна ли пр€ма€ оси Ox
    bool isParallelToOX() const;

    // 6) нахождение отрезков, отсекаемых пр€мой на координатных ос€х
    double getIntercepsOX() const;
    double getIntercepsOY() const;

    // 7) нахождение углового коэффициента пр€мой
    double getSlope() const;

    // 8) ѕроверка совпадени€ двух пр€мых (через ==)
    bool operator==(const Line& other) const;

};