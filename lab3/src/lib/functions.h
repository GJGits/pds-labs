#include <functional>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>

#include "mapper.h"
#include "reducer.h"
#include "result.h"

template <class MapperInputT, class ResultT>
std::vector<ResultT> map(const MapperInputT &input);

template <class ReducerInputT, class ResultT>
ResultT reduce(const ReducerInputT &input);

//template <class MapperInputT, class ReducerInputT, class ResultT>
std::map<std::string, int> mapReduce(std::string input, std::function<std::vector<ResultT>(const MapperInputT &input)> mapfun, std::function<ResultT(const ReducerInputT &input)> redfun);
