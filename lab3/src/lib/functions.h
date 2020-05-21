#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <regex>
#include <stdio.h> 

#include "mapper.h"
#include "reducer.h"
#include "result.h"

std::string parse(const std::string &target, const std::regex &rgx);
std::shared_ptr<char[]> prepareDeserialization(std::vector<char> serialized);

template <class T>
void write_to_pipe(int fd, const T &obj) {
    std::vector<char> ser = obj.serialize();
    write(fd, ser.data(), ser.size());
}

template <class T>
T read_from_pipe(int fd) {
    T obj;
    std::vector<char> buf {};
    char r = ' ';
    while (r != '\n') {
        read(fd, &r, 1);
        buf.push_back(r);
    }
    obj.deserialize(prepareDeserialization(buf));
    return obj;
}

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
            std::vector<ResultT> results = mapfun(MapperInputT(line));
            int acc = accs.find(results[0].getKey()) == accs.end() ? 0 : accs[results[0].getKey()].getValue();
            ResultT rt = reducefun(ReducerInputT{results[0].getKey(), results[0].getValue(), acc});
            accs[rt.getKey()] = rt;
        }
    }
    return accs;
}

template <typename MapperInputT, typename ResultT, typename ReducerInputT, typename M, typename R>
std::map<std::string, ResultT> mapReduceConcurrent(const std::string &inputf, M &mapfun, R &reducefun)
{   
    int p[2];
    std::map<std::string, ResultT> accs{};
    if(pipe(p) < 0) {
        accs["PIPE_FAILED"] = ResultT{"PIPE_FAILED", 0};
        return accs;
    }
    
    std::ifstream inFile;
    std::string line;
    inFile.open(inputf);
    if (inFile)
    {
        while (getline(inFile, line))
        {
            // key: string(ip, data, ...), value: num of occ in line (1 in questo caso)
            write_to_pipe<MapperInputT>(p[1], MapperInputT(line));
            MapperInputT m = read_from_pipe<MapperInputT>(p[0]);
            std::cout << "read from pipe: " << m.getInput() << "\n";
            std::vector<ResultT> results = mapfun(MapperInputT(line));
            int acc = accs.find(results[0].getKey()) == accs.end() ? 0 : accs[results[0].getKey()].getValue();
            ResultT rt = reducefun(ReducerInputT{results[0].getKey(), results[0].getValue(), acc});
            accs[rt.getKey()] = rt;
        }
    }
    return accs;
}