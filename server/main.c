
#include "gt.h"
int main()
{
    printf("backlog:%d\n",BACKLOG);
    threadpool_t *first_pool = threadpool_create(6,1500,0);
    int listenfd = Socket(TCPSERV);
    open_noblock(listenfd);
    //Connect_mysql();
    int epollfd = epoll_create(MAX_CONN);   //创建epoll文件描述符
    assert(epollfd != -1);
    struct epoll_event ready_fd[MAX_CONN]; //存放epoll_wait返回的可读写事件
    
    /* initial */
    for(int i = 0;i < MAX_CONN;i++)
    {
        ready_fd[i].data.fd = -1;
        clients[i].fd = -1;
    }

    register_epoll_fd(epollfd,listenfd,0);

    main_thread_func(epollfd,ready_fd,first_pool,listenfd);

    
    return 0;
}
