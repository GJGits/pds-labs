#include "../lib/test.h"

Color::Modifier red(Color::FG_RED);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT); // restore color

void printResult(int tot_tests, int errors)
{
    std::cout << "--> Passed: " << (tot_tests - errors) << "/" << tot_tests;
    if (errors != 0)
    {
        std::cout << " [" << red << "KO!" << def << "]" << std::endl;
    }
    else
    {
        std::cout << " [" << blue << "OK!" << def << "]" << std::endl;
    }
}

void test_all()
{
}
