#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 1. Функция получения индекса первого вхождения подстроки в тексте
int findFirst(const std::string& s, const std::string& p) {
    if (p.empty() || s.empty() || p.length() > s.length()) {
        return -100;
    }

    int n = s.length();
    int m = p.length();

    int TAB[256];
    for (int i = 0; i < 256; i++) TAB[i] = m;
    for (int i = 0; i < m - 1; i++) TAB[p[i]] = m - 1 - i;

    int k;
    int i = m - 1, j = m - 1;
    while (i < n && j >= 0)
    {
        k = i;
        j = m - 1;
        while (j >= 0)
        {
            if (s[k] == p[j]) 
            { 
                k--; 
                j--; 
            }
            else 
            { 
                i = i + TAB[s[i]]; 
                j = i - m + 1; 
                break; 
            }
        }
    }
    if (j < 0) return (i + 1 - m);
    else return -1;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int f;
    string s, p;
    cout << "Введите текст для сравнения: ";
    getline(cin, s);
    cout << endl << "Введите паттерн: ";
    getline(cin, p);

    f = findFirst(s, p);
    cout << endl << f;
}