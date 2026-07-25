#include <gtest/gtest.h>
#include <Windows.h>
#include <iostream>


int main(int argc, char** argv)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}