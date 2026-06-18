// Лабораторная работа 5
// Организация ввода-вывода и работа с текстовыми файлами.

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string readFile(const string& fileName)
{
    ifstream in(fileName, ios::binary);
    if (!in) return "";

    ostringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

void printFile(const string& fileName)
{
    ifstream in(fileName);
    if (!in) {
        cout << "Файл " << fileName << " не открыт" << endl;
        return;
    }

    char ch;
    while (in.get(ch)) cout << ch;
}

void countBlankAndVisible(const string& text, int& blankCount, int& visibleCount)
{
    blankCount = 0;
    visibleCount = 0;

    for (unsigned char ch : text) {
        if (isgraph(ch)) visibleCount++;
        else blankCount++;
    }
}

vector<size_t> findSubstring(const string& text, const string& pattern)
{
    vector<size_t> positions;
    if (pattern.empty()) return positions;

    size_t pos = text.find(pattern);
    while (pos != string::npos) {
        positions.push_back(pos);
        pos = text.find(pattern, pos + 1);
    }

    return positions;
}

void writeSearchResult(const string& outputFile, const vector<size_t>& positions)
{
    ofstream out(outputFile);
    out << "Найдено вхождений: " << positions.size() << endl;
    for (size_t i = 0; i < positions.size(); ++i) {
        out << "Позиция " << i + 1 << ": " << positions[i] << endl;
    }
}

string movePageNumbers(const string& text)
{
    string result;
    size_t start = 0;

    while (start < text.size()) {
        size_t end = text.find('\f', start);
        string page = text.substr(start, end == string::npos ? string::npos : end - start);

        size_t firstEnd = page.find('\n');
        string firstLine = firstEnd == string::npos ? page : page.substr(0, firstEnd);
        string body = firstEnd == string::npos ? "" : page.substr(firstEnd + 1);

        string number;
        for (char ch : firstLine) {
            if (isdigit(static_cast<unsigned char>(ch))) number += ch;
        }

        result += body;
        if (!result.empty() && result.back() != '\n') result += '\n';
        if (!number.empty()) result += number + "\n";

        if (end == string::npos) break;
        result += '\f';
        start = end + 1;
    }

    return result;
}

void xorCipherFile(const string& inputFile, const string& outputFile, const string& key)
{
    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    if (!in || !out || key.empty()) {
        cout << "Ошибка открытия файла или пустой ключ" << endl;
        return;
    }

    char ch;
    size_t i = 0;
    while (in.get(ch)) {
        out.put(static_cast<char>(ch ^ key[i % key.size()]));
        ++i;
    }
}

void createSampleFile(const string& fileName)
{
    ofstream out(fileName);
    out << "- 34 -\n";
    out << "Первая страница содержит строку для поиска.\n";
    out << "Строка может повторяться несколько раз.\n";
    out << '\f';
    out << "- 35 -\n";
    out << "Вторая страница тоже содержит строку.\n";
}

int main(int argc, char* argv[])
{
    system("chcp 1251>nul");

    const string inputFile = argc > 1 ? argv[1] : "lr5_input.txt";
    const string key = argc > 2 ? argv[2] : "key";

    ifstream check(inputFile);
    if (!check) createSampleFile(inputFile);

    cout << "=== ЛАБОРАТОРНАЯ РАБОТА 5 ===" << endl;
    cout << "\n--- Содержимое файла ---" << endl;
    printFile(inputFile);

    string text = readFile(inputFile);
    int blankCount = 0, visibleCount = 0;
    countBlankAndVisible(text, blankCount, visibleCount);

    cout << "\n\nПустых символов: " << blankCount << endl;
    cout << "Непустых символов: " << visibleCount << endl;

    vector<size_t> positions = findSubstring(text, "строка");
    writeSearchResult("lr5_search_result.txt", positions);
    cout << "Результат поиска записан в lr5_search_result.txt" << endl;

    ofstream moved("lr5_pages_result.txt");
    moved << movePageNumbers(text);
    cout << "Номера страниц перенесены в lr5_pages_result.txt" << endl;

    xorCipherFile(inputFile, "lr5_encoded.txt", key);
    xorCipherFile("lr5_encoded.txt", "lr5_decoded.txt", key);
    cout << "Шифрование выполнено: lr5_encoded.txt, lr5_decoded.txt" << endl;

    return 0;
}
