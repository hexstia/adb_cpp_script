//
// Created by wangy on 2020/9/2.
//

#include "Adb_Command.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
ICommand &Adb_Command::set_ParamterList(const char **args) {
    return *this;
}

ICommand &Adb_Command::set_enviroment(const char **env) {
    return *this;
}


std::shared_ptr<std::string> Adb_Command::getCommandline() {
    return std::shared_ptr<std::string>();
}

void Adb_Command::setIp(const char *ip) {
        sp_ip = std::make_shared<std::string>(ip);
}

std::shared_ptr<std::string> Adb_Command::getIp() {

    return sp_ip;
}

void Adb_Command::setPort(const char *port) {
    sp_port =  std::make_shared<std::string>(port);

}

std::shared_ptr<std::string> Adb_Command::getPort() {

    return sp_port;
}

Adb_Command::Adb_Command() {

}


Adb_Command::Adb_Command(const char *ip, const char *port, const char *bin_program) {

    this->sp_commandline = std::make_shared<std::string>();
    if(ip == nullptr){
        throw "ip is null !!!";
    }else{
        setIp(ip);
    }

    if(port == nullptr){
        setPort("5555");
    }else{
        setPort(port);
    }

    if(bin_program == nullptr){
        *(this->sp_commandline) = "adb";
    }else{
        *(this->sp_commandline) = bin_program;
    }



}

bool Adb_Command::connect() {
    std::string cmdline = " connect ";
//    std::cout <<"buf :"<<buf <<std::endl;
    return exec(cmdline);
}

bool Adb_Command::disconnect() {
    std::string cmdline = " disconnect ";
//    std::cout <<"buf :"<<buf <<std::endl;
    return exec(cmdline);
    return false;
}

bool Adb_Command::reboot(const char *mode) {
    std::string cmdline = " root  "; //暂时不要重启 //待修复问题 // 还需要开线程处理。
//    std::cout <<"buf :"<<buf <<std::endl;
    return exec(cmdline);
}

bool Adb_Command::root() {
    std::string cmdline = " root  ";
//    std::cout <<"buf :"<<buf <<std::endl;
    return exec(cmdline);
}

bool Adb_Command::remount() {
    std::string cmdline = " remount ";
//    std::cout <<"buf :"<<buf <<std::endl;
    return exec(cmdline);
    return false;
}

bool Adb_Command::pushFile(const char *localPath, const char *targetPath, const char *options) {
    std::string cmdline = " push ";
    cmdline += localPath;
    cmdline += " ";
    cmdline += targetPath;
    return exec(cmdline);
}

bool Adb_Command::pushDir(const char *localPath, const char *targetPath, const char *options) {
    return false;
}

bool Adb_Command::pullFile(const char *localPath, const char *targetPath, const char *options) {
    return false;
}

bool Adb_Command::pullDir(const char *localPath, const char *targetPath, const char *options) {
    return false;
}

bool Adb_Command::installApk(const char *apkPath, const char *args) {
    return false;
}

bool Adb_Command::uninstallApk(const char *packageName) {
    return false;
}

bool Adb_Command::sync(const char *localPath) {
    return false;
}

bool Adb_Command::getAdbShell(std::shared_ptr<Adb_Shell> &sp_shell) {
    return false;
}

bool Adb_Command::getAdbLog(std::shared_ptr<Adb_Log> &sp_log) {
    return false;
}

/**
 *  重定向 标准输出到本地缓存，为了执行sytem
 * @param cmdline
 * @param buf
 * @param size
 * @return
 */
int Adb_Command::system_cmd(const char *cmdline, char *buf, size_t size) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return -1;
    }
    int tmpout = dup(fileno(stdout));   // 保存stdout，用于恢复
    int fd = dup2(pipefd[1], fileno(stdout)); // 将标准输出重定向到pipefd[1]，即之后标准输出将写到pipefd[1]
    if (fd < 0)
    {
        return -2;
    }
    int ret = system(cmdline);  // 执行程序，这里会有输出
    dup2(tmpout, fileno(stdout));// 恢复stdout
    close(pipefd[1]);// 关闭输入，N.B.这里必须先关闭才能继续下面的读操作，否则读操作会挂住

    char c;
    int index = 0;
    while (read(pipefd[0], &c, 1) > 0)// 读吧，保证缓冲区够用
    {
        buf[index++] = c; // 保存到本地缓冲中
        if (index >= (size - 1))
            break;
    }
    buf[index] = '\0';
    close(pipefd[0]);
    return ret;
}

/**
 *   重定向 标准输出到本地缓存，为了执行sytem
 * @param cmdline
 * @param buf
 * @param size
 * @return
 */
int Adb_Command::system_cmd_thread(const char *cmdline, char *buf, size_t size) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return -1;
    }
    int tmpout = dup(fileno(stdout));   // 保存stdout，用于恢复
    int fd = dup2(pipefd[1], fileno(stdout)); // 将标准输出重定向到pipefd[1]，即之后标准输出将写到pipefd[1]
    if (fd < 0)
    {
        return -2;
    }
    int ret = system(cmdline);  // 执行程序，这里会有输出
    dup2(tmpout, fileno(stdout));// 恢复stdout
    close(pipefd[1]);// 关闭输入，N.B.这里必须先关闭才能继续下面的读操作，否则读操作会挂住

    char c;
    int index = 0;
    while (read(pipefd[0], &c, 1) > 0)// 读吧，保证缓冲区够用
    {
        buf[index++] = c; // 保存到本地缓冲中
        if (index >= (size - 1))
            break;
    }
    buf[index] = '\0';
    close(pipefd[0]);
    return ret;
}

Adb_Command::~Adb_Command() {

}

bool Adb_Command::exec(std::string& cmdline) {
        cmdline.insert(0,"adb");
        if(cmdline.find("connect")==4||cmdline.find("disconnect")==4){
//            std::cout <<"connect "<<cmdline.find("connect")<<std::endl;
            cmdline.append(*getIp()+":"+(*getPort()));
            cmdline.append(" ; sleep 0.1");
        }else{
            cmdline.insert(3," -s "+*getIp()+":"+*getPort()+" ");
        }
    std::cout <<"   ___exec()  : "<<cmdline <<std::endl;
        char* buf = new char[255];
        int res =  system_cmd(cmdline.c_str(),buf,255);
        bool rebo = (res==0) ?true:false;
//    std::cout <<"buf :"<<buf <<std::endl;
        delete[] buf;
        cmdline.clear();
    return rebo;
}


