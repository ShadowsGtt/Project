#include "../include/wechat.h"

void handle_sign_in(int fd)
{
    struct 
    {
        int length;
        char sour[16];
        char dest[16];
        char password[16];
    }request;
    int n = recv(fd,&request,sizeof(request),0);
    printf("source:%s\ndest:%s\n",request.sour,request.dest);
    printf("password:%s\n",request.password);
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    //event.events |= EPOLLONESHOT;
    if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event) == -1) 
    {
        fprintf(stderr,"%d register failed!",fd);
    }
}
