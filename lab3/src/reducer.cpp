#include "lib/reducer.h"

ReducerInputT::ReducerInputT(std::string key, int value, int acc) : key{key}, value{value}, acc{acc}{}
int ReducerInputT::getValue() const {return this->value;}
int ReducerInputT::getAcc() const {return this->acc;}
std::string ReducerInputT::getKey() const {return this->key;};