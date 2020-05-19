#include <string>

class ResultT
{
private:
    std::string key;
    int value;

public:
    ResultT(std::string key, int value);
    std::string getKey();
    int getValue();
};