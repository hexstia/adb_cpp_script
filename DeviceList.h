//
// Created by wangy on 2020/9/2.
//

#ifndef BB_DEVICELIST_H
#define BB_DEVICELIST_H


#include <memory>
#include <map>

template <typename T>
class DeviceList {
public:
    DeviceList(const std::shared_ptr<std::map<std::string,T >> &data);


    std::shared_ptr<T> getDevice(const char* ip);

      bool isExist(const char* ip);


        void push(T element,const char*ip);

        T getElement(const char* ip);

        std::shared_ptr<std::map<std::string,T >> getData();

private:
       std::shared_ptr<std::map<std::string,T >> data;

};


#endif //BB_DEVICELIST_H
