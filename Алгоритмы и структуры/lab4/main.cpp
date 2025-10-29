#include <iostream>
#include <vector>
#include <random>
using namespace std;

//�������� ������� ��������� ����� (���������� random)
vector<int> generateRandomArray(int size, int min_val, int max_val) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(min_val, max_val);

	vector<int> arr(size);
	for (int i = 0; i < size; i++) {
		arr[i] = distrib(gen);
	}
	return arr;
}

// ����� �������
void outputArray(const vector<int>& arr) {
	for (int num : arr) {
		cout << num << " ";
	}
	cout << endl;
}

// �������� �� �����������������
bool isSorted(vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		if (arr[i] < arr[i - 1]) {
			return false;
		}
	}
	return true;
}

// ���������� ����� � ������������������� �����
void shellSort(vector<int>& arr) {
	int n = arr.size();
	//�������� ����
	for (int gap = n / 2; gap > 0; gap /= 2) {
		// ��������� ���������� ��������� ��� ����� ����
		for (int i = gap; i < n; i++) {
			int temp = arr[i];
			int j;
			// �������� ��������, ���� �� ������ ���������� ������� ��� arr[i]
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}
int main() 
{
	vector<int> arr1 = generateRandomArray(20, 0, 99);
	outputArray(arr1);

	shellSort(arr1);
	outputArray(arr1);

	

}
