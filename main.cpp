#include <iostream>
#include <stdlib.h>
#include "Device.h"
#include <unistd.h>
using namespace std;


void testAdbCommand(){
    shared_ptr<Adb_Command> cmd = make_shared<Adb_Command>("192.168.4.1","5555");
    shared_ptr<Adb_Command> cmd1 = make_shared<Adb_Command>("192.168.4.1");
    shared_ptr<Adb_Command> cmd2 = make_shared<Adb_Command>("192.168.4.1","5555","adb");

}

#include <map>
void test_map(){
    Device dev("192.168.10.11");
    dev.setPort("6666");
    shared_ptr<map<string ,Device>> mmap = make_shared<map<string ,Device>>();
    mmap->insert(map<string ,Device>::value_type ("192.168.10.11",dev));
    auto iter =   mmap->find("192.168.10.11");
    Device de1 = iter->second;
    cout <<"dev1 port " << *de1.getIp()<<endl;
}


void testDevice(){
    shared_ptr<Device> sp_device = make_shared<Device>("192.168.11.2");
    bool  res  = false;
    //res 1 为执行语句成功，  0 执行语句失败
    res =  sp_device->connect();
    std::cout <<"connect res : "<<res<< endl;
    res =   sp_device->root();
    std::cout <<"root res : "<<res<< endl;
    res =  sp_device->remount();
    std::cout <<"remount res : "<<res<< endl;
    res = sp_device->reboot();
    std::cout <<"reboot res : "<<res<< endl;
//    res = sp_device->disconnect();
//    std::cout <<"disconnect res : "<<res<< endl;
    res = sp_device->pushFile("/tmp/tmp.GzXZJRRavI/cmake-build-debug/Makefile","/sdcard/", nullptr);
    std::cout <<"pushFile res : "<<res<< endl;
//    test_map();
//    sp_device->connect();
//    Device* device = new Device("","","");
//    device->connect();
}

#include <string.h>


int main() {
//    char* buf = new char[1024];
//    int len = strlen(buf);
//    cout << "len :"<<len <<endl;
    testDevice();
//    test_map();
    //    testAdbCommand();
    return 0;
}