#include "tst_testclass.h"

#include <gtest/gtest.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);

    if (RUN_ALL_TESTS())
        return a.exec();

    return 0;
}
