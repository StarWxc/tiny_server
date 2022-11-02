#pragma once

#include <string>

#include "module/tiny_module.h"
#include "application/tiny_protocol.h"
#include "application/tiny_test_protocol.h"

using namespace std;

class testModule : public Module
{
    public:
        testModule(const string &name, const int &index);
        ~testModule();
        virtual void analyConfig(string config);
        virtual Protocol* protocolInit();
    private:
};

testModule::testModule(const string &name, const int &index)
:Module(name, index)
{
}

testModule::~testModule()
{
}

void testModule::analyConfig(const string &config)
{
    cout<<config<<endl;
}

Protocol* testModule::protocolInit()
{
    TinyTest* protocal = new TinyTest();
    return protocal;
}


/// /////////////
class testModuleFactory : public ModuleFactory
{
    public:
        testModuleFactory(const string &factoryName);
        ~testModuleFactory();
        virtual Module* moduleCreate(const int &index);
};

testModuleFactory::testModuleFactory()
:ModuleFactory("test")
{
}

testModuleFactory::~testModuleFactory()
{
}

Module* testModuleFactory::moduleCreate(const int &index)
{
    testModule* module = new testModule(this->_name, index);

    return module;
};