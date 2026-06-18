// Лабораторная работа 9
// Шаблоны функций и классов. Сортировка состава с использованием тупика.

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

template <class T>
void sortArray(T array[], int size)
{
    for (int i = 0; i < size - 1; ++i) {
        for (int j = size - 1; j > i; --j) {
            if (array[j - 1] > array[j]) {
                T temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
        }
    }
}

template <class T>
T getmax(T first, T second)
{
    return first > second ? first : second;
}

template <class T>
T getmax(T array[], int size)
{
    T result = array[0];
    for (int i = 1; i < size; ++i) {
        if (array[i] > result) result = array[i];
    }
    return result;
}

const char* getmax(const char* first, const char* second)
{
    return strcmp(first, second) > 0 ? first : second;
}

class Money {
private:
    long rubles;
    int kopecks;

public:
    Money(long r = 0, int k = 0)
    {
        rubles = r + k / 100;
        kopecks = k % 100;
    }

    bool operator>(const Money& other) const
    {
        return rubles > other.rubles ||
            (rubles == other.rubles && kopecks > other.kopecks);
    }

    friend ostream& operator<<(ostream& out, const Money& value)
    {
        out << value.rubles << " руб. " << value.kopecks << " коп.";
        return out;
    }
};

template <class T>
class TStack {
private:
    T* items;
    int size;
    int count;

public:
    explicit TStack(int maxSize = 10)
    {
        size = maxSize;
        count = 0;
        items = new T[size];
    }

    ~TStack()
    {
        delete[] items;
    }

    bool empty() const
    {
        return count == 0;
    }

    bool full() const
    {
        return count == size;
    }

    void push(T value)
    {
        if (!full()) items[count++] = value;
    }

    T pop()
    {
        return items[--count];
    }

    T top() const
    {
        return items[count - 1];
    }
};

template <int size>
class MemBlock {
private:
    char* data;

public:
    MemBlock()
    {
        data = new char[size];
        data[0] = '\0';
    }

    ~MemBlock()
    {
        delete[] data;
    }

    operator char* ()
    {
        return data;
    }
};

void printIntArray(const int array[], int size, const string& title)
{
    cout << title << ": ";
    for (int i = 0; i < size; ++i) cout << array[i] << ' ';
    cout << endl;
}

void sortRailwayTrain(const int input[], int size, int output[])
{
    TStack<int> deadEnd(size);
    int expected = size;
    int outIndex = 0;

    for (int i = size - 1; i >= 0; --i) {
        deadEnd.push(input[i]);

        while (!deadEnd.empty() && deadEnd.top() == expected) {
            output[outIndex++] = deadEnd.pop();
            --expected;
        }
    }
}

int main()
{
    system("chcp 1251>nul");

    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 9 ===" << endl;

    int numbers[] = { 10, 20, 30, 11, 25, 32, 0 };
    const int numbersSize = sizeof(numbers) / sizeof(numbers[0]);
    sortArray(numbers, numbersSize);
    printIntArray(numbers, numbersSize, "Отсортированный массив int");

    Money money[] = { Money(19, 10), Money(99, 99), Money(99, 95), Money(19, 95) };
    const int moneySize = sizeof(money) / sizeof(money[0]);
    sortArray(money, moneySize);
    cout << "Отсортированный массив Money:" << endl;
    for (int i = 0; i < moneySize; ++i) cout << "  " << money[i] << endl;

    cout << "max int = " << getmax(3, 5) << endl;
    cout << "max str = " << getmax("строка1", "строка2") << endl;
    cout << "max array = " << getmax(numbers, numbersSize) << endl;

    TStack<int> stack(5);
    stack.push(33);
    stack.push(45);
    cout << "Значения в стеке: " << stack.pop() << ", " << stack.pop() << endl;

    MemBlock<512> block;
    strcpy(block, "Строка в шаблонном блоке памяти");
    cout << static_cast<char*>(block) << endl;

    int train[] = { 1, 5, 3, 4, 2 };
    int sortedTrain[5] = {};
    sortRailwayTrain(train, 5, sortedTrain);
    printIntArray(train, 5, "Вход состава");
    printIntArray(sortedTrain, 5, "Выход состава");

    return 0;
}
