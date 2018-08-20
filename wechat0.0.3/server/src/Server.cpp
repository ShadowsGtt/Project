/*************************************************************************
	> Motto : Be better!
	> Author: ShadowsGtt 
	> Mail  : 1025814447@qq.com
	> Time  : 2018年08月16日 星期四 11时42分35秒
 ************************************************************************/
#include "../include/Server.h"
#include "../include/ReadConfig.h"
#include "../include/ThreadPool.h"

Server * Server::_Server = NULL;

void Server::Listen()
{
    size_t size;
    int on = 1;
    int port;
    
    cout<<"out:"<<_servConfig["port"]<<endl;
    port= atoi(_servConfig["port"].c_str());
    _ServAddr.sin_family = AF_INET;
    _ServAddr.sin_port = htons(port);
    inet_pton(AF_INET,_servConfig["ip"].c_str(),&_ServAddr.sin_addr);    

    
    if((_ListenFd = socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("socket");
        exit(1);
    }
    if(setsockopt(_ListenFd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))< 0)  {
        perror("setsockopt");
    }
    if(bind(_ListenFd,(struct sockaddr *)&_ServAddr,sizeof(struct sockaddr)) == -1){
        perror("bind");
        exit(1);
    }
    if(listen(_ListenFd,BACKLOG)==-1){
        perror("listen");
        exit(1);
    }
    cout<<"listen......."<<endl;

}

void Server::Loop()
{
    _Ep = new Epoll(); 
    _Ep->EpollCreate();
    
    while(true)
    {
        
        
    }
}

void Server::Run()
{
    ReadConfig(string("wechat.conf"),_servConfig);
    PrintConfig(_servConfig);
    ThreadPool tp;
    tp.PrintThreadPool();
    this->Listen();
}


