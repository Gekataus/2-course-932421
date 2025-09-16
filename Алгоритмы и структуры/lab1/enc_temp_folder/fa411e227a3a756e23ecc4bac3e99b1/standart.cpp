#include <iostream>
#include <random>
#include <chrono>
#include <time.h>
#include <stdio.h>

using namespace std;

void RandMatrAnyIntD(int** matr, int m, int n, int a, int b)
{
	srand(time(0));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			if(i != j) matr[i][j] = rand() % (b - a + 1) + a;
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
	while (0 < i < n && p[i] > p[i + 1]) i--;
	if (i < 0) return false;
	int j = n - 1;
	while (i < j <= n && p[i] < p[j]) j--;
	Swap(&p[i], &p[j]);
	int left = i + 1;
	int right = n - 1;
	while (left < right) 
		{
			Swap(&p[left], &p[right]);
			++left;
			--right;
		}
	return true;
}

int main()
{
	int n; int start = 1;
	int** matr;
	int i = 0;

	std::cout << "enter number of cities: ";
	cin >> n;

	/*cout << "enter town from what you want to start: ";
	cin >> start;*/

	matr = new int* [n];
	for (i = 0; i < n; i++) matr[i] = new int[n]();
	RandMatrAnyIntD(matr, n, n, 1, 10);
	std::cout << "Your cost matrix:\n";
	OutputMatrIntD(matr, n, n);

	int cost = 0; int cost_min = 100000;
	int j = ++start;
	int* p;
	p = new int[n - 1];
	for (i = 0; i < n - 1; i++) p[i] = j++;

	while (Permutation(p, n))
	{
		int i = 0;
		cost += matr[start][p[i]];
		while (i < n - 1)
		{	
			cost += matr[p[i]][p[i + 1]];
			i++;
		}
		cost += matr[p[i]][start];
	
		if (cost < cost_min) cost_min = cost;
		
	}

	std::cout << "min cost = " << cost_min;

	


}