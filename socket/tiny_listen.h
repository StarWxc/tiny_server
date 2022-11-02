#pragma once

#include <string>
#include <memory>

#include "tiny_event.h"
#include "poll/tiny_poll.h"
#include "module/tiny_module.h"
#include "tiny_manager.h"

using namespace std;

enum ListenFamily
{
    ListenIpv4,
    ListenIpv6,
};

enum ListenType
{
    ListenTcp,
    ListenUdp,
};

class Listen : public Event
{
    public:
    
        Listen(shared_ptr<Module> module, shared_ptr<ObjectPoll> &poll);
        ~Listen();
        
        int bind(const ListenFamily &family, const ListenType &type, const string &ip, const int &port);
        int listen();
        virtual void handler();
    private:
        ListenFamily _family;
        ListenType   _type;
        string  _ip;
        int     _port;
        
        shared_ptr<ObjectPoll> _poll;
        shared_ptr<Module> _module;

        shared_ptr<GlobalConfig> _globalConfig;
        shared_ptr<Manager> _manager;
};
