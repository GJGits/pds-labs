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
    std::shared_ptr<char[]> result{new char[size + 1]};
    for (size_t i = 0; i < size; i++)
        result.get()[i] = serialized[i];
    result.get()[size] = '\0';
    return result;
}

void write_to_pipe(int fd, std::vector<char> buff)
{
    write(fd, reinterpret_cast<char*>(&buff[0]), buff.size());
}

std::vector<char> read_from_pipe(int fd)
{   
    std::vector<char> buf{};
    char r = ' ';
    while (r != '\n' && r != '\0' )
    {
        read(fd, &r, 1);
        buf.push_back(r);
    }
    return buf;
}
