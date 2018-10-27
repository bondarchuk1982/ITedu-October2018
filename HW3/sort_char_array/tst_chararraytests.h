#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <chararraysorts.h>

extern char** my_argv;

using namespace testing;

class TestsClass : public ::testing::Test
{
protected:
    CharArraySorts chArraySorts;
};
TEST_F(TestsClass, Test1)
{
    char *input = new char[6]{'b', 'd', 'a', 'c', 'e'};
    char *expected = new char[6]{'a', 'b', 'c', 'd', 'e'};
    char *actual = chArraySorts(input);

    EXPECT_STREQ(actual, expected);
}
TEST_F(TestsClass, Test2)
{
    char *input = new char[6]{'\0'};
    char *expected = new char[6]{'\0'};
    char *actual = chArraySorts(input);

    EXPECT_STREQ(actual, expected);
}
TEST_F(TestsClass, Test3)
{
    char *input = new char[6]{'b', 'd', 'a', '1', '2'};
    char *expected = new char[6]{'1', '2', 'a', 'b', 'd'};
    char *actual = chArraySorts(input);

    EXPECT_STREQ(actual, expected);
}
TEST_F(TestsClass, Test4)
{
    char *input = new char[6]{'a', 'a', 'a', 'a', 'a'};
    char *expected = new char[6]{'a', 'a', 'a', 'a', 'a'};
    char *actual = chArraySorts(input);

    EXPECT_STREQ(actual, expected);
}
