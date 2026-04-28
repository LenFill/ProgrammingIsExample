#include <iostream>
#include <iomanip>   
#include <cstdlib>  
#include <climits>   
#include <cmath>     
using namespace std;
#define N 5   

// Вывод матрицы на экран
void printMatrix(float m[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(8) << setprecision(2) << fixed << m[i][j];
        cout << endl;
    }
}
// Минимум и максимум всей матрицы
float minMatrix(float m[N][N])
{
    float mn = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (m[i][j] < mn) mn = m[i][j];
    return mn;
}

float maxMatrix(float m[N][N])
{
    float mx = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (m[i][j] > mx) mx = m[i][j];
    return mx;
}
// Среднеарифметическое значение всей матрицы
float avgMatrix(float m[N][N])
{
    float sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += m[i][j];
    return sum / (N * N);
}
// Элемент, наиболее близкий по значению к среднеарифметическому
float closestToAvg(float m[N][N])
{
    float avg = avgMatrix(m);
    float closest = m[0][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (fabs(m[i][j] - avg) < fabs(closest - avg))
                closest = m[i][j];
    return closest;
}
// Максимум / минимум нижнетреугольной части (i > j)
float maxLower(float m[N][N])
{
    float mx = m[1][0];   // первый элемент нижнего треугольника
    for (int i = 0; i < N; i++)
        for (int j = 0; j < i; j++)
            if (m[i][j] > mx) mx = m[i][j];
    return mx;
}

float minLower(float m[N][N])
{
    float mn = m[1][0];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < i; j++)
            if (m[i][j] < mn) mn = m[i][j];
    return mn;
}

// Максимум / минимум верхнетреугольной части (i < j)
float maxUpper(float m[N][N])
{
    float mx = m[0][1];   // первый элемент верхнего треугольника
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (m[i][j] > mx) mx = m[i][j];
    return mx;
}

float minUpper(float m[N][N])
{
    float mn = m[0][1];
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (m[i][j] < mn) mn = m[i][j];
    return mn;
}
// Среднее нижнего и верхнего треугольников
float avgLower(float m[N][N])
{
    float sum = 0; int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < i; j++) { sum += m[i][j]; cnt++; }
    return (cnt > 0) ? sum / cnt : 0;
}

float avgUpper(float m[N][N])
{
    float sum = 0; int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) { sum += m[i][j]; cnt++; }
    return (cnt > 0) ? sum / cnt : 0;
}
// Суммы нижнего и верхнего треугольников
float sumLower(float m[N][N])
{
    float s = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < i; j++)
            s += m[i][j];
    return s;
}

float sumUpper(float m[N][N])
{
    float s = 0;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            s += m[i][j];
    return s;
}
// Максимум и минимум главной диагонали (i == j)
float maxMainDiag(float m[N][N])
{
    float mx = m[0][0];
    for (int i = 1; i < N; i++)
        if (m[i][i] > mx) mx = m[i][i];
    return mx;
}

float minMainDiag(float m[N][N])
{
    float mn = m[0][0];
    for (int i = 1; i < N; i++)
        if (m[i][i] < mn) mn = m[i][i];
    return mn;
}
// Максимум и минимум побочной диагонали (i + j == N-1)
float maxSecDiag(float m[N][N])
{
    float mx = m[0][N - 1];
    for (int i = 0; i < N; i++)
        if (m[i][N - 1 - i] > mx) mx = m[i][N - 1 - i];
    return mx;
}

float minSecDiag(float m[N][N])
{
    float mn = m[0][N - 1];
    for (int i = 0; i < N; i++)
        if (m[i][N - 1 - i] < mn) mn = m[i][N - 1 - i];
    return mn;
}
// Суммы, минимумы, максимумы, средние по строкам
void rowStats(float m[N][N])
{
    cout << "\n--- Статистика по строкам ---" << endl;
    for (int i = 0; i < N; i++) {
        float sum = 0, mn = m[i][0], mx = m[i][0];
        for (int j = 0; j < N; j++) {
            sum += m[i][j];
            if (m[i][j] < mn) mn = m[i][j];
            if (m[i][j] > mx) mx = m[i][j];
        }
        cout << "Строка " << i << ": сумма=" << setw(8) << sum
            << "  мин=" << setw(7) << mn
            << "  макс=" << setw(7) << mx
            << "  среднее=" << setw(7) << setprecision(2) << sum / N << endl;
    }
}
// Суммы, минимумы, максимумы, средние по столбцам
void colStats(float m[N][N])
{
    cout << "\n--- Статистика по столбцам ---" << endl;
    for (int j = 0; j < N; j++) {
        float sum = 0, mn = m[0][j], mx = m[0][j];
        for (int i = 0; i < N; i++) {
            sum += m[i][j];
            if (m[i][j] < mn) mn = m[i][j];
            if (m[i][j] > mx) mx = m[i][j];
        }
        cout << "Столбец " << j << ": сумма=" << setw(8) << sum
            << "  мин=" << setw(7) << mn
            << "  макс=" << setw(7) << mx
            << "  среднее=" << setw(7) << setprecision(2) << sum / N << endl;
    }
}
int main() {
    system("chcp 1251>nul");
    float m[N][N];

    
    srand(42);  // фиксированное зерно — результат воспроизводим
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m[i][j] = (rand() % 201 - 100) / 10.0f;  // числа от -10.0 до 10.0

    cout << "\nИсходная матрица " << N << "x" << N << ":" << endl;
    printMatrix(m);

    // --- Вся матрица ---
    cout << "\n--- Вся матрица ---" << endl;
    cout << "Минимум:                " << minMatrix(m) << endl;
    cout << "Максимум:               " << maxMatrix(m) << endl;
    cout << "Среднеарифметическое:   " << avgMatrix(m) << endl;
    cout << "Ближайший к среднему:   " << closestToAvg(m) << endl;

    // --- Треугольники ---
    cout << "\n--- Нижнетреугольная часть (i > j) ---" << endl;
    cout << "Максимум:    " << maxLower(m) << endl;
    cout << "Минимум:     " << minLower(m) << endl;
    cout << "Среднее:     " << avgLower(m) << endl;
    cout << "Сумма:       " << sumLower(m) << endl;

    cout << "\n--- Верхнетреугольная часть (i < j) ---" << endl;
    cout << "Максимум:    " << maxUpper(m) << endl;
    cout << "Минимум:     " << minUpper(m) << endl;
    cout << "Среднее:     " << avgUpper(m) << endl;
    cout << "Сумма:       " << sumUpper(m) << endl;

    // --- Диагонали ---
    cout << "\n--- Главная диагональ (i == j) ---" << endl;
    cout << "Максимум: " << maxMainDiag(m) << endl;
    cout << "Минимум:  " << minMainDiag(m) << endl;

    cout << "\n--- Побочная диагональ (i + j == N-1) ---" << endl;
    cout << "Максимум: " << maxSecDiag(m) << endl;
    cout << "Минимум:  " << minSecDiag(m) << endl;

    // --- Строки и столбцы ---
    rowStats(m);
    colStats(m);
    system("pause>nul");
    return 0;
}
