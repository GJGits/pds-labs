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
    std::function<std::vector<ResultT>(const MapperInputT &input)> mapIp = [](const MapperInputT &input) {
        std::vector<std::string> tokens;
        std::stringstream check1(input.getInput());
        std::string intermediate;
        while (getline(check1, intermediate, ' '))
        {
            tokens.push_back(intermediate);
        }
        ResultT t{tokens[0], 1};
        return std::vector<ResultT>{t};
    };
    std::function<ResultT(const ReducerInputT &input)> reduce = [](const ReducerInputT &input) { return ResultT{input.getKey(), (input.getValue() + input.getAcc())}; };
    std::map<std::string, int> results;
    {
        DurationLogger mip{"mapreduce_ip"};
        results = mapReduce("../logs/localhost_access_log.2020.txt", mapIp, reduce);
    }

    //print first 20 rows
    /*
    int count = 0;
    for (std::pair<std::string, int> element : results)
    {
        std::cout << "(" << element.first << ", " << element.second << ")\n";
        if (++count > 100)
            break;
    }
    */
}

void mapReduceOra()
{

    std::cout << "##### TEST MAP-REDUCE ORA #####\n";
    std::function<std::vector<ResultT>(const MapperInputT &input)> mapOra = [](const MapperInputT &input) {
        std::vector<std::string> tokens;
        std::stringstream check1(input.getInput());
        std::string intermediate;
        while (getline(check1, intermediate, ':'))
        {
            tokens.push_back(intermediate);
        }
        ResultT t{tokens[1], 1};
        return std::vector<ResultT>{t};
    };
    std::function<ResultT(const ReducerInputT &input)> reduce = [](const ReducerInputT &input) { return ResultT{input.getKey(), (input.getValue() + input.getAcc())}; };
    std::map<std::string, int> results;
    {
        DurationLogger mip{"mapreduce_ora"};
        results = mapReduce("../logs/localhost_access_log.2020.txt", mapOra, reduce);
    }

    //print first 20 rows
    /*
    int count = 0;
    for (std::pair<std::string, int> element : results)
    {
        std::cout << "(" << element.first << ", " << element.second << ")\n";
        if (++count > 100)
            break;
    }
    */
}

void mapReduceURL()
{
    std::cout << "##### TEST MAP-REDUCE URL #####\n";
    std::function<std::vector<ResultT>(const MapperInputT &input)> mapURL = [](const MapperInputT &input) {
        std::vector<std::string> tokens;
        std::stringstream check1(input.getInput());
        std::string intermediate;
        while (getline(check1, intermediate, '/'))
        {
            tokens.push_back(intermediate);
        }
        if (tokens.size() < 3)
        {
            return std::vector<ResultT>{{"unvalid", 1}};
        }
        if (tokens.size() <= 5)
        {
            return std::vector<ResultT>{{"/", 1}};
        }
        std::string re{"/"};
        for (size_t i = 3; i < tokens.size() - 1; i++)
        {
            if (i != (tokens.size() - 1))
                re += tokens[i] + "/";
            else
            {
                std::vector<std::string> tokens2;
                std::stringstream check2(tokens[tokens.size() - 1]);
                std::string intermediate2;
                while (getline(check1, intermediate2, ' '))
                {
                    tokens2.push_back(intermediate2);
                }
                re += tokens2[0];
            }
        }
        return std::vector<ResultT>{{re, 1}};
    };
    std::function<ResultT(const ReducerInputT &input)> reduce = [](const ReducerInputT &input) { return ResultT{input.getKey(), (input.getValue() + input.getAcc())}; };
    std::map<std::string, int> results;
    {
        DurationLogger mip{"mapreduce_url"};
        results = mapReduce("../logs/localhost_access_log.2020.txt", mapURL, reduce);
    }

    //print first 20 rows
    int count = 0;
    for (std::pair<std::string, int> element : results)
    {
        std::cout << "(" << element.first << ", " << element.second << ")\n";
        if (++count > 100)
            break;
    }
}

void test_all()
{
    std::cout << "\n\n";
    mapReduceIp();
    std::cout << "\n";
    mapReduceOra();
    std::cout << "\n";
    mapReduceURL();
    std::cout << "\n\n";
}
