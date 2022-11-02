#include "tiny_cofnig.h"
#include "tiny_error.h"

using namespace std;


GlobalConfig::GlobalConfig()
{
    this->config = new tinyConfig();
}

GlobalConfig::~GlobalConfig()
{
    cout<<"delete global config"<<endl;
    delete this->config;
}

static int GlobalConfig::setGlobalConfig(string cfgFilePath)
{
    if(cfgFilePath != nullptr)
        return CONFIG_RESET;

    _mutex.lock();

    _globalConfig = shared_ptr<GlobalConfig>(new GlobalConfig(), SafeDeletor());
    if(_globalConfig == nullptr)
        return CONFIG_ERR;

    //读配置文件
    //

    _mutex.unlock();

    return CONFIG_OK;
}

