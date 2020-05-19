#include "lib/duration.h"

Color::Modifier red(Color::FG_RED);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT); // restore color

DurationLogger::DurationLogger(const char *name) {
    this->name = new char[strlen(name) + 1];
    memcpy(this->name, name, strlen(name) + 1);
    std::cout << "  >>>>> starting [" << name << "]" << std::endl;
    this->t0 = clock();
}

DurationLogger::~DurationLogger() {
    std::cout << "  <<<<< ending [" << (this->name) << "]: [" << blue << ((float)clock() - (float)t0 ) / CLOCKS_PER_SEC << def << "]sec" << std::endl;
    delete[] this->name;
    this->name = nullptr;
}