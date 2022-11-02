#pragma once

#include <functional>

#include "module/tiny_module.h"
#include "socket/tiny_connection.h"
#include "tool/tiny_buf.h"

using namespace std;

class Protocol;

typedef function<Protocol*()> protocolInitFunc; 

class Protocol
{
    public:
        Protocol(shared_ptr<Module> module)
        :_module(module);
        {};
        virtual ~Protocol();
        
        void setConnet(const Connection *&conn){this->_connect = conn;}

        virtual void readHandler(TinyBuf &recvBuf){};
        virtual void writeHandler(TinyBuf &sendBuf){};

    public:

    protected:
        shared_ptr<Module> _module;
        Connection *_connect;

};
