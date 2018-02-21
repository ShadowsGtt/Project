#include "../../include/head.h"
//#include "../../include/wechat.h"
#include "../../include/threadpool.h"
#define ServPort 40009
#define ServIp  "111.230.171.212"

struct sockaddr_in serv_addr;


void create_fd(int fd)
{
    printf("thread:%ld exc taks\n",pthread_self());
    if( connect(fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1  )
        perror("connect");
}
int main()
{
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ServPort);
    inet_pton(AF_INET,ServIp,&serv_addr.sin_addr);

    threadpool_t *pool = threadpool_create(7,1000,0);
    sleep(2);
    for(int i = 0;i < 21;i++)
    {
        int fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd == -1)
            perror("sockfd");
        threadpool_add(pool,create_fd,fd,0);
    }

    char ch;
    while( (ch = getchar()) != 'q' );
    for(int i = 3; i <= 24;i++)
    {
        close(i);
    }

}
