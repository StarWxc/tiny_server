#pragma once

#include "tiny_protocol.h"
#include <iostream>

class TinyTest : public Protocol
{
    TinyTest(){};
    ~TinyTest(){};

    virtual void readHandler(TinyBuf &recvBuf)
    {
        char buf[1024] = {};
        recvBuf.getDataFromBuf(buf, 1024);

        cout<< buf <<endl;
    };
    virtual void writeHandler(TinyBuf &sendBuf){};
}