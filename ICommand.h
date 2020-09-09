//
// Created by wangy on 2020/9/2.
//

#ifndef CC_ICOMMAND_H
#define CC_ICOMMAND_H

#include <string>
#include <memory>

class ICommand {
public:
    virtual   ICommand& set_ParamterList(const char* args[])=0;
    virtual   ICommand& set_enviroment(const char* env[])=0;
    virtual   std::shared_ptr<std::string>  getCommandline() = 0;
    virtual   void     setIp(const char* ip)=0;
    virtual   std::shared_ptr<std::string>  getIp()=0;
    virtual    void     setPort(const char* port)=0;
    virtual   std::shared_ptr<std::string>  getPort()=0;
};


#endif //CC_ICOMMAND_H
