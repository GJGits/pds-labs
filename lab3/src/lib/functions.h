#pragma once

#include <vector>
#include <fstream>
#include <map>
#include <regex>

#include "mapper.h"
#include "reducer.h"
#include "result.h"

template <typename MapperInputT, typename ResultT, typename ReducerInputT, typename M, typename R>
std::map<std::string, ResultT> mapReduceSerial(const std::string &inputf, M &mapfun, R &reducefun)
{
    std::map<std::string, ResultT> accs{};
    std::ifstream inFile;
    std::string line;
    inFile.open(inputf);
    if (inFile)
    {
        while (getline(inFile, line))
        {
            // key: string(ip, data, ...), value: num of occ in line (1 in questo caso)
            std::vector<ResultT> results = mapfun(line);
            int acc = accs.find(results[0].getKey()) == accs.end() ? 0 : accs[results[0].getKey()].getValue();
            ResultT rt = reducefun(ReducerInputT{results[0].getKey(), results[0].getValue(), acc});
            accs[rt.getKey()] = rt;
        }
    }
    return accs;
}