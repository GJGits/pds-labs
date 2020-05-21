#include "lib/functions.h"

std::string parse(const std::string &target, const std::regex &rgx)
{
    std::smatch matches;
    std::string token{""};
    token = std::regex_search(target, matches, rgx) ? matches[0] : std::string("NOT_FOUND");
    return token;
}

std::shared_ptr<char[]> prepareDeserialization(std::vector<char> serialized)
{
    size_t size = serialized.size();
    char *serchar = new char[size + 1];
    for (size_t i = 0; i < size; i++)
        serchar[i] = serialized[i];
    serchar[size] = '\0';
    return std::shared_ptr<char[]>(serchar);
}
