
#ifndef _EPOOL_H
#define _EPOOL_H

#include "../include/allHead.h"

#define EPOLL_READ      0x01
#define EPOLL_WRITE     0x02
#define EPOLL_ERROR     0x04
#define EPOLL_HUP       0x08
#define EPOLL_LT        0x16
#define EPOLL_ET        0x32

#define MAX_EPOLL_EVENT 65536

class Epoll
{
public:
    Epoll()
    {
        _EpollFd = -1;
        _ReadyNum = 0;
        _Timeout = -1;
        _isTimeout = false;
        
    }
    void EpollCreate();
    void EpollAdd(int,int);
    void EpollDel(int);
    void EpollMod(int,int);
    void EpollWait();
    
private:
    int _EpollFd;
    int _ReadyNum;
    int _Timeout;
    bool _isTimeout;
    map<int,epoll_event> _EpollEvent;
    vector<epoll_event> _ReadyEpEvent;
};

#endif
