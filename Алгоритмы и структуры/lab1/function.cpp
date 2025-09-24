#include "function.h"
#include <random>
#include <chrono>

std::random_device randomDevice;
std::mt19937_64 generator(randomDevice());
int rangeStart = 1;
int rangeEnd = 25;
std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);


void RandMatrAnyIntD(int** matr, int m, int n, int a, int b)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			if (i != j) matr[i][j] = distribution(generator);
		}
}

void OutputMatrIntD(int** matr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf_s("%5d", matr[i][j]);
		printf_s("\n");
	}
}

void Swap(int* a, int* b)
{
	int per = *a;
	*a = *b;
	*b = per;
}

bool Permutation(int* p, int n)
{
	int i = n - 2;
	while (i >= 0 && p[i] >= p[i + 1]) i--;
	if (i < 0) return false;
	int j = n - 1;
	while (p[i] >= p[j]) j--;
	Swap(&p[i], &p[j]);
	int left = i + 1;
	int right = n - 1;
	while (left < right)
	{
		Swap(&p[left], &p[right]);
		left++;
		right--;
	}
	return true;
}

void OutputMasPtr(int* a, int n)
{
	for (int* p = a; p < a + n; p++) printf("%4d", *p);
}

void FindMinElement(int** matr, int n, int* str, int* col_min)
{
	int col;
	int min = 100000;
	for (col = 0; col < n; col++)
		if (matr[*str][col] < min && matr[*str][col] != 0) {*col_min = col; min = matr[*str][col];}
}

void CopyMas(int* a, int* b, int n)
{
	int i;
	for (i = 0; i < n; i++) b[i] = a[i];
}

int Find(int* a, int n, int B)
{
	for (int i = 0; i < n; i++)
		if (a[i] == B) return i;
	return -1;
}