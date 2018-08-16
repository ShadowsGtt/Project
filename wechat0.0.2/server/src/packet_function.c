#include "../include/wechat.h"
ssize_t Recv(int sockfd,void *buf,size_t len,int flags)
{
    printf("in Recv   fd:%d\n",sockfd);
    int n = recv(sockfd,buf,len,flags);
    if(n == 0)
    {
        printf("fd:%d closed\n",sockfd);
        close(sockfd);
        sockfd_set[sockfd] = 0;
    }
    if(n == -1)
        perror("Recv error");

    return n;
}
ssize_t Send(int sockfd,void *buf,size_t len,int flags)
{
    int n = send(sockfd,buf,len,flags);
    
    if(n == 0)
    {
        printf("fd:%d closed\n",sockfd);
        close(sockfd);
        sockfd_set[sockfd] = 0;
    }
    if(n == -1)
        perror("send erro");

    return n;
}
