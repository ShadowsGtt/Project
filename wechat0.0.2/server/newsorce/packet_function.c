#include "../include/wechat.h"
ssize_t Recv(int sockfd,void *buf,size_t len,int flags)
{
    char err_buf[30]={0};
    int n = recv(sockfd,buf,len,flags);
    sprintf(buf,"fd:%d recv error",sockfd);
    if(n == 0)
    {
        printf("fd:%d closed\n",sockfd);
        close(sockfd);
        sockfd_set[sockfd] = 0;
    }
    if(n == -1)
        perror(buf);

    return n;
}
ssize_t Send(int sockfd,void *buf,size_t len,int flags)
{
    int n = send(sockfd,buf,len,flags);
    
    //snprintf(buf,30,"fd:%d send error\n",sockfd);
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
