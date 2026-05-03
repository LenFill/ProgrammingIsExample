//  Лабораторная работа 3
#include <iostream>
using namespace std;

void printArray(int arr[], int n, const char* label)
{
    cout << label << ": ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

void copyArray(int src[], int dst[], int n)
{
    for (int i = 0; i < n; i++) dst[i] = src[i];
}
// ЗАДАНИЕ 1: Сортировка методом «мини-макса»
void sortMiniMax(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        int imin = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[imin]) imin = j;
        int tmp = arr[i]; arr[i] = arr[imin]; arr[imin] = tmp;
    }
}
// ЗАДАНИЕ 2а: Сортировка методом «пузырька»
void sortBubble(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp;
            }
}
// ЗАДАНИЕ 2б: Быстрая сортировка (метод Хоара)
void sortQuick(int arr[], int left, int right)
{
    if (left >= right) return;
    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            i++; j--;
        }
    }
    sortQuick(arr, left, j);
    sortQuick(arr, i, right);
}
// ЗАДАНИЕ 3: Чётные значения — по возрастанию, нечётные — по убыванию
void sortEvenAscOddDesc(int arr[], int n)
{
    int even[100], eCnt = 0, odd[100], oCnt = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) even[eCnt++] = arr[i];
        else                  odd[oCnt++] = arr[i];
    }
    sortBubble(even, eCnt);   // чётные — по возрастанию
    sortBubble(odd, oCnt);    // нечётные — по убыванию
    for (int i = 0; i < oCnt / 2; i++) {
        int tmp = odd[i]; odd[i] = odd[oCnt - 1 - i]; odd[oCnt - 1 - i] = tmp;
    }
    int ei = 0, oi = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) arr[i] = even[ei++];
        else                  arr[i] = odd[oi++];
    }
}
// ЗАДАНИЕ 4: Сортировка по возрастанию на интервале [n1, n2]
void sortRangeAsc(int arr[], int n1, int n2)
{
    sortBubble(arr + n1, n2 - n1 + 1);
}
// ЗАДАНИЕ 5: Сортировка по убыванию на интервале [n1, n2]
void sortRangeDesc(int arr[], int n1, int n2)
{
    int len = n2 - n1 + 1;
    sortBubble(arr + n1, len);
    for (int i = 0; i < len / 2; i++) {
        int tmp = arr[n1 + i]; arr[n1 + i] = arr[n2 - i]; arr[n2 - i] = tmp;
    }
}
int main()
{
    system("chcp 1251>nul");
    int original[] = { 2, 5, -8, 1, -4, 6, 3, -5, -9, 13, 0, 4, 9 };
    int n = sizeof(original) / sizeof(int);
    int arr[20];

    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 3 ===" << endl;
    printArray(original, n, "Исходный массив     ");

    copyArray(original, arr, n);
    sortMiniMax(arr, n);
    printArray(arr, n, "Мини-макс (возр.)   ");

    copyArray(original, arr, n);
    sortBubble(arr, n);
    printArray(arr, n, "Пузырёк   (возр.)   ");

    copyArray(original, arr, n);
    sortQuick(arr, 0, n - 1);
    printArray(arr, n, "Быстрая   (возр.)   ");

    copyArray(original, arr, n);
    sortEvenAscOddDesc(arr, n);
    printArray(arr, n, "Чётные (Возврастание) Нечётные (Убывание) ");

    copyArray(original, arr, n);
    sortRangeAsc(arr, 2, 7);
    printArray(arr, n, "Возр. на [2..7]     ");

    copyArray(original, arr, n);
    sortRangeDesc(arr, 2, 7);
    printArray(arr, n, "Убыв. на [2..7]     ");
    system("pause>nul");
    return 0;
}