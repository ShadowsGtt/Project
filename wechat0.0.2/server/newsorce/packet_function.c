#include "../include/wechat.h"
ssize_t Recv(int sockfd,void *buf,size_t len,int flags)
{
    char err_buf[20];
    int n = recv(sockfd,buf,len,flags);
    sprintf(buf,"fd:%d recv error",sockfd);
    if(n == 0)
    {
        printf("fd:%d closed\n",sockfd);
        close(sockfd);
    }
    if(n == -1)
        perror(buf);

    return n;
}
