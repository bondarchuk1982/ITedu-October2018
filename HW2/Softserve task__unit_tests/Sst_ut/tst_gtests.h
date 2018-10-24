#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <sname.h>

using namespace testing;

class TestsClass : public ::testing::Test
{
protected:
    SName sName;

    std::string str;
    std::list<std::string> strList;
};

TEST_F(TestsClass, WriteFileTest)
{
    EXPECT_TRUE(sName.creatFile());
}

TEST_F(TestsClass, ReadFileTest)
{
    EXPECT_TRUE(sName.rFile(str));
}

TEST_F(TestsClass, strToListTest0)
{
    str = "adda ksjhfk,  2klslkf5 345 ..., asdhfo ., .,0{)asdkf";
    std::string tmp = str;
    sName.parseString(str, strList);
    EXPECT_EQ(str, tmp);
}

TEST_F(TestsClass, strToListTest1)
{
    str = "adda ksjhfk, askdfhj 2klslkf5 adsfh 345 ..., asdhfo ., .,0{) asdkf";
    std::string tmp = str;
    sName.parseString(str, strList);
    EXPECT_EQ(strList.size(), 7);
    EXPECT_EQ(str, tmp);
}

TEST_F(TestsClass, strToListTest2)
{
    sName.parseString(str, strList);
    EXPECT_EQ(strList.size(), 0);
}

TEST_F(TestsClass, strToListTest3)
{
    sName.rFile(str);
    sName.parseString(str, strList);
    EXPECT_EQ(strList.size(), 5000);
}

TEST_F(TestsClass, sortTest0)
{
    strList.sort();
    std::list<std::string> expected;

    EXPECT_EQ(strList, expected);
}

TEST_F(TestsClass, sortTest1)
{
    strList = {"cc", "aa", "bb"};
    strList.sort();
    std::list<std::string> expected = {"aa", "bb", "cc"};

    EXPECT_EQ(strList, expected);
}


TEST_F(TestsClass, nameToNumberTest0)
{
    EXPECT_EQ(sName.nameToNumber(strList), 0);
}

TEST_F(TestsClass, nameToNumberTest1)
{
    strList = {"adda", "adda"};
    EXPECT_EQ(sName.nameToNumber(strList), 20);
}
