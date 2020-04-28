#pragma once

#include "base.h"

class File : public Base
{

private:
public:
    const uintmax_t getSize();
    const virtual void ls(int indent);
    const virtual int mType();
};