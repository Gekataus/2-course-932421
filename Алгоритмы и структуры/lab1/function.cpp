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