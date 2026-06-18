#include "Stroka.h"

using namespace std;

int Stroka::lengthOf(const char* value)
{
    if (value == nullptr) return 0;

    int length = 0;
    while (value[length] != '\0') ++length;
    return length;
}

void Stroka::copyText(char* destination, const char* source)
{
    if (source == nullptr) source = "";

    while (*source != '\0') {
        *destination = *source;
        ++destination;
        ++source;
    }

    *destination = '\0';
}

void Stroka::assignText(const char* value)
{
    int newLength = lengthOf(value);
    if (newLength + 1 > capacity) {
        delete[] str;
        capacity = newLength + 1;
        str = new char[capacity];
    }

    copyText(str, value);
}

Stroka::Stroka()
{
    capacity = 81;
    str = new char[capacity];
    str[0] = '\0';
}

Stroka::Stroka(int size)
{
    capacity = size > 0 ? size + 1 : 1;
    str = new char[capacity];
    str[0] = '\0';
}

Stroka::Stroka(const char* value)
{
    capacity = lengthOf(value) + 1;
    str = new char[capacity];
    copyText(str, value);
}

Stroka::Stroka(const Stroka& other)
{
    capacity = other.capacity;
    str = new char[capacity];
    copyText(str, other.str);
}

Stroka::~Stroka()
{
    delete[] str;
}

Stroka& Stroka::operator=(const Stroka& other)
{
    if (this != &other) assignText(other.str);
    return *this;
}

Stroka Stroka::operator+(const Stroka& other) const
{
    Stroka result(dlina() + other.dlina());
    copyText(result.str, str);

    char* tail = result.str + dlina();
    copyText(tail, other.str);

    return result;
}

bool Stroka::operator==(const Stroka& other) const
{
    int i = 0;
    while (str[i] != '\0' && other.str[i] != '\0') {
        if (str[i] != other.str[i]) return false;
        ++i;
    }

    return str[i] == other.str[i];
}

int Stroka::dlina() const
{
    return lengthOf(str);
}

void Stroka::vvod()
{
    char buffer[256];
    cin.getline(buffer, 256);
    assignText(buffer);
}

void Stroka::vyvod() const
{
    cout << str;
}

ostream& operator<<(ostream& out, const Stroka& value)
{
    out << value.str;
    return out;
}

istream& operator>>(istream& in, Stroka& value)
{
    char buffer[256];
    in.getline(buffer, 256);
    value.assignText(buffer);
    return in;
}
