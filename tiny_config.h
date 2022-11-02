#pragma once

#include <iostream>
#include <mutex>
#include <memory>
#include <string>

using namespace std;

class GlobalConfig;

//智能指针删除器
class ConfigSafeDeletor
{
    public:
        void operator()(GlobalConfig *globalConfig)
        {
            delete globalConfig;
        }
};

class tinyConfig
{
    public:
        tinyConfig();
        ~tinyConfig();
    public:
        int listenBacklog;

        //conn
        int connectCount;
        int recvBufSize;
        int sendBUfSize;
};


class GlobalConfig
{
    private:
        GlobalConfig();
        ~GlobalConfig();

        GlobalConfig(const GlobalConfig &) = delete;
        GlobalConfig &operator=(const GlobalConfig &) = delete;

        //设置友元函数类，确保删除器能够访问到析构函数
        friend class ConfigSafeDeletor;

    public:
        static int setGlobalConfig(string cfgFilePath);
        static shared_ptr<GlobalConfig> getGlobalConfig(){ return _globalConfig; };

        tinyConfig* getConfig(){return config;}

    private:
        static shared_ptr<GlobalConfig> _globalConfig;
        static mutex _mutex;

        //配置参数
        tinyConfig* config;
};