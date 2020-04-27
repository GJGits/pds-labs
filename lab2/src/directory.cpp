#include "lib/directory.h"

void Directory::ls(int indent)
{
}

std::weak_ptr<Directory> Directory::get(std::string name)
{   
    Directory *d = heap(std::string("NOT IMPLEMENTED YET")); 
    return std::make_shared<Directory>(*d); 
}

std::shared_ptr<Directory> Directory::addDirectory(std::string name)
{   
    std::shared_ptr<Directory> dir_res = makeDir(name, this->self); // todo: capire cosa farne
    this->children.insert(std::make_pair(name, makeDir(name, this->self)));
    return dir_res;
}

std::shared_ptr<Directory> Directory::makeDir(std::string name, std::weak_ptr<Directory> parent)
{   
    Directory *d = new Directory(name);
    std::shared_ptr<Directory> dir = std::make_shared<Directory>(*d);
    dir->self = dir;
    dir->parent = parent;
    return dir;
}