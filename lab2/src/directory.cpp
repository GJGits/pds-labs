#include "lib/directory.h"

const std::string Base::getName()
{
    return this->name;
}


/*
std::shared_ptr<Directory> Directory::getRoot()
{
    if (Directory::root.use_count() == 0)
        Directory::root = std::shared_ptr<Directory>(heap("/"));
    return root;
}

std::shared_ptr<Directory> Directory::addDirectory(std::string name)
{
    std::shared_ptr<Directory> child = makeDir(name, this->self);
    this->children.insert(std::make_pair(name, child));
    return child;
}

std::shared_ptr<Directory> Directory::makeDir(std::string name, std::weak_ptr<Directory> parent)
{
    Directory *d = new Directory(name);
    std::shared_ptr<Directory> dir(d);
    dir->self = dir;
    dir->parent = parent;
    return dir;
}

*/