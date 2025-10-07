#pragma once
#include "line.h"
#include <iostream>
#include <math.h>

class Line
{
private:
    double a_, b_, c_;

public:
    // 1) Конструктор
    Line(); // по умолчанию

    // 2) Ввод/вывод уравнения прямой
    void input();
    void output() const;

    // 3) Аксессоры
    double getA() const;
    double getB() const;
    double getC() const;

    void setA(double a);
    void setB(double b);
    void setC(double c);

    //4) Проходит ли прямая через начало координат
    bool PassingOrigins() const;

    // 5) проверка, параллельна ли прямая оси Ox
    bool isParallelToOX() const;

    // 6) нахождение отрезков, отсекаемых прямой на координатных осях
    double getIntercepsOX() const;
    double getIntercepsOY() const;

    // 7) нахождение углового коэффициента прямой
    double getSlope() const;

    // 8) Проверка совпадения двух прямых (через ==)
    bool operator==(const Line& other) const;

    // 9) Проверка параллельности двух прямых
    bool isParallelTo(const Line& other) const;

    // 10) Проверка принадлежности точки прямой
    bool containsPoint(double x, double y) const;

    // 11) Нахождение расстояния от точки до прямой
    double distanceToPoint(double x, double y) const;

    // 12) Нахождение точки пересечения двух прямых
    bool findIntersection(const Line& other, double& x, double& y) const;

    // 13) Нахождение расстояния между двумя параллельными прямыми
    double distanceToParallelLine(const Line& other) const;

};