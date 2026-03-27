#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Header.h"
#include <iomanip>

void File10() {
    using namespace std;
    ifstream fin("File10_input.dat", ios::binary);
    if (!fin.is_open()) {
        cout << "Ошибка: не найден файл" << endl;
        return;
    }
    fin.seekg(0, ios::end);
    int n = fin.tellg() / 4;
    fin.seekg(0, ios::beg);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        fin.read((char*)&a[i], 4);
    }
    fin.close();
    ofstream fout("File10_output.dat", ios::binary);
    for (int i = n - 1; i >= 0; i--) {
        fout.write((char*)&a[i], 4);
    }
    fout.close();
    cout << "Было:  ";
    for (int i = 0; i < n; i++) cout << setw(2) << a[i] << " ";
    cout << "\nСтало: ";
    ifstream res("File10_output.dat", ios::binary);
    int x;
    while (res.read((char*)&x, 4)) {
        cout << setw(2) << x << " ";
    }
    cout << endl;
}

void createFile10() {
    using namespace std;
    ofstream fout("File10_input.dat", ios::binary);
    srand(time(0));
    int n = 5 + rand() % 16;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        fout.write((char*)&a[i], 4);
    }
    cout << endl;
    fout.close();
}

void File30() {
    using namespace std;
    ifstream fin("File30.dat", ios::binary);
    if (!fin.is_open()) {
        cout << "Ошибка: не найден файл" << endl;
        return;
    }
    fin.seekg(0, ios::end);
    int n = fin.tellg() / 4;
    fin.seekg(0, ios::beg);

    if (n % 2 != 0) {
        cout << "Ошибка: нужно четное количество" << endl;
        fin.close();
        return;
    }
    int os = n / 2;
    vector<int> a(os);
    for (int i = 0; i < os; i++) {
        fin.read((char*)&a[i], 4);
    }
    fin.close();
    ofstream fout("File30.dat", ios::binary | ios::trunc);
    for (int i = 0; i < os; i++) {
        fout.write((char*)&a[i], 4);
    }
    fout.close();
    cout << "Осталось " << setw(2) << os << " чисел: ";
    for (int i = 0; i < os; i++) cout << a[i] << " ";
    cout << endl;
}
void createFile30() {
    using namespace std;
    ofstream fout("File30.dat", ios::binary);
    srand(time(0));
    int n = 8 + (rand() % 10) * 2;
    vector<int> a(n);
    cout << "В файле  " << setw(2) << n << " чисел: ";
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        fout.write((char*)&a[i], 4);
        cout << a[i] << " ";
    }
    cout << endl;
    fout.close();
}

void File52(int n) {
    using namespace std;
    vector<string> files = { "S1.dat", "S2.dat", "S3.dat", "S4.dat" };
    vector<vector<int>> d(n);
    vector<int> siz(n);
    for (int i = 0; i < n; i++) {
        ifstream fin(files[i], ios::binary);
        if (!fin.is_open()) {
            cout << "Ошибка: не найден файл " << files[i] << endl;
            return;
        }
        fin.seekg(0, ios::end);
        siz[i] = fin.tellg() / 4;
        fin.seekg(0, ios::beg);
        d[i].resize(siz[i]);
        for (int j = 0; j < siz[i]; j++) {
            fin.read((char*)&d[i][j], 4);
        }
        fin.close();
    }
    ofstream fout("S0.dat", ios::binary);
    fout.write((char*)&n, 4);
    for (int i = 0; i < n; i++) {
        fout.write((char*)&siz[i], 4);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < siz[i]; j++) {
            fout.write((char*)&d[i][j], 4);
        }
    }
    fout.close();
    cout << "Архив успешно создан!" << endl;
    ifstream res("S0.dat", ios::binary);
    int x;
    while (res.read((char*)&x, 4)) {
        cout << setw(2) << x << " ";
    }
    cout << endl;
}

void createFile52(int n) {
    using namespace std;
    srand(time(0));
    vector<string> files = { "S1.dat", "S2.dat", "S3.dat", "S4.dat"};
    vector<int> con = { 0, 0, 0, 0};
    for (int i = 0; i < n; i++) {
        con[i] = 1 + rand() % 10;
    }
    for (int i = 0; i < n; i++) {
        ofstream fout(files[i], ios::binary);
        cout << files[i] << " (" << con[i] << " чисел): ";
        for (int j = 0; j < con[i]; j++) {
            int x = 10 + rand() % 90; 
            fout.write((char*)&x, 4);
            cout << x << " ";
        }
        cout << endl;
        fout.close();
    }
}

int calc(const std::string& s, int& p) {
    if (p >= s.length()) return 0;

    // Пропуск пробелов
    if (s[p] == ' ') {
        p++;
        return calc(s, p);
    }

    // Цифра
    if (s[p] >= '0' && s[p] <= '9') {
        return s[p++] - '0';
    }

    // Скобка
    if (s[p] == '(') {
        p++;
        int a = calc(s, p);

        if (s[p] == ')') {
            p++;
            return a;
        }

        char op = s[p++];
        int b = calc(s, p);

        int r;
        if (op == '+') r = a + b;
        else if (op == '-') r = a - b;
        else r = a * b;

        if (s[p] == ')') {
            p++;
            return r;
        }

        // Есть еще операции
        std::string rest = s.substr(p);
        std::string newExpr = std::to_string(r) + rest;
        p = 0;
        return calc(newExpr, p);
    }

    // Выражение без скобок (первый символ - цифра)
    int left = s[p++] - '0';

    if (p >= s.length()) return left;

    char op = s[p++];

    // Определяем правую часть
    int right;
    if (p < s.length() && s[p] == '(') {
        right = calc(s, p);
    }
    else if (p < s.length() && s[p] >= '0' && s[p] <= '9') {
        right = s[p++] - '0';
    }
    else {
        right = 0;
    }

    int result;
    if (op == '+') result = left + right;
    else if (op == '-') result = left - right;
    else result = left * right;

    // Если есть продолжение
    if (p < s.length() && s[p] != ' ' && s[p] != ')') {
        std::string rest = s.substr(p);
        std::string newExpr = std::to_string(result) + rest;
        p = 0;
        return calc(newExpr, p);
    }

    return result;
}

void Recur17() {
    using namespace std;
    ifstream fin("Recur17_input.dat");
    if (!fin.is_open()) {
        cout << "Ошибка: не найден файл" << endl;
        return;
    }
    string s;
    fin >> s;
    fin.close();
    cout << "Выражение: " << s << endl;
    int p = 0;
    int res = calc(s, p);
    ofstream fout("Recur17_output.dat");
    fout << res << endl;
    fout.close();
    cout << "Результат: " << res << endl;
}

void createRecur17() {
    using namespace std;
    srand(time(0));
    vector<string> exs = { "(3+5-(9-2+(4*5)-(1-(3*0))-6))"};
    int idx = rand() % exs.size();
    ofstream fout("Recur17_input.dat", ios::binary);
    string s = exs[idx];
    fout.write(s.c_str(), s.length());
    fout.close();
}