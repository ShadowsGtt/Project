#include "../include/wechat.h"
#include "../include/database.h"

void handle_sign_up(int fd)
{
    struct 
    {
        char UID[16];
        char Uname[16];
        char Passwd[16];
        char Usex;
        char PhoneNumber[11];
    }msg;

    struct 
    {
        int res;
        char message[100];
    }reply;

    int n = recv(fd,&msg,sizeof(msg),0);
    if(n <= 0)
        close(fd);
    char sql[200];
    sprintf(sql,"insert into UserTable(UID,Uname,Passwd,Usex,PhoneNumber) values('%s','%s','%s','%c','%s')",msg.UID,msg.Uname,msg.Passwd,msg.Usex,msg.PhoneNumber);
    printf("sql:%s\n",sql);

    if(exc_sql(CONN_MYSQL,sql) == 0)
    {
        reply.res = 0;
        sprintf(reply.message,"注册成功!\n");
    }
    else
    {   
        reply.res = -1;
        sprintf(reply.message,"注册失败!该用户名已经被注册!\n");
    }
    n = send(fd,&reply,sizeof(reply),0);
    if(n <= 0)
        close(fd);

    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event) == -1) 
    {
        fprintf(stderr,"%d register failed!",fd);
    }
}
