// Лабораторная работа 6
// Описание класса строки.

#pragma once

#include <iostream>

class Stroka {
private:
    char* str;
    int capacity;

    static int lengthOf(const char* value);
    static void copyText(char* destination, const char* source);
    void assignText(const char* value);

public:
    Stroka();
    explicit Stroka(int size);
    Stroka(const char* value);
    Stroka(const Stroka& other);
    ~Stroka();

    Stroka& operator=(const Stroka& other);
    Stroka operator+(const Stroka& other) const;
    bool operator==(const Stroka& other) const;

    int dlina() const;
    void vvod();
    void vyvod() const;

    friend std::ostream& operator<<(std::ostream& out, const Stroka& value);
    friend std::istream& operator>>(std::istream& in, Stroka& value);
};
