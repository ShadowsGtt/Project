
#ifndef _EPOOL_H
#define _EPOOL_H

#include "../include/allHead.h"
#include <cstdio>
#include <cstdlib>

#define EPOLL_READ      0x01
#define EPOLL_WRITE     0x02
#define EPOLL_ERROR     0x04
#define EPOLL_HUP       0x08
#define EPOLL_LT        0x16
#define EPOLL_ET        0x32


class Epoll
{
public:
    Epoll()
    {
        EpollFd = -1;
        
    }
    void EpollCreate();
    void EpollAdd(int,int);
    void EpollDel(int);
    void EpollMod(int,int);
    
    
private:
    int _EpollFd;
    map<int,epoll_event> _EpollEvent;
    
}

#endif
