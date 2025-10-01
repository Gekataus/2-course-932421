#include "line.h"
#include <iostream>
#include <math.h>

Line::Line() : a_(0), b_(1), c_(0) {}
void Line::input()
{
	std::cout << "������� ������������ a, b, c ������ ax + by + c = 0 " << std::endl;
	std::cin >> a_ >> b_ >> c_;
}

void Line::output() const
{
    std::cout << a_ << "x + " << b_ << "y + " << c_ << " = 0" << std::endl;
}

// �������
double Line::geta() const { return a_; }
double Line::getb() const { return b_; }
double Line::getc() const { return c_; }

// �������
void Line::seta(double a) {
    a_ = a;
    if (a_ == 0 && b_ == 0) {
        std::cout << "��������������: ������������ a � b ����� ������������ ��������, ����������� �������� �� ���������: a = 0, b = 1" << std::endl;
        b_ = 1;
    }
}

void Line::setb(double b) {
    b_ = b;
    if (a_ == 0 && b_ == 0) {
        std::cout << "��������������: ������������ a � b ����� ������������ ��������, ����������� �������� �� ���������: a = 0, b = 1" << std::endl;
        b_ = 1;
    }
}

void Line::setc(double c) { c_ = c; }

//�������� ������ ���������
bool Line::PassingOrigins() const {
    if (c_ == 0) return true;
    return false;
}

// ���������� ��������, ���������� ������ �� ������������ ����
double Line::getIntercepsOX() const 
{
    if (a_ == 0) { std::cout << "������ �� �������� �� OX ��������"; return -1; }
    else return ( - c_ / a_);
}

double Line::getIntercepsOY() const
{
    if (b_ == 0) { std::cout << "������ �� �������� �� OX ��������"; return -1; }
    else return (-c_ / b_);
}

