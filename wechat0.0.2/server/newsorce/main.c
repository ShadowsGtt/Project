#include "../include/wechat.h"
#include "../include/threadpool.h"
#include "../include/database.h"
int pthread_setconcurrency(int);


/* 这里相当于main函数 */
int main()
{
    //signal(SIGSEGV,SIG_IGN);
    //set_daemon("./server",0);

    printf("main thread start running\n");
    printf("backlog:%d\n",BACKLOG);

    int epoll_fd;
    int opt = 1;
    int new_fd;
    int sin_size = sizeof(struct sockaddr_in);
    int listenfd = Socket(TCPSERV);
    maxfd = 0;
    bzero(heart_count,sizeof(heart_count));
    printf("sizeof:%lu\n",sizeof(heart_count));

    struct sockaddr_in client_addr;

    /* 设置同时可运行的线程数量 */
    pthread_setconcurrency(COUNT+1);

    /* 开启listenfd的非阻塞模式 */
    open_noblock(listenfd);

    /* 连接数据库 */
    CONN_MYSQL =  mysql_init(NULL);  
    if (CONN_MYSQL == NULL)  
        fprintf(stderr,"mysql_init failed!\n"); 
    mysql_options(CONN_MYSQL, MYSQL_OPT_RECONNECT, &opt);
    connect_mysql(CONN_MYSQL);

    /* epoll 相关 */
    epoll_fd = epoll_create(MAX_CONN);   //创建epoll文件描述符
    assert(epoll_fd != -1);
    struct epoll_event ready_fd[MAX_CONN]; //存放epoll_wait返回的可读写事件

    /* 初始化epoll事件结构 */
    for(int i = 0;i < MAX_CONN;i++)
        ready_fd[i].data.fd = -1;

    /* 将listenfd注册到epoll事件中 */
    register_epoll_fd(epoll_fd,listenfd,0);

    /* 创建心跳线程 */
    pthread_t heart_tid;
    if(pthread_create((&heart_tid), NULL,heart_beat,NULL) != 0) 
        perror("thread heart create failed");

    /* 创建工作线程 */
    create_work_thread(COUNT);
    
    int i = 0;
    while(1)
    {
        if(COUNT == i)
            i = 0;
        int rtnum = epoll_wait(epoll_fd,ready_fd,MAX_CONN,-1);

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
