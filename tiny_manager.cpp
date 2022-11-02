#include "tiny_manager.h"
#include "tiny_error.h"

using namespace std;


Manager::Manager()
{
    this->_globalConfig = GlobalConfig::getGlobalConfig();
}

Manager::~Manager()
{
    cout<<"delete Manager"<<endl;
}

static int Manager::managerInit()
{
    if(_manager != nullptr)
        return CONFIG_RESET;

    _mutex.lock();

    _manager = shared_ptr<Manager>(new Manager, SafeDeletor());
    if(_manager == nullptr)
        return CONFIG_ERR;

    tinyConfig* gConfig = this->_globalConfig->getConfig();
    //init

    //conn
    this->connList = list<Connection*>(gConfig->connectCount, nullptr);
    for(auto &iter : this->connList)
    {
        iter = new Connection(gConfig->recvBufSize, gConfig->sendBUfSize);
    }



    _mutex.unlock();

    return CONFIG_OK;
}


static shared_ptr<Manager> Manager::getGManager()
{
    return _manager;
}


Connection* Manager::connRemove()
{
    if(this->connList.empty())
        return nullptr;
    _connMutex.lock();

    list<Connection*> iterator = this->connList.end();
    Connection* conn = *iterator;
    this->connList.pop_back();

    _connMutex.unlock();
    return conn;
}

void Manager::connAdd(const Connection* &conn)
{
    _connMutex.lock();

    this->connList.push_back(conn);

    _connMutex.unlock();
}







