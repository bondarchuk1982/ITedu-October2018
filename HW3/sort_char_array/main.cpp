#include "tst_chararraytests.h"

#include <gtest/gtest.h>

char** my_argv;

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    my_argv = argv;
    return RUN_ALL_TESTS();
}
