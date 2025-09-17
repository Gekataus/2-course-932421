#include <iostream>
#include "function.h"
#include <chrono>

int main()
{
	int n; int start = 1;
	int** matr;
	int i = 0;
	int j = 0;

	std::cout << "enter number of cities: ";
	std::cin >> n;

	std::cout << "enter town from what you want to start: ";
	std::cin >> start;

	matr = new int* [n];
	for (i = 0; i < n; i++) matr[i] = new int[n]();

	RandMatrAnyIntD(matr, n, n, 1, 10);
	std::cout << "Your cost matrix:\n";
	OutputMatrIntD(matr, n, n);

	int cost = 0; int cost_min = 100000;
	
	int* p;
	p = new int[n - 1];
	for (i = 0; i < n - 1; i++, j++)
	{	
		if (j == start) p[i] = ++j;
		else p[i] = j;
	}

	std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
	do
	{
		//std::cout << "\np = "; OutputMasPtr(p, n - 1);
		cost = 0;
		cost += matr[start][p[0]];
		for (i = 0; i < n - 2; i++) cost += matr[p[i]][p[i+1]];
		cost += matr[p[i]][start];
		//std::cout << "    cost = " << cost;
		if (cost < cost_min) cost_min = cost;
		//std::cout << "    min cost = " << cost_min;
	} while (Permutation(p, n - 1));

	std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = timeEnd - timeStart;
	std::cout << "time: " << duration.count() << std::endl;

	std::cout << "\nmin cost = " << cost_min;

	
	for (i = 0; i < n; i++) delete[] matr[i];
	delete[] matr; delete[] p;

	


}