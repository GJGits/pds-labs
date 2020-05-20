#pragma once

#include <string>

template <typename T>
class SimpleResult
{
    std::string key;
    T value;

public:
    SimpleResult() = default;
    SimpleResult(std::string key) : key(std::move(key)) {}
    SimpleResult(std::string key, T value) : key(std::move(key)), value(std::move(value)) {}
    std::string getKey() const { return key; }
    T getValue() const { return value; }
};