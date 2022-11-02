#pragma once

#include <string>

#include "application/tiny_protocol.h"

using namespace std;


class Module
{
    public:
        Module(const string &name, const int &index)
        :_name(name), _index(index)
        {};
        virtual ~Module(){};

        virtual void analyConfig(const string &config){};
        virtual Protocol* protocolInit() = 0;
    protected:
        string _name;
        int    _index;
}


class ModuleFactory
{
    public:
        ModuleFactory(const string &factoryName);
        ~ModuleFactory();

        bool checkName(const string &name);
        virtual Module* moduleCreate(const int &index){};

    protected:
        string _factoryName;
};

ModuleFactory::ModuleFactory(const string &factoryName)
:_factoryName(factoryName)
{
}

ModuleFactory::~ModuleFactory()
{
}

bool ModuleCreate::checkName(const string &name)
{
    int ans = this->_factoryName.compare(name);
    return ans == 0? true:false;
}
