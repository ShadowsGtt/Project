
#include "../include/head.h"
#include "../include/wechat.h"
int Socket(int type)   
{
    int sockfd;
    const int on = 1;
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ServPort);
    inet_pton(AF_INET,ServIp,&serv_addr.sin_addr);
    switch(type)
    {
        case UDPCLIENT:         /* udp客户端套接字 */
            if((sockfd = socket(AF_INET,SOCK_DGRAM,0))==-1)
            {
                perror("socket");
                exit(1);
            }
            break;
        case TCPCLIENT:         /* tcp客户端套接字 */
            if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
            {
                perror("socket");
                exit(1);
            }
            if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1 )
            {
                perror("connect");
                exit(-1);
            }

            break;
        default:
            sockfd = -1;
    }
        return sockfd;
}
