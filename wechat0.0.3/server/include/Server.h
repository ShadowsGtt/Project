/*************************************************************************
	> Motto : Be better!
	> Author: ShadowsGtt 
	> Mail  : 1025814447@qq.com
	> Time  : 2018年08月16日 星期四 10时27分45秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

#include "allHead.h"
#include "Epoll.h"


class Epoll;
struct Client
{
    int SockFd;
    string UserName;
    string GroupId;
    string NickName;
    sockaddr_in ClientAddr;

    Client(int fd = -1){}
    
};

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
    map<string,string> &getServConfig(){ return this->_servConfig; }
    void Listen();
    void Loop();
private:
    static Server *_Server;
    Server()
    {
        _ListenFd = -1;
        memset(&_ServAddr,0,sizeof(_ServAddr));
        _Ep = NULL;
    }
    ~Server(){
        delete _Server;
    }

private:
    map<string,string> _servConfig;
    //vector<string> _ConfigComment;
    sockaddr_in _ServAddr;
    int _ListenFd;
    hash_map<string,Client> ClientMesg;
    Epoll *_Ep;
    
};

#endif
