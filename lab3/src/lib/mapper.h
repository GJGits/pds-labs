#pragma once

#include <string>

class SimpleMapperInputT
{
private:
    std::string input;

public:
    SimpleMapperInputT(std::string input): input{std::move(input)}{}
    std::string getInput() const {return input;}
};
