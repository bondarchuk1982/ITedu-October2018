#include "stringpolindrome.h"

bool StringPolindrome::operator()(const std::string& str)
{
    if (str.empty()) return false;
    if (str.length() == 1){
        if(isalpha(str[0])) {
            return true;
        }
        else {
            return false;
        };
    }

    size_t iBegin = 0;
    size_t iEnd = str.length() - 1;

    while (iBegin != iEnd) {
        if (!isalpha(str[iBegin])) {
            iBegin++;
            continue;
        }
        else if (!isalpha(str[iEnd])) {
            iEnd--;
            continue;
        }
        else if (str[iBegin] != str[iEnd]) return false;

        iBegin++;
        iEnd--;
    }
    return true;
}
