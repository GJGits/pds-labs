#pragma once

#include <string>

template <typename V, typename A>
class SimpleReducerInput
{
    std::string key;
    V value;
    A accumulator;

public:
    SimpleReducerInput() {} // per deserializzazione
    SimpleReducerInput(std::string key, V value, A accumulator) : key(std::move(key)), value(std::move(value)), accumulator(std::move(accumulator)) {}
    std::string getKey() const { return key; }
    V getValue() const { return value; }
    A getAccumulator() const { return accumulator; }
    std::vector<char> serialize() const
    {   
        //std::cout << "serialize reducer\n";
        boost::property_tree::ptree pt;
        pt.put("key", key);
        pt.put("value", value);
        pt.put("accumulator", accumulator);
        std::ostringstream buf;
        boost::property_tree::write_json(buf, pt, false);
        //necessario perche chiamata buf.str().begin() non funziona
        std::string result = buf.str();
        return std::vector<char>(result.begin(), result.end()); 
    }
    void deserialize(std::shared_ptr<char[]> json)
    {   
        //std::cout << "deserialize reducer\n";
        boost::property_tree::ptree pt;
        std::string jsonstr {(char *)(json.get())};
        std::istringstream is{jsonstr};
        boost::property_tree::read_json(is, pt);
        key = pt.get<std::string>("key");
        value = pt.get<int>("value");
        accumulator = pt.get<int>("accumulator");
        //std::cout << "deserialize redinput: (" << key << ", " << value << ", " << accumulator << ")\n";
    }
};