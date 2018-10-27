#include "chararraysorts.h"

char *CharArraySorts::operator()(char *ch)
{
    if (ch[0] == '\0' || ch[1] == '\0') return ch;

    size_t i = 0;

    while (ch[i] != 0) {
        size_t j = i + 1;
        size_t minIndex = i;

        while (ch[j] != 0) {
            if (ch[j] < ch[minIndex]) {
                minIndex = j;
            }

            j++;
        }
        if (minIndex != i) {
            std::swap(ch[i], ch[minIndex]);
        }
        i++;
    }
    return ch;
}
