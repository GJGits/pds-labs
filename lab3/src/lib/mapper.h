#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <string>

class SimpleMapperInputT
{
private:
    std::string input;

public:
    SimpleMapperInputT(std::string input) : input{std::move(input)} {}
    std::string getInput() const { return input; }
    std::vector<char> serialize() const
    {
        boost::property_tree::ptree pt;
        pt.put("input", input);
        std::ostringstream buf;
        boost::property_tree::write_json(buf, pt, false);
        //necessario perche chiamata buf.str().begin() non funziona
        std::string result = buf.str();
        return std::vector<char>(result.begin(), result.end()); 
    }
    void deserialize(std::shared_ptr<char[]> json)
    {
        boost::property_tree::ptree pt;
        std::string jsonstr {(char *)(json.get())};
        std::istringstream is{jsonstr};
        boost::property_tree::read_json(is, pt);
        this->input = pt.get<std::string>("input");
       // std::cout << "deserialize: " << this->input;
    }
};
