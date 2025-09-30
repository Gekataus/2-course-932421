#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 1. Функция получения индекса первого вхождения подстроки в тексте
int findFirst(const string& s, const string& p) {
    int n = s.size();
    int m = p.size();

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

// 2. Функция получения индексов всех вхождений подстроки в тексте
vector<int> findAll(const string& s, const string& p) 
{
    vector<int> results;

    int n = s.size();
    int m = p.size();

    int TAB[256];
    for (int i = 0; i < 256; i++) TAB[i] = m;
    for (int i = 0; i < m - 1; i++) TAB[p[i]] = m - 1 - i;

    int k;
    int i = m - 1, j;
    while (i < n) //пока не конец строки
    {
        k = i;
        j = m - 1;
        while (j >= 0) // j бежит с конца образца
        {
            if (s[k] == p[j]) //возможно, есть совадение
            {
                k--;
                j--;
            }
            else //совпадения нет, идем обратно в цикл
            {
                i = i + TAB[s[i]];
                break;
            }
        }
        if (j < 0) //нашли вхождение
        {
            results.push_back(i - m + 1);
            i++; // Сдвигаем на 1 для поиска следующего вхождения
        }
    }

    return results;
}

// 3. Функция получения индексов вхождений в заданном диапазоне
vector<int> findAllInRange(const string& s, const string& p, int start, int end) 
{
    vector<int> results;

    if (p.empty() || s.empty() || start > end || start < 0 || end >= s.size()) 
    {
        return results;
    }

    int n = end - start + 1; // длина диапазона
    int m = p.size();

    if (m > n) //образец больше диапазона
    {
        return results;
    }

    int TAB[256];
    for (int i = 0; i < 256; i++) TAB[i] = m;
    for (int i = 0; i < m - 1; i++) TAB[p[i]] = m - 1 - i;

    int k;
    int i = start + m - 1, //граница начала 
    j = m - 1;
    while (i <= end) // + граница конца
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
                break;
            }
        }
        if (j < 0) 
        {
            results.push_back(i - m + 1);
            i++; // Сдвигаем на 1 для поиска следующего вхождения
        }
    }

    return results;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int first;
    string s, p;
    vector<int> second;
    vector<int> third;

    cout << "Введите текст для сравнения (на английском): ";
    getline(cin, s);
    cout << endl << "Введите паттерн (на английском): ";
    getline(cin, p);

    if (p.empty() || s.empty())
    {
        cerr << "Ошибка: пустой текст или паттерн"; return -1;
    }

    if (p.size() > s.size())
    {
        cerr << "Ошибка: паттерн длиннее текста"; return -1;
    }

    int start;
    cout << "Введите начальную границу поиска (начиная с 0): ";
    cin >> start;
    cout << endl;

    if(start < 0)
    {
        cerr << endl << "Ошибка: некорректный ввод диапазона";
        return -1;
    }

    int end;
    cout << "Введите конечную границу поиска (до " << s.size() - 1 << "): ";
    cin >> end;
    cout << endl;

    if (start > end || end >= s.size())
    {
        cerr << endl << "Ошибка: некорректный ввод диапазона";
        return -1;
    }


    first = findFirst(s, p);
    second = findAll(s, p);
    third = findAllInRange(s, p, start, end);

    if (first == -1)
    {
        cout << "Паттерн не найден в тексте.";
        return 0;
    }
    else  cout << "Паттерн найден в тексте, индекс первого вхождения: " << first << endl;

    if (second.size() < 2) cout << "Паттерн появляется в тексте один раз" << endl;
    else
    {
        cout << "Индексы всех вхождений: [ ";
        for (int index = 0; index < second.size(); index++) cout << second[index] << " ";
        cout << "]" << endl;
    }

    if (third.size() == 0) cout << "В заданном диапазоне вхождений нет";
    else
    {
        cout << "Индексы вхождений в заданном диапазоне: [ ";
        for (int index = 0; index < third.size(); index++) cout << third[index] << " ";
        cout << "]" << endl;
    }


    return 0;
}