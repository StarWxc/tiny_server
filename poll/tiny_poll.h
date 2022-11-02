#pragma once

#include "socket/tiny_socket.h"

using namespace std;

enum EventFlag
{
    ONLY_READ = 0,
    ONLY_WRITE,
    READ_WRITE,
    ONLY_TIME,
};

class ObjectPoll
{
    public:
        ObjectPoll();
        ~ObjectPoll();

        virtual Socket* wait() = 0;
        virtual int ctlAdd(Socket* socket) = 0;
        virtual int ctlMod(Socket* socket) = 0;
        virtual int ctlDel(Socket* socket) = 0;
    private:
        
};

ObjectPoll::ObjectPoll()
{
}

ObjectPoll::~ObjectPoll()
{
}
