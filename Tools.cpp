//
// Created by wangy on 2020/9/4.
//

#include "Tools.h"
#include <sstream>
#include "string.h"
 void Tools::_split(const std::string &s, char delim, std::vector<std::string> &elems){
        std::stringstream ss(s);
        std::string item;

        while (getline(ss, item, delim)) {
                elems.push_back(item);
            }
}

void Tools::_splitLine(const std::string &s, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    char* buf = new char[255];
    while(ss.getline(buf,255)){
        item = buf;
        elems.push_back(item);
        memset(buf,0,255);
    }
    delete[] buf;
}