#include "../include/wechat.h"
#include "../include/threadpool.h"
#include "../include/database.h"
int pthread_setconcurrency(int);


/* 这里相当于main函数 */
void main_thread_func() 
{
    set_daemon("./server",0);

    printf("main thread start running\n");
    printf("backlog:%d\n",BACKLOG);

    /* 连接数据库 */
    CONN_MYSQL =  mysql_init(NULL);  
    if (CONN_MYSQL == NULL)  
        fprintf(stderr,"mysql_init failed!\n"); 
    int opt = 1;
    mysql_options(CONN_MYSQL, MYSQL_OPT_RECONNECT, &opt);
    connect_mysql(CONN_MYSQL);


    pthread_setconcurrency(6);

    epollfd = epoll_create(MAX_CONN);   //创建epoll文件描述符

    int listenfd = Socket(TCPSERV);
    open_noblock(listenfd);
    assert(epollfd != -1);
    struct epoll_event ready_fd[MAX_CONN]; //存放epoll_wait返回的可读写事件

    for(int i = 0;i < MAX_CONN;i++)
    {
        ready_fd[i].data.fd = -1;
        clients_mesg[i].fd = -1;
    }

    register_epoll_fd(epollfd,listenfd,0);

    threadpool_t *first_pool = threadpool_create(6,1500,0);
    while(1)
    {
        int rtnum = epoll_wait(epollfd,ready_fd,MAX_CONN,-1);
        for(int i = 0;i < rtnum;i++)
        {
            int fd = ready_fd[i].data.fd;
            
            /* 有客户连接 */

            if(fd == listenfd )
            {
                /* 主线程将新连接注册到epoll事件中 */
                threadpool_add(first_pool,handle_connection,listenfd,0);
            }
            
            else if( ready_fd[i].events & EPOLLIN )
            {
                /* 解析客户请求 */
                threadpool_add(first_pool,handle_read_request,fd,0);
            }

            else if(ready_fd[i].events & EPOLLOUT)
            {
                /* 应答客户请求 */
                threadpool_add(first_pool,prequest_func[fd],fd,0);
            }
            
        }
        
    }
}
