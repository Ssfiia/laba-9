#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include "Header.h"
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    using namespace std;
    int choice, N, K;
    do {
        cout << "\n ВЫБОР ЗАДАНИЯ " << endl;
        cout << "1. File10: В обратном порядке." << endl;
        cout << "2. File30: Удалить вторую половину ." << endl;
        cout << "3. File52: Файл-архив." << endl;
        cout << "4. Recur17: Значение целочисленного выражения." << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Обратный порядок элементов" << endl;
            createFile10();
            File10();
            break;
        case 2:
            cout << "Удаление второй половины" << endl << endl;
            createFile30();
            File30();
            break;
        case 3:
            int n;
            cout << "Создание архива" << endl << endl;
            do {
                cout << "Введите количество файлов (<= 4): ";
                cin >> n;
                if (n <= 0 || n > 4) cout << "Количество файлов должно быть положительным и меньше 5" << endl;
            } while (n <= 0 || n > 4);
            createFile52(n);
            File52(n);
            break;
        case 4:
            cout << "Вычисление выражения" << endl << endl;
            createRecur17();
            Recur17();
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
}
