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
    double geta() const;
    double getb() const;
    double getc() const;

    void seta(double a);
    void setb(double b);
    void setc(double c);

    //4) �������� �� ������ ����� ������ ���������
    bool PassingOrigins() const;
    double getIntercepsOX() const;
    double getIntercepsOY() const;
    
};
