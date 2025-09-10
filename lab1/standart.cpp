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

int main()
{
	int town, start;
	int** matr;
	int i = 0;

	cout << "enter number of cities: ";
	cin >> town;

	cout << "enter town from what you want to start: ";
	cin >> start;

	matr = new int* [town];
	for (i = 0; i < town; i++)
		matr[i] = new int[town]();
	RandMatrAnyIntD(matr, town, town, 1, 15);
	cout << "Your cost matrix:\n";
	OutputMatrIntD(matr, town, town);


}