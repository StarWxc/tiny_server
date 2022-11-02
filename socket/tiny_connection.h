#pragma once

#include <string>
#include <memory>

#include "tiny_event.h"
#include "poll/tiny_poll.h"
#include "application/tiny_protocol.h"
#include "tool/tiny_buf.h"
#include "tiny_manager.h"

using namespace std;

enum ConnType
{
    TcpConn,
    UdpConn,
};

class Connection : public Event
{
    public:
        Connection(int recvBufSize, int sendBufSize);
        virtual ~Connection();
        virtual void handler();

        int connInit(shared_ptr<ObjectPoll> poll, const int &fd, const ConnType &connType, shared_ptr<Protocol> protocol);

        int connRecv();
        int connSend();

    public:
        struct sockaddr localSockAddr;
        socklen_t       localSockLen;

        struct sockaddr sockAddr;
        socklen_t       sockLen;

    private:
        ConnType _connType;

        shared_ptr<Protocol> _protocol;
        shared_ptr<ObjectPoll> _poll;

        TinyBuf _recvBuf;
        TinyBuf _sendBuf;

        shared_ptr<GlobalConfig> _globalConfig;
        shared_ptr<Manager> _manager;
        
};