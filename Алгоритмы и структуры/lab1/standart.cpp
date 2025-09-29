#include <iostream>
#include "function.h"
#include <chrono>

int main()
{
	int n,i; int start = 1, j = 0;
	int** matr;

	std::cout << "enter number of cities: ";
	std::cin >> n;

	std::cout << "enter town from what you want to start: ";
	std::cin >> start;

	matr = new int* [n];
	for (i = 0; i < n; i++) matr[i] = new int[n]();

	RandMatrAnyIntD(matr, n, n, 1, 10);
	std::cout << "Your cost matrix:\n";
	OutputMatrIntD(matr, n, n);

	int cost = 0; int cost_min = 100000; int cost_max = 0;
	
	int* p;
	p = new int[n - 1];
	for (i = 0; i < n - 1; i++, j++)
	{	
		if (j == start) p[i] = ++j;
		else p[i] = j;
	}

	int* bestPermutation;
	bestPermutation = new int[n - 1];

	int* worstPermutation;
	worstPermutation = new int[n - 1];

	std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
	
	do
	{
		//std::cout << "\np = "; OutputMasPtr(p, n - 1);
		cost = 0;
		cost += matr[start][p[0]];
		for (i = 0; i < n - 2; i++) cost += matr[p[i]][p[i + 1]];
		cost += matr[p[i]][start];
		//std::cout << "    cost = " << cost;
		if (cost < cost_min) { cost_min = cost; CopyMas(p, bestPermutation, n-1); }
		if (cost > cost_max) {cost_max = cost; CopyMas(p, worstPermutation, n - 1); }
		//std::cout << "    min cost = " << cost_min;
	} while (Permutation(p, n - 1));

	std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = timeEnd - timeStart;

	std::cout << "min cost = " << cost_min;
	std::cout << ";  Best Permutation: " << "[ " << start; OutputMasPtr(bestPermutation, n - 1); std::cout << " " << start << " ]" << std::endl;
	std::cout << "max cost = " << cost_max;
	std::cout << ";  Worst Permutation: " << "[ " << start; OutputMasPtr(worstPermutation, n - 1); std::cout << " " << start << " ]" << std::endl;
	std::cout << "time: " << duration.count()  << std::endl;

	//3d method
	int step = 0, cost_min3d = 0, col_min = 0, itec = start, k = 0, f = -2;
	int* ThirdMethod;
	ThirdMethod = new int[n + 1];
	for (i = 0; i < n + 1; i++) ThirdMethod[i] = -1;
	ThirdMethod[k] = start; k++;

	std::chrono::high_resolution_clock::time_point timeStartNew = std::chrono::high_resolution_clock::now();

	while (step < n-1)
	{
		FindMinElement(matr, n, &itec, &col_min);
		f = Find(ThirdMethod, n + 1, col_min);
		if (f != -1) { matr[itec][col_min] = 0; FindMinElement(matr, n, &itec, &col_min);}
		cost_min3d += matr[itec][col_min];
		ThirdMethod[k] = col_min; k++;
		
		
		for (i = itec, j = 0; j < n; j++) matr[i][j] = 0;
		for (i = 0, j = col_min; i < n; i++) matr[i][j] = 0;
		
		//std::cout << itec << " " << col_min << std::endl;
		
		itec = col_min;
		
		
		step++;
	}
	cost_min3d += matr[itec][start];
	ThirdMethod[k] = start;

	std::chrono::high_resolution_clock::time_point timeEndNew = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> durationNew = timeEndNew - timeStartNew;

	std::cout << "min cost 3d metod = " << cost_min3d;
	std::cout << "; Third Method: " << "[ "; OutputMasPtr(ThirdMethod, n + 1); std::cout << " ]";
	std::cout << "\ntime: " << durationNew.count() << std::endl;
	

	
	for (i = 0; i < n; i++) delete[] matr[i];
	delete[] matr; delete[] p; delete[] bestPermutation; delete[] worstPermutation; delete[] ThirdMethod;
}