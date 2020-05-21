#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <regex>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <unistd.h>

#include "mapper.h"
#include "reducer.h"
#include "result.h"

std::string parse(const std::string &target, const std::regex &rgx);
std::shared_ptr<char[]> prepareDeserialization(std::vector<char> serialized);

template <class T>
void write_to_pipe(int fd, const T &obj)
{
    std::vector<char> ser = obj.serialize();
    write(fd, ser.data(), ser.size());
}

template <class T>
T read_from_pipe(int fd)
{
    T obj;
    std::vector<char> buf{};
    char r = ' ';
    while (r != '\n')
    {
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

    int mapPipe[2];
    int reducePipe[2];
    pid_t child_map, child_reduce;
    std::map<std::string, ResultT> accs{};

    // 1. PIPE CREATION
    if (pipe(mapPipe) < 0 || pipe(reducePipe) < 0)
    {
        accs["PIPE_FAILED"] = ResultT{"PIPE_FAILED", 0};
        return accs;
    }

    // 2. FOR PROCESSES: 1 CONTROLLER(PARENT), 1 MAPPER, 1 REDUCER
    child_map = fork();

    if (child_map == 0)
    {
        /* Child map code */

        struct timeval tval;
        fd_set cset;
        FD_ZERO(&cset);
        FD_SET(mapPipe[0], &cset);
        tval.tv_sec = 1; // in locale un'attesa di 1sec ok
        tval.tv_usec = 0;
        int map_tout = 1;
        while ((map_tout = select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == 1)
        {
            // 1. leggo il map input inviatomi dal parent
            MapperInputT m = read_from_pipe<MapperInputT>(mapPipe[0]);
            // 2. eseguo la map
            ResultT rm = mapfun(m);
            // 3. scrivo il result sulla pipe (valutare come ser/deser array)
            write_to_pipe<ResultT>(mapPipe[1], rm);
        }

        // 4. timeout ed exit processo
        exit(0);
    }
    else
    {
        child_reduce = fork();

        if (child_reduce == 0)
        {
            /* Child reduce code */

            struct timeval tval;
            fd_set cset;
            FD_ZERO(&cset);
            FD_SET(mapPipe[0], &cset);
            tval.tv_sec = 1; // in locale un'attesa di 1sec ok
            tval.tv_usec = 0;
            int red_tout = 1;
            while ((red_tout = select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == 1)
            {
                // 1. leggo reducer input
                ReducerInputT ri = read_from_pipe<ReducerInputT>(reducePipe[0]);
                // 2. eseguo reduce
                ResultT res_reduce = reducefun(ri);
                // 3. scrivo il result sulla pipe
                write_to_pipe<ResultT>(reducePipe[1], res_reduce);
            }

            // 4. timeout ed exit processo
            exit(0);
        }
        else
        {
            /* Parent Code */
            std::ifstream inFile;
            std::string line;
            inFile.open(inputf);
            if (inFile)
            {
                while (getline(inFile, line))
                {
                    // key: string(ip, data, ...), value: num of occ in line (1 in questo caso)
                    write_to_pipe<MapperInputT>(mapPipe[1], MapperInputT(line));
                    ResultT rm = read_from_pipe<ResultT>(mapPipe[0]);
                    int acc = accs.find(rm.getKey()) == accs.end() ? 0 : accs[rm.getKey()].getValue();
                    write_to_pipe<ReducerInputT>(reducePipe[1], ReducerInputT{rm.getKey(), rm.getValue(), acc});
                    ResultT rt = read_from_pipe<ResultT>(reducePipe[0]);
                    accs[rt.getKey()] = rt;
                }
            }
            return accs;
        }
    }

    return accs;
}