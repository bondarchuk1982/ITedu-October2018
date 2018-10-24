#include "sname.h"

SName::SName(){}

void SName::wFile()
{
    std::srand(unsigned(std::time(nullptr)));

    std::ofstream fs("Name.txt"); // Имя файла

    if (!fs.is_open()) { // если файл не открыт
        std::cout << "Файл не создан или не найден!\n"; // сообщить об этом
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
}
void SName::rFile()
{
    std::ifstream fs("Name.txt"); // Имя файла
    std::string str = "";

    if (!fs.is_open()) // если файл не открыт
        std::cout << "Файл не найден!\n"; // сообщить об этом
    else {
        std::cout << "Читаем файл!\n";

        std::ostringstream oss;
        oss << fs.rdbuf();
        str = oss.str();

        fs.close(); // закрываем файл
    }
    parseString(str);
}

void SName::parseString(std::string &str)
{
    std::string tmp = "";
    size_t index = 0;

    std::array<std::string, 5000> nArray;

    for (const auto& i : str){
        if (isalpha(i)) {
            tmp += i;
        }
        else {
            if (tmp != "") {
                nArray[index] =  tmp;
                tmp.clear();
                index++;
            }
        }
    }
    sortArray(nArray);
}

void SName::stlSortArray(std::array<std::string, 5000>& nArray)
{
    std::cout << "Сортируем методом std::sort!\n";
/* Сортировка с использованием алгоритмов STL для поиска и перестановки элементов в массиве
 * но без использования алгоритма сортировки std::sort
 */
/*    std::array<std::string, 0>::iterator begin = nArray.begin();
      while (begin != std::end(nArray)) { // цикл по элементам массива имён
        std::iter_swap(begin, std::min_element(begin, std::end(nArray)));

        begin++;
      }
*/
    std::sort(nArray.begin(), nArray.end());
}
void SName::sortArray(std::array<std::string, 5000>& nArray)
{
    std::cout << "Сортируем!\n";

// Сортировка без использования алгоритмов STL
    size_t index = 0;
    for (auto &i : nArray) { // цикл по элементам массива имён

        size_t min_index = index; // индекс текущего имени в массиве

        for (size_t j = index + 1; j < nArray.size(); j++) { // цикл по элементам массива имён
            if (i == "") break; // конец массива
            else if (nArray[j] < nArray[min_index]) min_index = j; // если нашлось имя меньшее (по алфавиту) чем текущее в
                                                                        // массиве присваиваем минимальному индексу его позицию
        }

        if (index != min_index) { // если текущий индекс не совпадает с минимальным именем
            std::string tmp = i; // из текущей позиции записываем имя во временную переменную
            i = nArray[min_index]; // минимальное имя записываем в текущую позицию
            nArray[min_index] = tmp; // в позицию минимального имени записываем значение из временной переменной
        }
        index++;
    }

    arrayInTerminal(nArray);
}

void SName::arrayInTerminal(std::array<std::string, 5000>& nArray)
{
    std::cout << "**********************************************************\n";
    for (const auto& i : nArray) { // цикл по элементам массива имён
        std::cout << i << '\n'; // выводим очередное имя из массива
    }
    std::cout << "**********************************************************\n";
    nameToNumber(nArray);
}

void SName::nameToNumber(std::array<std::string, 5000>& nArray)
{
    double rezult = 0; // общая цифра для всех имён

    for (const auto& i : nArray) { // цикл по элементам массива имён
        char buff[i.length()]; // создаём буфер символов для имени
        strcpy(buff, i.c_str()); // копируем символы имени в буфер

        for (size_t j = 0; j < i.length(); j++) // цикл по символам буфера
            rezult += static_cast<int>(buff[j]) - 96; // преобразуем символ в цифру
    }

    std::cout << "**********************************************************\n";
    printf("%.0f \n", rezult);
}
