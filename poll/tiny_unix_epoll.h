#pragma once

#include <memory>
#include "poll/tiny_poll.h"
#include <sys/epoll.h>
#include <vector>

using namespace std;

class UnixEpoll
{
    public:
        UnixEpoll(int size = 0);
        ~UnixEpoll();

        virtual Socket* wait();
        virtual int ctlAdd(Socket* socket);
        virtual int ctlMod(Socket* socket);
        virtual int ctlDel(Socket* socket);
    
    private:
        int _epollFd;
        vector<struct epoll_event> _eventVector;
};


