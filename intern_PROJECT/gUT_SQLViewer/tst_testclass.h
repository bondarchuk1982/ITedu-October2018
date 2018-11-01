#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <../SQLViewer/database.h>

using namespace testing;

class TestClass : public ::testing::Test {
protected:
    DataBase db;
};

TEST_F(TestClass, TestConnect)
{
    EXPECT_FALSE(db.openDataBase(""));
    EXPECT_FALSE(db.connectToDataBase(""));

    EXPECT_TRUE(db.openDataBase("myDataBase.db"));
    EXPECT_TRUE(db.connectToDataBase("myDataBase.db"));
}
TEST_F(TestClass, TestOnAddUpdateDeleteDBNotConnected)
{
    EXPECT_FALSE(db.sqlQuery(""));
    EXPECT_FALSE(db.sqlQuery("CREATE TABLE Contacts (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "Date NOT NULL, "
                              "Time NOT NULL, "
                              "Name VARCHAR(255) NOT NULL, "
                              "Phone VARCHAR(10) NOT NULL);"));

    EXPECT_FALSE(db.sqlQuery("SELECT * FROM Con;"));
    EXPECT_FALSE(db.sqlQuery("SELECT * FROM Contacts;"));

    db.oneContact.name = "First";
    db.oneContact.phone = "111111111";
    EXPECT_FALSE(db.onAdd());

    db.oneContact.name = "Second";
    db.oneContact.phone = "222222222";
    EXPECT_FALSE(db.onAdd());

    db.oneContact.id = 1;
    db.oneContact.name = "third";
    db.oneContact.phone = "333333333";
    EXPECT_FALSE(db.onUpdate());

    db.oneContact.id = 2;
    EXPECT_FALSE(db.onDelete());
}
TEST_F(TestClass, TestOnAddUpdateDeleteDBIsConnected)
{
    db.connectToDataBase("myDataBase.db");

    EXPECT_FALSE(db.sqlQuery(""));
    EXPECT_TRUE(db.sqlQuery("CREATE TABLE Contacts (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "Date NOT NULL, "
                              "Time NOT NULL, "
                              "Name VARCHAR(255) NOT NULL, "
                              "Phone VARCHAR(10) NOT NULL);"));

    EXPECT_FALSE(db.sqlQuery("SELECT * FROM Con;"));
    EXPECT_TRUE(db.sqlQuery("SELECT * FROM Contacts;"));


    db.oneContact.name = "First";
    db.oneContact.phone = "111111111";
    EXPECT_TRUE(db.onAdd());

    db.oneContact.name = "Second";
    db.oneContact.phone = "222222222";
    EXPECT_TRUE(db.onAdd());

    db.oneContact.name = "";
    db.oneContact.phone = "111111111";
    EXPECT_FALSE(db.onAdd());

    db.oneContact.name = "First";
    db.oneContact.phone = "";
    EXPECT_FALSE(db.onAdd());

    db.oneContact.name = "";
    db.oneContact.phone = "";
    EXPECT_FALSE(db.onAdd());

    db.oneContact.id = 1;
    db.oneContact.name = "third";
    db.oneContact.phone = "333333333";
    EXPECT_TRUE(db.onUpdate());

    db.oneContact.name = "";
    db.oneContact.phone = "333333333";
    EXPECT_FALSE(db.onUpdate());

    db.oneContact.name = "third";
    db.oneContact.phone = "";
    EXPECT_FALSE(db.onUpdate());

    db.oneContact.name = "";
    db.oneContact.phone = "";
    EXPECT_FALSE(db.onUpdate());

    db.oneContact.id = 1;
    db.oneContact.name = "third";
    db.oneContact.phone = "333333333";
    EXPECT_TRUE(db.onDelete());

    db.oneContact.name = "";
    db.oneContact.phone = "333333333";
    EXPECT_FALSE(db.onDelete());

    db.oneContact.name = "third";
    db.oneContact.phone = "";
    EXPECT_FALSE(db.onDelete());

    db.oneContact.name = "";
    db.oneContact.phone = "";
    EXPECT_FALSE(db.onDelete());
}
