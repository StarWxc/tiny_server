#pragma once

#include <iostream>
#include <mutex>
#include <memory>
#include <string>
#include <cstring>

using namespace std;

#define TinyBuf_OK      0
#define TinyBuf_ERR     -1

class TinyBuf
{
    public:
        TinyBuf(const int &size);
        ~TinyBuf();
        
        void reset();
        int resize();

        void checkEmpty();

        int memSize(){return this->_memSize;};
        int dataSize(){return this->_last - this->_pos;};

        void* getStart(){return this->_start};
        void* getEnd(){return this->_end};

        void* getPos(){return this->pos};
        void* getLast(){return this->last};

        int movePos(const int &size);
        int moveLast(const int &size);

        int surplusSize();

        int getDataFromBuf(char dstBuf[], int bufSize);
        int pushDataToBuf(char srcBuf[], int bufSize);
    private:
        int     _memSize;

        u_char *_start;
        u_char *_end;

        u_char *_pos;
        u_char *_last;
};


TinyBuf::TinyBuf(const int &size)
:_memSize(size)
{
    this->_start = (u_char*)malloc(this->_memSize);
    this->_end = this->_start + _memSize;

    this->_pos = this->_start;
    this->_last = this->_start;
}

TinyBuf::~TinyBuf()
{
    free((void*)this->_start);
}

void TinyBuf::reset()
{
    this->_pos = this->_start;
    this->_last = this->_start;
}

int TinyBuf::resize(const int &size)
{
    free((void*)this->_start);

    this->_memSize = size;
    this->_start = (u_char*)malloc(this->_memSize);
    this->_end = this->_start + this->_memSize;
    this->_pos = this->_start;
    this->_last = this->_start;
}

void TinyBuf::checkEmpty()
{
    if((this->pos != this->_start) and (this->_pos == this->_last))
    {
        this->reset();
    }
}

int TinyBuf::movePos(const int &size)
{
    this->_pos + size;
    if((this->_pos - this->_end) > 0)
    {
        this->_pos - size;
        return TinyBuf_ERR;
    }
    return TinyBuf_OK
}

int TinyBuf::moveLast(const int &size)
{
    this->_last + size;
    if((this->_last - this->_end) > 0)
    {
        this->_last - size;
        return TinyBuf_ERR;
    }
    return TinyBuf_OK
}

int TinyBuf::surplusSize()
{
    return this->_end - this->_last;
}

int TinyBuf::getDataToBuf(char dstBuf[], int bufSize)
{
    int dataSize = this->dataSize();

    bufSize = dataSize < bufSize ? dataSize:bufSize;

    memcpy((void*)dstBuf, (void*)this->_pos, bufSize);
    this->movePos(bufSize);

    return bufSize;
}

int TinyBuf::pushDataToBuf(char srcBuf[], int bufSize)
{
    int surplus = this->surplusSize();

    int dataSize = surplus < bufSize ? surplus:bufSize;

    memcpy((void*)this->_last, (void*)srcBuf, dataSize);
    this->moveLast(dataSize);
    
    return dataSize;
}
