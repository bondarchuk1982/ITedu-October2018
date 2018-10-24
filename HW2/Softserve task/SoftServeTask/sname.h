#ifndef SNAME_H
#define SNAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <list>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <functional>
class SName
{
public:
    SName(); // Конструктор класса

    bool creatFile(); // Создание или запись сгенерированных имён в файл
    bool rFile(std::string&); // Считывание данных из файла

    void parseString(std::string&, std::list<std::string>&);
    void arrayInTerminal(std::list<std::string>&); // вывод списка имён в терминал
    double nameToNumber(std::list<std::string>&); // Перевод имён в цифры и получение общего числа для всех имён

};

#endif // SNAME_H
