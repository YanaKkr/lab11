#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void CreateBIN(char* fname) // створення файлу символів з введених рядків
{
ofstream fout(fname, ios::binary); // відкрили файл для запису
char ch; // відповідь користувача – чи продовжувати введення
string s; // введений користувачем рядок
do
{
cin.get(); // очищуємо буфер клавіатури – щоб не було символу
cin.sync(); // "кінець рядка", який залишився після вводу числа
cout << "enter line: "; getline(cin, s); // ввели рядок
for (unsigned i=0; i<s.length(); i++) // скануємо введений рядок
fout.write((char*)&s[i], sizeof(s[i])); // записали символ у файл
cout << "continue? (y/n): "; cin >> ch;
}
while (ch == 'y' || ch == 'Y');
cout << endl;
}
void PrintBIN(char* fname) // виведення файлу на екран
{
ifstream fin(fname, ios::binary); // відкрили файл для зчитування
char c; // прочитаний символ
while ( fin.read((char*)&c, sizeof(c) )) // поки можна прочитати символ
{
cout << c << endl; // виводимо його на екран
}
cout << endl;
}

void ProcessBIN(const char* fname, const char* gname) {
    std::ifstream readFile(fname, std::ios::binary);
    ofstream g(gname, ios::binary);
    if (!readFile.is_open()) {
        std::cerr << "Unable to open the file for reading.\n";
        return;
    }

    int maxOdd = INT_MIN;
    int minEven = INT_MAX;
    int currentNumber;

    while (readFile.read(reinterpret_cast<char*>(&currentNumber), sizeof(int))) {
        if (currentNumber % 2 != 0 && currentNumber > maxOdd) {
            maxOdd = currentNumber;
        } else if (currentNumber % 2 == 0 && currentNumber < minEven) {
            minEven = currentNumber;
        }
    }

    readFile.close(); // Close the input file stream

    std::ofstream fout(gname, std::ios::binary | std::ios::app); // Open in append mode
    if (!fout.is_open()) {
        std::cerr << "Unable to open the file for writing.\n";
        return;
    }

    fout.write(reinterpret_cast<const char*>(&maxOdd), sizeof(int));
    fout.write(reinterpret_cast<const char*>(&minEven), sizeof(int));
    g.write((char*)&maxOdd, sizeof(char));
    g.write((char*)&minEven, sizeof(char));
    fout.close(); // Close the output file stream
}

int main()
{
// binary files
char fname[100]; // ім'я першого файлу
cout << "enter file name 1: "; cin >> fname;
CreateBIN(fname); // ввели рядки файлу з клавіатури
PrintBIN(fname); // вивели вміст першого файлу на екран
char gname[100]; // ім'я другого файлу
cout << "enter file name 2: "; cin >> gname;
ProcessBIN(fname, gname);
PrintBIN(gname); // вивели вміст файлу на екран
return 0;
}

