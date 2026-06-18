// Лабораторная работа 6
// Создание и использование собственного класса Stroka.

#include <iostream>
#include "Stroka.h"

using namespace std;

int main()
{
    system("chcp 1251>nul");

    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 6 ===" << endl;

    Stroka s1("qwert");
    Stroka s2("asdfg");
    Stroka s3;
    Stroka s4(s1);
    Stroka s5(120);

    cout << "Введите строку s3: ";
    s3.vvod();

    s5 = s1 + s2 + s4;

    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;
    cout << "s5 = " << s5 << endl;
    cout << "Длина s5 = " << s5.dlina() << endl;

    if (s1 == s5) {
        cout << "Строки s1 и s5 равны" << endl;
    }
    else if (s1 == s4) {
        cout << "Строки s1 и s4 равны" << endl;
    }
    else {
        cout << "Равных строк не найдено" << endl;
    }

    return 0;
}
