#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <iostream>
#include <string.h>

class Message {
    
    private:
        long id;
        char *data;
        int size;
        char *nkMessage(int n);

    public:
        static int counter;
        Message();
        Message(int n);
        Message(const Message &source);
        Message(Message &&source);
        ~Message();
        long getId();
        int getSize();
        const char* getData();
        friend std::ostream& operator<<(std::ostream& os, const Message& m);
    
};
#endif