//
// Created by wangy on 2020/9/2.
//

#ifndef BB_DEVICE_H
#define BB_DEVICE_H

#include "Adb_Command.h"
#include "DeviceList.h"
class Device : public Adb_Command{
public:
    Device(const char *ip, const char *port= nullptr, const char *binProgram= nullptr);
    static std::shared_ptr<Device>  parseList(std::string data);
    virtual ~Device();
    bool connect();
    std::shared_ptr<Device> isExistsDevice();
    const char*  getStatus() const;
    bool  isStatus();
    void setStatus(const char*  status);
    void setNetSegment();
    void setNetSegment(const char* netfa);
    char *getNetSegment() const;
    static std::shared_ptr<DeviceList<Device>> getDeviceList(const char* netSegment = nullptr, const char* status = nullptr );
private:
     std::string* Status;
     char* netSegment;



};


#endif //BB_DEVICE_H
