#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tiny_config.h"
#include "poll/tiny_poll.h"

using namespace std;

class Event
{
    public:
        Event()
        :enableFlag(READ_WRITE), readyFlag(0)
        {};
        virtual ~Event();
        
        virtual void handler(){};

    public:
        //
        int fd;
        //使能
        int enableFlag;
        //触发
        int readyFlag;
};