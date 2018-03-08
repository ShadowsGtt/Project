#include "../include/wechat.h"
#include "../include/database.h"


void handle_chat(int fd)
{
    printf("----------in handle_chat-------------\n");

    /* 提取头部 */
    
    struct 
    {
        int type;
        char dst_name[16];
        char src_name[16];
        char mesg[MAXMESGLEN];
    }mesg;
    int n = recv(fd,&mesg,sizeof(mesg),MSG_PEEK );
    if(n == -1)
        perror("in handle_chat,recv");

    printf("窥探到目的地:%s,type:%d\n",mesg.dst_name,mesg.type);

    if(n == 0)
    {
        printf("in handle_chat,close fd");
        close(fd);
    }

    /* 转发内容 */
    int pipefd[2];
    n = pipe(pipefd);
    if(n == -1)
        perror("in handle_chat,pipefd");
    
    /* 消息移动到管道中 */
    n = splice(fd,NULL,pipefd[1],NULL,sizeof(mesg),0);
    if(n == -1)
        perror("fd->pipe");

    int dst_fd = get_fd_byname(mesg.dst_name);

    
    if(dst_fd != -1)
    {
        n = splice(pipefd[0],NULL,dst_fd,NULL,sizeof(mesg),0);
        if(n == -1)
            perror("pipe->fd");
        
    }
    else if(dst_fd == -1) 
    {
        bzero(&mesg.mesg,sizeof(mesg.mesg));
        strcat(mesg.mesg,"消息发送失败,对方不在线[暂不支持离线消息]");
        n = send(fd,&mesg,sizeof(mesg),0);
        if(n == -1)
            perror("send offline");
        else
            printf("对方不在线已告知\n");
    }

    bzero(&mesg,sizeof(mesg));
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event) == -1) 
    {
        fprintf(stderr,"%d register failed!",fd);
    }
}
