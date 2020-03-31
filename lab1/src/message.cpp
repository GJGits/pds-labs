#include "lib/message.h"
#include <utility>

int Message::counter = 0;

Message::Message(): id(-1), size(0){
    this->data = nkMessage(0);
}

Message::Message(int size): id(counter++), size(size) {
    this->data = nkMessage(size);
}

Message::Message(const Message &source): id(source.id), size(source.size) {
    this->data = new char[size + 1];
    memcpy(this->data, source.data, source.size + 1); 
}

Message::Message(Message &&source): 
    id(std::exchange(source.id, 0)), size(std::exchange(source.size, 0)) {
   this->data = source.data;
   source.data = nullptr; 
}

Message::~Message() {
    delete[] this->data;
    this->data = nullptr;
}

long Message::getId() {
    return this->id;
}

int Message::getSize() {
    return this->size;
}

const char* Message::getData() {
    return this->data;
}

std::ostream& operator << (std::ostream& os, const Message& m) {
    return os << m.data;
}

char* Message::nkMessage(int n) {
    srand(5);
    std::string vowels = "aeiou";
    std::string consonants = "bcdfghlmnpqrstvz";
    char *m = new char[n+1];
    for(int i = 0; i < n; i++) {
        m[i] = i % 2 ? vowels[rand() % vowels.size()] : consonants[rand() % consonants.size()];
    }
    m[n] = 0 ;
    return m;
}