#ifndef MESSAGE_STORE
#define MESSAGE_STORE

#include<optional>
#include<tuple>
#include "message.h"

class MessageStore {
    private:
        Message *messages;
        int dim; // dimensione corrente array
        int n; // incremento memoria
    public:
        MessageStore(int n);
        ~MessageStore();
        void add(Message &m);
        std::optional<Message> get(long id);
        bool remove(long id);
        std::tuple<int, int> stats();
        void compact();
        int getN();
        int getDim();
};

#endif