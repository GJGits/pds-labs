#include "../lib/test.h"

Color::Modifier red1(Color::FG_RED);
Color::Modifier blue1(Color::FG_BLUE);
Color::Modifier def1(Color::FG_DEFAULT); // restore color

void printResult(int tot_tests, int errors)
{
    std::cout << "--> Passed: " << (tot_tests - errors) << "/" << tot_tests;
    if (errors != 0)
    {
        std::cout << " [" << red1 << "KO!" << def1 << "]" << std::endl;
    }
    else
    {
        std::cout << " [" << blue1 << "OK!" << def1 << "]" << std::endl;
    }
}

void mapReduceIp()
{
    std::cout << "##### TEST MAP-REDUCE IP #####\n";
    auto mapIp = [](const SimpleMapperInputT &input) {
        std::vector<std::string> tokens;
        std::stringstream check1(input.getInput());
        std::string intermediate;
        while (getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }
        SimpleResult<int> t{tokens[0], 1};
        return std::vector<SimpleResult<int>>{t};
    };
    auto reduce = [](const SimpleReducerInput<int, int> &input) { return SimpleResult<int>{input.getKey(), (input.getValue() + input.getAccumulator())}; };
    std::map<std::string, SimpleResult<int>> results;
    {
        DurationLogger mip{"mapreduce_ip"};
        results = mapReduceSerial<SimpleMapperInputT, SimpleResult<int>, SimpleReducerInput<int, int>>("../logs/localhost_access_log.2020.txt", mapIp, reduce);
    }

    //print first 100 rows
    /*
    int count = 0;
    for (std::pair<std::string, SimpleResult<int>> element : results)
    {
        std::cout << "(" << element.first << ", " << element.second.getValue() << ")\n";
        if (++count > 100)
            break;
    }
    */
}
void test_all()
{
    std::cout << "\n\n";
    mapReduceIp();
    std::cout << "\n";
    std::cout << "\n\n";
}
