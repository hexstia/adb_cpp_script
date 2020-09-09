//
// Created by wangy on 2020/9/2.
//

#include "Device.h"
#include "DeviceList.cpp"
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "Tools.h"
Device::Device(const char *ip, const char *port, const char *binProgram):Adb_Command(ip,port,binProgram)  {
//    std::cout <<"Device(const char *, const char *, const char *)  ..."<<std::endl;
    setNetSegment();
    Status = new std::string();

}



/**
 *  链接设备
 * @return
 */
bool Device::connect() {
    std::shared_ptr<Device> sp_device = nullptr ;
    sp_device = isExistsDevice();
    //sp_device!=null : device already appears in the device list.
    // isStatus :device list :device is  device online status
    //isStatus :offline or lock usb debug
    if(sp_device && sp_device->isStatus()){
        return true ;
    }

    return Adb_Command::connect();
}
/**
 *  设备已经链接的判断，
 *  如果设备已经链接则返回
 * @return
 */

std::shared_ptr<Device> Device::isExistsDevice() {
    std::cout <<"isExistsDevice()"<< netSegment<<std::endl;

    std::shared_ptr<DeviceList<Device>> sp_devicelist = getDeviceList(netSegment,"all");

    if(sp_devicelist->getData()->size()==0){
        return nullptr;
    }

    const char* p = getIp()->c_str();
    std::cout <<"ip :"<< p <<std::endl;
    std::shared_ptr<std::map<std::string,Device >> sp_map = sp_devicelist->getData();
    auto iter =  sp_map->find(p);
    if(sp_map->end() ==iter) { //在map中未找到
        return nullptr;
    }
    Device device = iter->second;
     std::cout <<"hello world "<<std::endl;
     bool status =   device.isStatus();
     std::cout <<"isExistsDevice() status "<<status <<std::endl;
     if(status){
        return std::make_shared<Device>(device);
    }
    return nullptr;
//return nullptr;
}

bool Device::isStatus() {
    if(this->Status == nullptr){
        return false;
    }
    if(Status->compare("device")){
        return true;
    }else{
        return false;
    }


    return false;
}

const char* Device::getStatus() const {
//    std::cout<<"getStatus()"<<std::endl;
        if(this->Status == nullptr){
            return nullptr;
        }
//        std::cout<<"getStatus()"<<*(this->Status)<<std::endl;
        return this->Status->c_str();
}

void Device::setStatus(const char*  status) {
    if(this->Status == nullptr){
        this->Status = new std::string(status);
    }else{
//        std::cout<< "setStatus : "<<this->Status <<std::endl;
        this->Status->erase();
        this->Status->append(status);
                std::cout<< "setStatus() : "<<*(this->Status) <<std::endl;
    }
}

void Device::setNetSegment() {
    netSegment = new char[3];
//    std::cout <<*getIp()<<std::endl;
    std::string strip = *getIp();
    int startIndex =strip.find('.',(strip.find('.')+1));
    int endIndex = strip.rfind('.');
    startIndex++;
//    std::cout <<startIndex <<std::endl;
//    std::cout <<endIndex <<std::endl;
    std::string str_netfault = strip.substr(startIndex,endIndex-startIndex);
    strcpy(netSegment,str_netfault.c_str());
//    std::cout <<"netSegment  "<<netSegment <<std::endl;
}



void test_display( std::shared_ptr<DeviceList<Device>>& devlist){
    std::shared_ptr<std::map<std::string,Device >> datas =   devlist->getData();
    int count  = (*datas).size();
    if(count ==0)
        return;
    std::string str =  "192.168.11.1";
    auto iters =  datas->find(str);
    std::cout << "/********************** test ***********************/"<<std::endl;
    std::cout <<"device ip "<< iters->first<<std::endl;
    std::cout <<"device list  ip "<<(*iters->second.getIp()).c_str()<<std::endl;
    std::cout <<"device list  port "<<(*iters->second.getPort()).c_str()<<std::endl;
    char* netse = iters->second.getNetSegment();
    std::cout <<"device list  netfa "<<netse<<std::endl;
    std::cout <<"device list  status "<<(iters->second.getStatus())<<std::endl;
    std::cout << "/********************** test ***********************/"<<std::endl;
}
/**
 *
 * @param netSegment
 * @param status offline ,device ,sync
 * @return
 */
