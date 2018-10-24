#include <iostream>
#include "sname.h"

using namespace std;

int main()
{
    SName sName; // Создаём объект класса

    if (sName.creatFile()) { // Создаём или записываем в файл рандомные имена(5000)
        std::string str; // Строка для имён из файла

        if (sName.rFile(str) && str != "") { // Читаем содержимое файла
            std::list<std::string> strList; // Контейнер для имён

            sName.parseString(str, strList); // Разбираем содержимое строки
            sName.arrayInTerminal(strList); // Выводим в терминал имена из контейнера

            strList.sort(); // Сортируем контейнер встроенной функцией сортировки
            sName.arrayInTerminal(strList); // Выводим в терминал имена из контейнера

            std::cout << "**********************************************************\n";
            printf("%.0f \n", sName.nameToNumber(strList)); // Выщитываем число для всех имён
        }
    }

    return 0;
}
