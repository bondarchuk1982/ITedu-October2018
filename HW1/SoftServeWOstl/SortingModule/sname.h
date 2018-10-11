#ifndef SNAME_H
#define SNAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <array>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <iterator>

class SName
{
public:
    SName(); // Конструктор класса

    void wFile(); // Создание или запись сгенерированных имён в файл
    void rFile(); // Считывание данных из файла

private:
    void stlSortArray(std::array<std::string, 5000>&); // STL метод сортировки
    void sortArray(std::array<std::string, 5000>&); // собственный метод сортировки
    void parseString(std::string&);
    void arrayInTerminal(std::array<std::string, 5000>&); // вывод списка имён в терминал
    void nameToNumber(std::array<std::string, 5000>&); // Перевод имён в цифры и получение общего числа для всех имён
};

#endif // SNAME_H
