#pragma once

#include <memory>

class Base
{
private:
    std::string name;

public:
    Base(std::string name) : name{name} {}
    const std::string getName();
    const virtual int mType() = 0;
    const virtual void ls(int indent) = 0;
};
