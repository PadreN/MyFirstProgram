#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

void checkValidInput() {
    if (cin.fail()) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        throw "Помилка вводу";
    }
}

void checkParamN(double n) {
    if (n <= 0) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        throw "Параметр n має бути більший за 0";
    }
}

void checkParamsMinMax(double a, double b) {
    if (a >= b) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        throw "Параметр a повинен бути меншим за параметр b";
    }
}

void checkParamH(double h) {
    if (h <= 0) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        throw "Параметр h має бути більший за 0";
    }
}

void readInput(double& a, double& b, double& h, double& n) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Введіть значення a: ";
    cin >> a;
    checkValidInput();

    cout << "Введіть значення b: ";
    cin >> b;
    checkValidInput();
    checkParamsMinMax(a, b);

    cout << "Введіть значення h: ";
    cin >> h;
    checkValidInput();
    checkParamH(h);

    cout << "Введіть значення n: ";
    cin >> n;
    checkValidInput();
    checkParamN(n);
}

double func_y(double n, double x) {
    double y = 0;
    if (x < 0) {
        y = 1;
        for (int i = 0; i < (n - 1); i++) {
            y *= (i * i * i) + x;
        }
    }
    else {
        double sum = 0;
        for (int i = 1; i <= n - 1; i++) {
            sum = 0;
            for (int j = 1; j <= n; j++) {
                sum += x / (i + j);
            }
            y += sum;
        }
    }
    return y;
}

int main() {
    try {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);

        double a, b, h, n;
        readInput(a, b, h, n);

        int choice;
        cout << "Зберегти результат у файлі чи у консолі? (Введіть 1 чи 2): ";
        cin >> choice;
        checkValidInput();

        if (choice == 1) {                 //частина коду яка відповідає за запис у файл
            string path = "results.txt";
            ofstream fout(path);

            if (!fout.is_open()) {
                cout << "Файл не відкривається" << endl;
            }
            else {
                for (double x = a; x <= b; x += h) {
                    double y = func_y(n, x);
                    fout << "x = " << x << "\t y = " << y << endl;
                }
                fout.close();
            }
        }
        else if (choice == 2) {
            for (double x = a; x <= b; x += h) {
                double y = func_y(n, x);
                cout << "x = " << x << "\t y = " << y << endl;
            }
        }
        else {
            cout << "Введіть 1 або 2" << endl;
            return 1;
        }
    }
    catch (const char* ex) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        cout << "\n" << ex << endl;
        cerr << "Помилка." << endl;
        return 1;
    }
    catch (...) {
        cout << "\n" << "Помилка." << endl;
        return 1;
    }

    return 0;
}
