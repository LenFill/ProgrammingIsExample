// Ознакомиться со структурой программы на языке С++.
// Для этого выполнить программу возведения числа 2 в степень.
// Модифиципровать программу так, чтобы вычислять степень с любым основанием

#include <iostream>
using namespace std;
void main(void)
{
    int i, k;
    int num;
    cout << "Enter a number: ";
    cin >> num;
    int power(int, int);
    for (i = 0; i < 10; i++) {
        k = power(num, i);
        cout << "i = " << i << ", k =" << k << endl;
    }
}
int power(int x, int n)
{
    int i, p = 1;
    for (i = 1; i < n; i++) p *= x;
    return p;
}

