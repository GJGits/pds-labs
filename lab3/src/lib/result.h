#pragma once

#include <string>

template <typename T>
class SimpleResult
{
    std::string key;
    T value;

public:
    SimpleResult() = default;
    SimpleResult(std::string key) : key(std::move(key)) {}
    SimpleResult(std::string key, T value) : key(std::move(key)), value(std::move(value)) {}
    std::string getKey() const { return key; }
    T getValue() const { return value; }
    std::vector<char> serialize() const
    {
        boost::property_tree::ptree pt;
        pt.put("key", key);
        pt.put("value", this->value);
        std::ostringstream buf;
        boost::property_tree::write_json(buf, pt, false);
        //necessario perche chiamata buf.str().begin() non funziona
        std::string result = buf.str();
        std::cout << "result serialization: " << result << "\n";
        return std::vector<char>(result.begin(), result.end()); 
    }
    void deserialize(std::shared_ptr<char[]> json)
    {
        boost::property_tree::ptree pt;
        std::string jsonstr {(char *)(json.get())};
        std::istringstream is{jsonstr};
        boost::property_tree::read_json(is, pt);
        this->key = pt.get<std::string>("key");
        this->value = pt.get<int>("value");
        std::cout << "result deserialization: (" << this->key << ", " << this->value << ")\n";
    }
};