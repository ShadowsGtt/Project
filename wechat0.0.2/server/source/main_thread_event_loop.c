
#include "../include/wechat.h"
#include "../include/threadpool.h"
#include "../include/database.h"


void main_thread_event_loop(int timeout)
{
    int                  epoll_fd;
    int                  new_fd;
    int                  listenfd ;
    struct sockaddr_in   client_addr;
    int                  sin_size;

    sin_size = sizeof(struct sockaddr_in);



    listenfd = Socket(TCPSERV);
    open_noblock(listenfd);

    /* epoll 相关 */
    epoll_fd = epoll_create(MAX_CONN);   //创建epoll文件描述符
    assert(epoll_fd != -1);
    struct epoll_event ready_fd[MAX_CONN]; //存放epoll_wait返回的可读写事件

    /* 初始化epoll事件结构 */
    for(int i = 0;i < MAX_CONN;i++)
        ready_fd[i].data.fd = -1;

    /* 将listenfd注册到epoll事件中 */
    register_epoll_fd(epoll_fd,listenfd,0);

    int i = 0;
    while(1)
    {
        if(COUNT == i)
            i = 0;
        int rtnum = epoll_wait(epoll_fd,ready_fd,MAX_CONN,timeout);

        new_fd = accept(listenfd,(struct sockaddr *)&client_addr,&sin_size );
        printf("accept new_fd:%d\n",new_fd);
        int n = write(thread[i].pipe[1],&new_fd,4);
        if(n == -1)
            perror("write in pipe");
        if(n == 4)
            printf("write to pipe 4 bytes\n");
        i++;
    }
}
