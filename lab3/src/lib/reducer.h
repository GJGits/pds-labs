#pragma once

#include <string>

template <typename V, typename A>
class SimpleReducerInput
{
    std::string key;
    V value;
    A accumulator;

public:
    SimpleReducerInput(std::string key, V value, A accumulator) : key(std::move(key)), value(std::move(value)), accumulator(std::move(accumulator)) {}
    std::string getKey() const { return key; }
    V getValue() const { return value; }
    A getAccumulator() const { return accumulator; }
};