#include "tiny_listen.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

Listen::Listen(shared_ptr<Module> module, shared_ptr<ObjectPoll> &poll)
:_module(module), _poll(poll),
{
    this->_globalConfig = GlobalConfig::getGlobalConfig();
    this->_manager = Manager::getManager();
}

Listen::~Listen()
{
    
}

int Listen::bind(const ListenFamily &family, const ListenType &type, const string &ip, const int &port)
{
    this->_family = ListenIpv4 ? AF_INET:AF_INET6;   this->_poll->ctlAdd(conn);
    this->_type = ListenTcp ? SOCK_STREAM:SOCK_DGRAM;
    this->_ip = ip;
    this->_port = port;

    this->fd = socket(_family, _type, 0);

    struct in_addr inAddr;
    inet_pton(_family, _ip.c_str(), &inAddr);

    struct sockaddr_in addr;
    addr.sin_family = _family;
    addr.sin_addr = inAddr;
    addr.sin_port = htons(_port);

    return bind(this->fd, (struct sockaddr *)addr, sizeof(addr));
}

int Listen::listen()
{
    return listen(this->fd, globalConfig->getConfig().listenBacklog);
}

void Listen::handler()
{
    //accpct
    Connection* conn = _manager->connRemove();
    if(conn == nullptr)
        return;

    int connSock = accept(this->fd, &conn->sockAddr, &conn->sockLen);
    conn->connInit(this->_poll, connSock, this->_type, this->_module->protocolInit());
    this->_poll->ctlAdd(conn);

    this->_poll->ctlAdd(this);

}