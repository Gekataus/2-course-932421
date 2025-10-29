#include <iostream>
#include <vector>
#include <random>
#include <cmath>
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

// 1. ������������������ ����� (h[0]0 = n/2, h[i] = h[i-1]/2, ..., h[t] = 1)
vector<int> generateShell(int n) {
    vector<int> gaps;
    int h = n / 2;

    while (h > 0) {
        gaps.push_back(h);
        h /= 2;
    }

    return gaps;
}

// 2. ������������������ ���� h[m] = 2^m - 1 ��� m = 1, 2, ..., t = log2(n)
vector<int> generateTwo(int n) {
    vector<int> gaps;
    int t = log2(n);

    // m = 1, 2, ..., t (� ������� ��������)
    for (int m = t; m >= 1; m--) {
        int h_m = pow(2, m) - 1;
        gaps.push_back(h_m);
    }

    return gaps;
}

// 3. ������������������ �����: h[i] = 1, h[j+1] = 3h[j] + 1 ��� j = 1, 2, ..., t-1
vector<int> generateKnuth(int n) {
    vector<int> gaps;

    // �������� � h[i] = 1
    int h_j = 1;
    gaps.push_back(h_j);

    // ��������� h[j+1] = 3h[j] + 1 ���� h[j+1] < n
    // j = 1, 2, ..., t-1 (t - ���������� ��������� � ������������������)
    while (true) {
        int h_j_plus_1 = 3 * h_j + 1;  // h[j+1] = 3h[j] + 1
        if (h_j_plus_1 >= n) {
            break;
        }
        gaps.push_back(h_j_plus_1);
        h_j = h_j_plus_1;
    }

    // ����������� ��� ������������� �� �������� � ��������
    reverse(gaps.begin(), gaps.end());

    return gaps;
}

//���������� �����
void shellSort(vector<int>& arr, const vector<int>& gaps) {
    int n = arr.size();

    for (int gap : gaps) {
        // ���������� ��������� � ������ �����
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            // �������� ��������, ���� �� ������ ���������� �������
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int x;
    vector<int> arr1;
    cout << "����� ������ � ����� ��� ������������� ������� � �������?" << endl << "� ������� - 1" << endl << "� ����� - 2" << endl;
    cin >> x;
    if (x == 1)
    {
        int n, min, max;
        cout << "������� ������ �������, ����������� � ������������ �������" << endl;
        cin >> n >> min >> max;
        vector<int> arr1 = generateRandomArray(n, min, max);
        cout << "��� ������:" << endl;
        outputArray(arr1);

        vector<int> h;
        cout << "��� ����������� ����?" << endl << "1. ������������������ �����" << endl << "2. ���������� 2 � ������� m" << endl << "3.������������������ �����" << endl;
        cin >> x;
        if (x == 1) h = generateShell(n);
        if (x == 2) h = generateTwo(n);
        if (x == 3) h = generateKnuth(n);
        shellSort(arr1, h);

        if (isSorted(arr1))
        {
            cout << "������ ������������" << endl;
            if (n < 100) {
                cout << "��������������� ������:" << endl;
                outputArray(arr1);
            }
        }
    }
}
