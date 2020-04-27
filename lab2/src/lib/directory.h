#pragma once

#include <memory>
#include <unordered_map>
#include <string>

class Directory {
    private:
        std::string name;
        std::weak_ptr<Directory> parent;
        std::weak_ptr<Directory> self;
        std::unordered_map<std::string, std::shared_ptr<Directory>> children;
        Directory(std::string name): name{name}{}
    public:
        void ls(int indent);
        std::weak_ptr<Directory> get(std::string name);
        std::shared_ptr<Directory> addDirectory(std::string name);
        static std::shared_ptr<Directory> makeDir(std::string name, std::weak_ptr<Directory> parent);
        static Directory* heap(std::string name) {
            return new Directory(name);
        }
};