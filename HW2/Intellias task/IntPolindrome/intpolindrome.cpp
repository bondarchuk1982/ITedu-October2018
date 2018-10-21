#include "intpolindrome.h"

IntPolindrome::IntPolindrome()
{
    std::srand(unsigned(std::time(nullptr)));

    int num = (std::rand() % 899 + 100)*(std::rand() % 899 + 100);
    std::cout << "num: "<< num << std::endl;
    std::cout << "************************" << std::endl;

    std::string s = "";
    while(num > 0) {
        s = std::to_string(num);

        if(std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin())) {
            std::cout << "Max polindrom: "<< num << std::endl;
            std::cout << "************************" << std::endl;

            break;
        }
        num--;
    }
}
