#include "../../include/wechat.h"
#include "../../include/threadpool.h"
//extern int threadpool_add(threadpool_t *,void (*)(int),int,int );

void create_fd(int fd)
{
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
    for(int i = 0;i < 1000;i++)
    {
        int fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd == -1)
            perror("sockfd");
        threadpool_add(pool,create_fd,fd,0);
        printf("%d connected\n",fd);
    }

    char ch;
    while( (ch = getchar()) != 'q' );
    for(int i = 3; i <= 1003;i++)
    {
        close(i);
    }

}
