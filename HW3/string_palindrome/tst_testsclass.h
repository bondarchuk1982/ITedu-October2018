#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "stringpolindrome.h"

using namespace testing;

class TestsClass : public ::testing::Test
{
protected:
    StringPolindrome strPolindrome;
};

TEST_F(TestsClass, Test1)
{
    EXPECT_TRUE(strPolindrome("ab  ababa baba"));
}
TEST_F(TestsClass, Test2)
{
    EXPECT_FALSE(strPolindrome("aba a b babs bs"));
}
TEST_F(TestsClass, Test3)
{
    EXPECT_TRUE(strPolindrome("ab  a1.1ba2,ba ba1ba"));
}
TEST_F(TestsClass, Test4)
{
    EXPECT_FALSE(strPolindrome(""));
}
TEST_F(TestsClass, Test5)
{
    EXPECT_FALSE(strPolindrome(" "));
}
TEST_F(TestsClass, Test6)
{
    EXPECT_TRUE(strPolindrome("a"));
}
