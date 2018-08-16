/*************************************************************************
	> Motto : Be better!
	> Author: ShadowsGtt 
	> Mail  : 1025814447@qq.com
	> Time  : 2018年08月16日 星期四 10时27分45秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include "allHead.h"


class Server
{
public:
    void Run();
public:
    static Server *newServer()
    {
        if(!_Server){
            _Server = new Server();
        }
        return _Server;
    }
    map<string,string> &getServConfig()
    {
        return this->_servConfig;
    }
private:
    static Server *_Server;
    Server(){}

private:
    map<string,string> _servConfig;
};

#endif
