#include "../include/wechat.h"
#include "../include/database.h"

void *thread_run(void *th)
{
    int fd_counts = 0;
    int self = -1;
    int epoll_fd ;
    pthread_t tid = pthread_self();

    printf("thread %lu start running\n",tid);

    for(int i = 0;i < COUNT;i++)
    {
        if( thread[i].tid == tid )
        {
            self = i;
            break;
        }
    }

    int pipefd = thread[self].pipe[0];

    epoll_fd = epoll_create(MAX_CONN);   //创建epoll文件描述符

    assert(epoll_fd != -1);
    struct epoll_event ready_fd[MAX_CONN]; //存放epoll_wait返回的可读写事件

    for(int i = 0;i < MAX_CONN;i++)
        ready_fd[i].data.fd = -1;
    register_epoll_fd(epoll_fd,pipefd,0);

    while(1)
    {
        int rtnum = epoll_wait(epoll_fd,ready_fd,MAX_CONN,-1);
        for(int i = 0;i < rtnum;i++)
        {
            int fd = ready_fd[i].data.fd;
            
            /* 收到主线程传输的fd */
            if(fd == pipefd)
            {
                int read_fd ;
                int n = read(fd,&read_fd,4);
                if( n == -1 )
                    perror("pipefd read error");
                /* 记录fd */
                sockfd_set[read_fd] = read_fd;
                if(read_fd > maxfd)
                    maxfd = read_fd;

                printf("%lu 即将接管fd:%d [总数:%d]\n",tid,read_fd,++fd_counts);

                /* 注册fd到epoll中 */
                register_epoll_fd(epoll_fd,read_fd,0);
            }
            else if( ready_fd[i].events & EPOLLIN )
            {
                /* 解析客户请求 */
                printf("client mesg\n");
                analysis_head(fd);
            }
            else if(ready_fd[i].events & EPOLLOUT)
            {
                /* 应答客户请求 */
            }
            else if(ready_fd[i].events & EPOLLERR)
            {
                printf("%d closed\n",ready_fd[i].data.fd);
            }
            
        }
        
    }
}

