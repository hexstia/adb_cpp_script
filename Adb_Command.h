//
// Created by wangy on 2020/9/2.
//

#ifndef CC_ADB_COMMAND_H
#define CC_ADB_COMMAND_H

#include "ICommand.h"
#include "Adb_Log.h"
#include "Adb_Shell.h"

class Adb_Command :public ICommand{

private:
    std::shared_ptr<std::string> sp_ip;
    std::shared_ptr<std::string> sp_port;
    std::shared_ptr<std::string> sp_commandline;

    public:
    Adb_Command();

    virtual ~Adb_Command();

    Adb_Command(const char *ip, const char * port= nullptr, const char * bin_program= nullptr);

    bool exec(std::string& cmdline);
    ICommand &set_ParamterList(const char **args) override;

    ICommand &set_enviroment(const char **env) override;

    std::shared_ptr<std::string> getCommandline() override;

    void setIp(const char *ip) override;

    std::shared_ptr<std::string> getIp() override;

    void setPort(const char *port) override;

    std::shared_ptr<std::string> getPort() override;

    virtual bool connect();

    virtual bool disconnect();

    virtual bool reboot(const char* mode = nullptr);

    virtual bool root();

    virtual bool remount();

    virtual bool pushFile(const char* localPath,const char* targetPath,const char* options = nullptr);

    virtual bool pushDir(const char* localPath,const char* targetPath,const char* options = nullptr);

    virtual bool pullFile(const char* localPath,const char* targetPath,const char* options = nullptr);

    virtual bool pullDir(const char* localPath,const char* targetPath,const char* options = nullptr);

    virtual bool installApk(const char* apkPath,const char* args= nullptr);

    virtual bool uninstallApk(const char* packageName);

    virtual bool sync(const char* localPath);

    virtual bool getAdbShell(std::shared_ptr<Adb_Shell> &sp_shell);

    virtual bool getAdbLog(std::shared_ptr<Adb_Log> &sp_log);

    static  int system_cmd(const char *cmdline, char *buf, size_t size);

    static  int system_cmd_thread(const char *cmdline, char *buf, size_t size);
};



#endif //CC_ADB_COMMAND_H
