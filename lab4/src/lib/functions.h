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
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include "mapper.h"
#include "reducer.h"
#include "result.h"

std::string parse(const std::string &target, const std::regex &rgx);
std::shared_ptr<char[]> prepareDeserialization(std::vector<char> serialized);
void write_to_pipe(int fd, std::vector<char> buff);
std::vector<char> read_from_pipe(int fd);

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
    int resultPipe[2];
    pid_t child_map, child_reduce;
    std::map<std::string, ResultT> accs{};

    // 1. PIPE CREATION
    if (pipe(mapPipe) < 0 || pipe(reducePipe) < 0 || pipe(resultPipe) < 0)
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
        tval.tv_sec = 60; // in locale un'attesa di 1sec ok
        tval.tv_usec = 0;
        int map_tout = 1;
        MapperInputT m;
        while ((map_tout = select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == 1)
        {
            // 1. leggo il map input inviatomi dal parent
            std::vector<char> mb = read_from_pipe(mapPipe[0]);
            m.deserialize(prepareDeserialization(mb));
            if (m.getInput().compare("NONE") == 0)
                break;
            // 2. eseguo la map
            ResultT rm = mapfun(m);
            // 3. scrivo il result sulla pipe (valutare come ser/deser array)
            write_to_pipe(resultPipe[1], rm.serialize());
        }

        // 4. timeout ed exit processo
        //exit(0);
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
            FD_SET(reducePipe[0], &cset);
            tval.tv_sec = 60; // in locale un'attesa di 1sec ok
            tval.tv_usec = 0;
            int red_tout = 1;
            ReducerInputT ri;
            while ((red_tout = select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == 1)
            {
                // 1. leggo reducer input
                std::vector<char> rib = read_from_pipe(reducePipe[0]);
                ri.deserialize(prepareDeserialization(rib));
                if (ri.getKey().compare("NONE") == 0)
                    break;
                // 2. eseguo reduce
                ResultT res_reduce = reducefun(ri);
                // 3. scrivo il result sulla pipe
                write_to_pipe(resultPipe[1], res_reduce.serialize());
            }

            // 4. timeout ed exit processo
            //exit(0);
        }
        else
        {
            /* Parent Code */
            std::ifstream inFile;
            std::string line;
            inFile.open(inputf);
            if (inFile)
            {
                std::regex rgx("^[\\w+?=!.\":\\s-\\[\\/\\]]+$");
                std::smatch matches;
                while (getline(inFile, line) && !line.empty())
                {
                    // evita di avere errori per JSON su righe con cofica diversa
                    if (std::regex_search(line, matches, rgx))
                    {
                        write_to_pipe(mapPipe[1], MapperInputT(line).serialize());
                        ResultT rm;
                        std::vector<char> rmb = read_from_pipe(resultPipe[0]);
                        rm.deserialize(prepareDeserialization(rmb));
                        int acc = accs.find(rm.getKey()) == accs.end() ? 0 : accs[rm.getKey()].getValue();
                        write_to_pipe(reducePipe[1], ReducerInputT{rm.getKey(), rm.getValue(), acc}.serialize());
                        ResultT rt;
                        std::vector<char> rtb = read_from_pipe(resultPipe[0]);
                        rt.deserialize(prepareDeserialization(rtb));
                        accs[rt.getKey()] = rt;
                    }
                }
            }
            write_to_pipe(mapPipe[1], MapperInputT("NONE").serialize());             // signal end map
            write_to_pipe(reducePipe[1], ReducerInputT{"NONE", -1, -1}.serialize()); // signal end reduce
            inFile.close();
            close(mapPipe[0]);
            close(mapPipe[1]);
            close(reducePipe[0]);
            close(reducePipe[1]);
            close(resultPipe[0]);
            close(resultPipe[1]);
            return accs;
        }
    }

    close(mapPipe[0]);
    close(mapPipe[1]);
    close(reducePipe[0]);
    close(reducePipe[1]);
    close(resultPipe[0]);
    close(resultPipe[1]);
    return accs;
}