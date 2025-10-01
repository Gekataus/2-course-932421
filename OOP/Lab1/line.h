#pragma once
#include "line.h"
#include <iostream>
#include <math.h>

class Line
{
private:
    double a_, b_, c_;

public:
    // 1) �����������
    Line(); // � ����������� �� ���������

    // 2) ����/����� ��������� ������
    void input();
    void output() const;

    // 3) ���������
    double getA() const;
    double getB() const;
    double getC() const;

    void setA(double a);
    void setB(double b);
    void setC(double c);

    //4) �������� �� ������ ����� ������ ���������
    bool PassingOrigins() const;

    // 5) ��������, ����������� �� ������ ��� Ox
    bool isParallelToOX() const;

    // 6) ���������� ��������, ���������� ������ �� ������������ ����
    double getIntercepsOX() const;
    double getIntercepsOY() const;

    // 7) ���������� �������� ������������ ������
    double getSlope() const;

    // 8) �������� ���������� ���� ������ (����� ==)
    bool operator==(const Line& other) const;

};