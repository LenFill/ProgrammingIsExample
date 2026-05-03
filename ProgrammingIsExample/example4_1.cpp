// ============================================================
//  ЛАБОРАТОРНАЯ РАБОТА 4

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int dlina1(const char* s) { int l = 0; while (s[l] != '\0') l++; return l; }
int dlina2(const char* s) { const char* p = s; while (*p != '\0') p++; return p - s; }
int dlina3(const char* s) { if (*s == '\0') return 0; return 1 + dlina3(s + 1); }
void kopir(char* dst, const char* src) { while (*src != '\0') { *dst = *src;dst++;src++; } *dst = '\0'; }
int sravn(const char* a, const char* b) { while (*a && *b) { if (*a != *b) return (unsigned char)*a - (unsigned char)*b; a++;b++; } return (unsigned char)*a - (unsigned char)*b; }
void konkat(char* dst, const char* src) { while (*dst != '\0') dst++; while (*src != '\0') { *dst = *src;dst++;src++; } *dst = '\0'; }

void demoStringArray() {
    const int ROWS = 4, COLS = 50;
    char sa[ROWS][COLS] = { "Первая строка","Вторая строка","Третья строка","Четвёртая строка" };
    cout << "\n--- Массив строк ---" << endl;
    for (int i = 0;i < ROWS;i++) cout << "sa[" << i << "] = \"" << sa[i] << "\", длина = " << dlina1(sa[i]) << endl;
}

int main() {
    char str1[] = "qwerty", str2[] = "1234567890";
    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 4 ===" << endl;
    cout << "\n--- Стандартные функции ---" << endl;
    cout << "strlen(str1) = " << strlen(str1) << endl;
    cout << "strlen(str2) = " << strlen(str2) << endl;
    char buf[100]; strcpy(buf, str1);
    cout << "strcpy: " << buf << endl;
    char buf2[100] = "Hello, "; strcat(buf2, "World!"); cout << "strcat: " << buf2 << endl;
    cout << "strcmp(str1,str2) = " << strcmp(str1, str2) << endl;

    cout << "\n--- Собственные функции ---" << endl;
    cout << "dlina1(\"" << str1 << "\") = " << dlina1(str1) << endl;
    cout << "dlina2(\"" << str1 << "\") = " << dlina2(str1) << endl;
    cout << "dlina3(\"" << str1 << "\") = " << dlina3(str1) << endl;
    char cb[100]; kopir(cb, str1); cout << "kopir: \"" << cb << "\"" << endl;
    cout << "sravn(\"abc\",\"abc\") = " << sravn("abc", "abc") << endl;
    cout << "sravn(\"abc\",\"abd\") = " << sravn("abc", "abd") << endl;
    char catB[100] = "Hello "; konkat(catB, "C++!"); cout << "konkat: \"" << catB << "\"" << endl;

    cout << "\n--- Динамическая память (malloc) ---" << endl;
    char* s3 = (char*)malloc(100); char* s4 = (char*)malloc(100);
    kopir(s3, "Строка в динамической памяти"); kopir(s4, s3);
    cout << "s3: " << s3 << endl << "s4: " << s4 << endl; free(s3); free(s4);

    cout << "\n--- Динамическая память (calloc) ---" << endl;
    int len = dlina1("Строка через calloc");
    char* s5 = (char*)calloc(len + 1, sizeof(char)); kopir(s5, "Строка через calloc");
    cout << "s5: " << s5 << endl; free(s5);
    cout << "Отличие: calloc обнуляет выделенную память, malloc — нет" << endl;

    demoStringArray();
    return 0;
}
