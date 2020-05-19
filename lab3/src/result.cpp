#include "lib/result.h"

ResultT::ResultT(std::string key, int value) : key{key}, value{value} {}
std::string ResultT::getKey() {return this->key;}
int ResultT::getValue() {return this->value;}