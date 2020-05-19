#include <string>

class ReducerInputT
{
private:
    std::string key;
    int value, acc;

public:
    ReducerInputT(std::string key, int value, int acc);
    int getValue() const;
    int getAcc() const;
    std::string getKey() const;
};