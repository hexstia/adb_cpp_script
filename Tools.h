//
// Created by wangy on 2020/9/4.
//

#ifndef CC_TOOLS_H
#define CC_TOOLS_H

#include <string>
#include <vector>
class Tools {
public:
    static void _split(const std::string &s, char delim, std::vector<std::string> &elems);
    static void _splitLine(const std::string &s,  std::vector<std::string> &elems);

};


#endif //CC_TOOLS_H
