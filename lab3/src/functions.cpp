#include "lib/functions.h"

std::vector<ResultT> map(const MapperInputT &input)
{
    return std::vector<ResultT>{};
}

ResultT reduce(const ReducerInputT &input)
{
    return ResultT{"", 0};
}

std::map<std::string, int> mapReduce(std::string input, std::function<std::vector<ResultT>(const MapperInputT &input)> mapfun, std::function<ResultT(const ReducerInputT &input)> redfun)
{
    std::map<std::string, int> accs{};
    std::ifstream inFile;
    std::string line;
    inFile.open(input);
    if (inFile)
    {
        while (getline(inFile, line))
        {
            // key: string(ip, data, ...), value: num of occ in line (1 in questo caso)
            std::vector<ResultT> results = mapfun(line);
            int acc = accs.find(results[0].getKey()) == accs.end() ? 0 : accs[results[0].getKey()];
            ResultT rt = redfun(ReducerInputT{results[0].getKey(), results[0].getValue(), acc});
            accs[rt.getKey()] = rt.getValue();
        }
    }
    return accs;
}