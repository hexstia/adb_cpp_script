//
// Created by wangy on 2020/9/2.
//

#include "DeviceList.h"
#include "Device.h"
#include <iostream>
template <typename  T>
std::shared_ptr<T> DeviceList<T>::getDevice(const char *ip) {
    return std::shared_ptr<T>();
}

template<typename T>
bool DeviceList<T>::isExist(const char *ip) {

    
    return false;
}



template<typename T>
void DeviceList<T>::push(T element,const char*ip) {
    data->insert(typename std::map<std::string ,T>::value_type (ip,element));
}

//
template<typename T>
T DeviceList<T>::getElement(const char* ip) {
    auto iter = data->find(ip);
//   auto iter =  data->find(ip);
//std::cout <<"iter->second"<<device.getIp() <<std::endl;
    return  iter->second;
}

template<typename T>
std::shared_ptr<std::map<std::string,T >> DeviceList<T>::getData() {
    return this->data;
}

template<typename T>
DeviceList<T>::DeviceList(const std::shared_ptr<std::map<std::string,T >> &data):data(data) {

}
