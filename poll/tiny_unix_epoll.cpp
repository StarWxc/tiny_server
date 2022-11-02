#include "poll/tiny_unix_epoll.h"
#include "tiny_error.h"
#include "socket/tiny_event.h"

using namespace std;

#define EVENT_VECTOR_SIZE 100

#define EPOLL_WAIT_TIMEOUT -1


UnixEpoll::UnixEpoll(int size)
:_eventVector(EVENT_VECTOR_SIZE)
{
    this->_epollFd = epoll_create1(0);
}

UnixEpoll::~UnixEpoll()
{
}


Event* UnixEpoll::wait()
{
    Event* socket = nullptr;

    int eventNums = epoll_wait(this->_epollFd, &*_eventVector.begin(), static_cast<int>(_eventVector.size()), EPOLL_WAIT_TIMEOUT);

    for (int i = 0; i < eventNums; i++)
    {
        socket = static_cast<Event*>(_eventVector[i].data.ptr);

        if(_eventVector[i].events & EPOLLIN)
            socket->readyRead = 1;

        if(_eventVector[i].events & EPOLLOUT)
            socket->readyWrite = 1;

        socket->handler();
    }
    
    return POLL_OK;
}

int UnixEpoll::ctlAdd(Event* socket)
{
    struct epoll_event epollEvt;

    switch(socket->enableFlag)
    {
        case ONLY_READ:
            epollEvt.events = epollEvt.events | EPOLLIN;
            break;

        case ONLY_WRITE:
            epollEvt.events = epollEvt.events | EPOLLOUT;
            break;

        case READ_WRITE:
            epollEvt.events = epollEvt.events | EPOLLIN;
            epollEvt.events = epollEvt.events | EPOLLOUT;
            break;

        default:
            break;
    }

    epollEvt.data.ptr = socket;

    epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, socket->fd, &epollEvt);

    return POLL_OK;

}

int UnixEpoll::ctlMod(Event* socket)
{
    struct epoll_event epollEvt;

    if(socket->enableRead)
        {epollEvt.events = epollEvt.events | EPOLLIN;}

    if(socket->enableWrite)
        {epollEvt.events = epollEvt.events | EPOLLOUT;}

    epollEvt.data.ptr = socket;

    epoll_ctl(this->_epollFd, EPOLL_CTL_MOD, socket->fd, &epollEvt);

    return POLL_OK;
}

int UnixEpoll::ctlDel(Event* socket)
{
    struct epoll_event epollEvt;

    epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, socket->fd, &epollEvt);

    return POLL_OK;
}