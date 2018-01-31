
#include "gt.h"
int main()
{
    /*
    int listenfd = Socket(TCPSERV);
    open_noblock(listenfd);
    printf("backlog:%d\n",BACKLOG);
    //Connect_mysql();
    int epollfd = epoll_create(MAX_CONN);   //创建epoll文件描述符
    assert(epollfd != -1);
    struct epoll_event ready_fd[MAX_CONN]; //存放epoll_wait返回的可读写事件


    thread_arg_t args;
    bzero(&args,sizeof(args));
    args.listenfd = listenfd;
    args.epollfd = epollfd;
    
    
    for(int i = 0;i < MAX_CONN;i++)
    {
        ready_fd[i].data.fd = -1;
        clients[i].fd = -1;
    }

    register_epoll_fd(epollfd,listenfd,0);

    //threadpool_t *first_pool = threadpool_create(6,1500,0);
    //main_thread_func(ready_fd,first_pool,&args);
    main_thread_func(ready_fd,&args);
*/
    main_thread_func();
    
    return 0;
}
