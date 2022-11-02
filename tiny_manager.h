#pragma once

#include <iostream>
#include <mutex>
#include <memory>
#include <string>
#include <list>

#include "socket/tiny_connection.h"

using namespace std;


class Manager
{
    private:
        Manager();
        ~Manager();

        Manager(const Manager &) = delete;
        Manager &operator=(const Manager &) = delete;

    public:
        static int managerInit();
        static shared_ptr<Manager> getManager();

        Connection* connRemove();
        void connAdd(const Connection* &conn);

    private:
        static shared_ptr<Manager> _manager;
        static mutex _mutex;

        shared_ptr<GlobalConfig> _globalConfig;

        list<Connection*> connList;
        mutex _connMutex;
};