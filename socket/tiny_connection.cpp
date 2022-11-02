#include <string>
#include <memory>

#include "tiny_event.h"
#include "poll/tiny_poll.h"
#include "application/tiny_protocol.h"
#include "socket/tiny_connection.h"
#include "tiny_error.h"

using namespace std;

Connection::Connection(int recvBufSize, int sendBufSize)
:_recvBuf(recvBufSize), _sendBuf(sendBufSize)
{
    this->_globalConfig = GlobalConfig::getGlobalConfig();
    this->_manager = Manager::getManager();
}

Connection::~Connection()
{

}

void Connection::handler()
{
    int recvAns;
    int sendAns;

    switch (this->readyFlag)
    {
        case ONLY_READ:
            recvAns = this->connRecv();
            this->_protocol->readHandler(this->_recvBuf);
            break;
        case ONLY_WRITE:
            this->_protocol->writeHandler(this->_sendBuf);
            sendAns = this->connSend();
            break;
        case READ_WRITE:
            recvAns = this->connRecv();
            this->_protocol->readHandler(this->_recvBuf);
            this->_protocol->writeHandler(this->_sendBuf);
            sendAns = this->connSend();
            break;  
        default:
            break;
    }

    this->_poll->ctlAdd(this);
}

int Connection::connInit(shared_ptr<ObjectPoll> poll, const int &fd, const ConnType &connType, shared_ptr<Protocol> protocol)
{
    this->_poll = poll;
    this->fd = fd;
    this->_connType = connType;
    this->_protocol = protocol;

    this->_recvBuf.reset();
    this->_sendBuf.reset();

    return TINY_OK;
}

int Connection::connRecv()
{
    this->_recvBuf.checkEmpty();
    
    int bufLen = this->_recvBuf.surplusSize();

    int recvSize = 0;
    if(this->_connType == TcpConn)
    {
        recvSize = recv(this->fd, (void*)this->_recvBuf.getLast(), bufLen, 0);
    }
    else if(this->_connType == UdpConn)
    {
        struct sockaddr srcAddr;
        socklen_t addrLen;
        recvSize = recvfrom(this->fd, (void*)this->_recvBuf.getLast(), bufLen, 0, &srcAddr, &addrLen);
    }

    if(recvSize > 0)
        this->_recvBuf.moveLast(recvSize);

    return recvSize;
}

int Connection::connSend()
{
    int bufLen = this->_sendBuf.dataSize();
    if(bufLen <= 0)
        return bufLen;

    ssize_t sendSize = 0;
    if(this->_connType == TcpConn)
    {
        sendSize = send(this->fd, (void*)this->_sendBuf.getPos(), bufLen, 0);
    }
    else if(this->_connType == UdpConn)
    {
        struct sockaddr dstAddr;
        socklen_t addrLen;
        sendSize = sendto(this->fd, (void*)this->_sendBuf.getPos(), bufLen, 0, &dstAddr, &addrLen);
    }
    if(sendSize > 0)
    {
        this->_sendBuf.movePos(sendSize);
        this->_sendBuf.checkEmpty();
    }
    
    return sendSize;
}