std::shared_ptr<DeviceList<Device>> Device::getDeviceList(const char *netSegment, const char *status) {
     std::cout <<"___getDeviceList()"<<std::endl;
//     system("adb connect 192.168.11.1:5555 ; sleep 0.1");
     std::string myStatus(status);
        int len = 10240;
        char *buf = new char[len];
        system_cmd("adb devices",buf,len);
        std::string res_line = buf;
        delete[] buf ;
        std::vector<std::string> vector;
        Tools::_splitLine(res_line,vector);
        std::cout <<"start......."<<std::endl;
        std::shared_ptr<std::map<std::string,Device >> data  = std::make_shared<std::map<std::string,Device >>();
//         Device de("192.168.11.1");
//        data->insert(std::map<std::string ,Device>::value_type ("192.168.10.11",de));
        std::shared_ptr<DeviceList<Device>> devlist  = std::make_shared<DeviceList<Device>>(data);
     for (  auto it =  vector.begin(); it !=  vector.end(); ++it) {
         if(it==vector.begin()){ //跳过表头  List of devices attached
             continue;
         }
         if(it==(vector.end()-1)){ //最后的空格跳过
             continue;
         }
         int cmpres = strcmp(status,"all");

         if(cmpres !=0){ //如果不是全选 则需要判断是 offline 还是device 等其他情况
         int findres = (*it).find(status); //如果内容 找不到所选标示则 跳过 筛选是自己想要的设备状态
         if(findres == -1){
             continue;
            }
         }
         std::shared_ptr<Device> sp_device = Device::parseList(*it);
         if(sp_device->getNetSegment() ==std::string(netSegment)){ // 网段相同
             std::cout <<"相等网段"<<std::endl;
             const char* char_ip = (*(sp_device->getIp())).c_str();
             devlist->push(*sp_device,char_ip);
         }
         std::cout << *it << " ========\n";
        }
    std::cout <<"endl......."<<std::endl;
//    test_display(devlist);

    return devlist;
}

Device::~Device() {
//        delete Status;


}

std::shared_ptr<Device>  Device::parseList(const std::string  data) {

    int tableIndex = data.find('\t');
    std::string myStatus = data.substr(tableIndex+1,data.length()-tableIndex); //解析status
    std::string ip_and_port = data.substr(0,tableIndex); //解析IPand port
    int colonIndex = ip_and_port.find(':');
    std::string ip = data.substr(0,colonIndex); //解析IP
    std::string port = data .substr(colonIndex+1,tableIndex-colonIndex); //解析IP
    int p1_index = data.find('.');
    int p2_index = data.find('.',p1_index+1);
    int p3_index = data.rfind('.');
    p2_index++;
    std::string _netfa  =  data.substr(p2_index,p3_index-p2_index); //解析网段
    std::shared_ptr<Device> device  = std::make_shared<Device>(ip.c_str());
    device->setPort(port.c_str());
    device->setStatus(myStatus.c_str());
    try {
        device->setNetSegment(_netfa.c_str());
//        device->setNetSegment(NULL);
    }catch (const std::string& msg){
        std::cerr <<"exception :"<<msg<<std::endl;
    }


    return device;
}

void Device::setNetSegment(const char *netfa) {

    if(netSegment!= NULL){
        free(netSegment);
    }
    if(netfa == NULL){
        throw std::string("Please use a function  setNetSegment(void)  without parameters ");
    }
    int len = strlen(netfa);
    netSegment = new char[len];
    strcpy(netSegment,netfa);

}

char *Device::getNetSegment() const {

    return netSegment;
}



