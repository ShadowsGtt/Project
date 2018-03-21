#include "../include/head.h"
#include "../include/wechat.h"
void Connect(int fd)
{
    char a[] = {'\\','|','-','/'};
    int i = 0;
    while(1)
    {
        int rrr = -1;
        if(rrr = connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)  ) == -1 )
        {
            if(errno == ECONNREFUSED)
            {
                printf("[%c]",a[i%4]);
                printf("连接服务器失败,正在重新连接");
                fflush(stdout);
                usleep(100000);
                printf("\x1b[0G\x1b[2K"); /* Clear the line. */
                
                i++;
                if(i == 5)
                    i = 0;
                close(sockfd);
                
                sockfd = socket(AF_INET,SOCK_STREAM,0);
                continue;
            }
            else if(errno == ECONNRESET)
            {
                fprintf(stderr,"与服务器断开连接!\n正在重新连接...\n");
                close(sockfd);
                sockfd = socket(AF_INET,SOCK_STREAM,0);
                continue;

            }
            else if(errno == EINPROGRESS )
            {
                fprintf(stderr,"正在与连接服务器....\n");
                break;
                
            }
            else if(errno == ENETUNREACH )
            {
                fprintf(stderr,"服务器不可达,请检查您的网络连接!\n");
                close(fd);
                break;
            }
        }
        else
            break;
    }
}
