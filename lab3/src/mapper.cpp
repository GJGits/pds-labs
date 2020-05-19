#include "lib/mapper.h"

MapperInputT::MapperInputT(std::string input) : input{input} {}
std::string MapperInputT::getInput() const {return this->input;}