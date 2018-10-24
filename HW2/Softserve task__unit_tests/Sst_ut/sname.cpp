#include "sname.h"

SName::SName(){}

bool SName::creatFile()
{
    std::srand(unsigned(std::time(nullptr)));

    std::ofstream fs("Name.txt"); // Имя файла

    if (!fs.is_open()) { // если файл не открыт
        std::cout << "Файл не создан или не найден!\n"; // сообщить об этом
        return false;
    }
    else {
        std::cout << "Записываем файл!\n";

        std::string str = "";

        for (int i = 0; i < 5000; ++i) {
            size_t lng = std::rand()% 8 + 2;

            for (size_t j = 0; j < lng; ++j) {
                char tmp = char(rand()%26+0x61);
                str.push_back(tmp);
            }

            str += " ";
        }
        fs << str;
    }
    fs.close();

    return true;
}
bool SName::rFile(std::string& str)
{
    str.clear();
    std::ifstream fs("Name.txt"); // Имя файла

    if (!fs.is_open()) { // если файл не открыт
        std::cout << "Файл не найден!\n"; // сообщить об этом
        return false;
    }
    else {
        std::cout << "Читаем файл!\n";

        std::ostringstream oss;
        oss << fs.rdbuf();
        str = oss.str();

        fs.close(); // закрываем файл
    }

    return true;
}

void SName::parseString(std::string& str, std::list<std::string>& strList)
{
    std::string tmp = "";

    for (const auto& i : str){
        if (isalpha(i)) {
            tmp += i;
        }
        else {
            if (tmp != "") {
                strList.push_back(tmp);
                tmp.clear();
            }
        }
    }

    if (tmp != "") {
        strList.push_back(tmp);
    }
}

void SName::arrayInTerminal(std::list<std::string> &strList)
{
    std::cout << "**********************************************************\n";
    for (const auto& i : strList) { // цикл по элементам массива имён
        std::cout << i << '\n'; // выводим очередное имя из массива
    }
    std::cout << "**********************************************************\n";
}

double SName::nameToNumber(std::list<std::string> &strList)
{
    double rezult = 0.0; // общая цифра для всех имён

    for (const auto& i : strList) { // цикл по элементам массива имён
        char buff[i.length()]; // создаём буфер символов для имени
        strcpy(buff, i.c_str()); // копируем символы имени в буфер

        for (size_t j = 0; j < i.length(); j++) // цикл по символам буфера
            rezult += static_cast<int>(buff[j]) - 96; // преобразуем символ в цифру
    }
    std::cout << "**********************************************************\n";
    printf("%.0f \n", rezult);
    return rezult;
}

