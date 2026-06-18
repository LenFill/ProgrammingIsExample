// Лабораторная работа 8
// Классы потоков C++ и работа с файлами через объектные потоки.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../LR6/Stroka.h"

using namespace std;

void saveStroka(const string& fileName, const Stroka& value)
{
    ofstream out(fileName);
    out << value << endl;
}

Stroka loadStroka(const string& fileName)
{
    ifstream in(fileName);
    Stroka value;
    in >> value;
    return value;
}

void streamCipher(const string& inputFile, const string& outputFile, const string& key)
{
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    char ch;
    size_t i = 0;
    while (in.get(ch)) {
        out.put(static_cast<char>(ch ^ key[i % key.size()]));
        ++i;
    }
}

void demonstrateStreamState(const string& fileName)
{
    ifstream in(fileName);
    cout << "good(): " << in.good() << endl;
    cout << "eof():  " << in.eof() << endl;
    cout << "fail(): " << in.fail() << endl;
    cout << "bad():  " << in.bad() << endl;

    string line;
    while (getline(in, line)) {
        cout << "Прочитана строка: " << line << endl;
    }

    cout << "После чтения до конца файла eof(): " << in.eof() << endl;
}

int main()
{
    system("chcp 1251>nul");

    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 8 ===" << endl;

    Stroka first("Строка записана через operator<<");
    saveStroka("lr8_stroka.txt", first);

    Stroka second = loadStroka("lr8_stroka.txt");
    cout << "Прочитано из файла: " << second << endl;

    ofstream plain("lr8_plain.txt");
    plain << "Файл шифруется средствами потоков C++." << endl;
    plain.close();

    const string key = "stream-key";
    streamCipher("lr8_plain.txt", "lr8_encoded.txt", key);
    streamCipher("lr8_encoded.txt", "lr8_decoded.txt", key);
    cout << "Шифрование выполнено: lr8_encoded.txt, lr8_decoded.txt" << endl;

    cout << "\n--- Состояние потока ---" << endl;
    demonstrateStreamState("lr8_decoded.txt");

    return 0;
}
