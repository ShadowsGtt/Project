#include "../include/wechat.h"
#include "../include/database.h"

void handle_sign_in(int fd)
{
    struct 
    {
        char UID[16];
        char Passwd[16];
    }mesg={"\0",{0}};

    struct 
    {
        int res;
        char message[100];
    }replay = {-1,{0}};

    int n = recv(fd,&mesg,sizeof(mesg),0);
    printf("username:%s\n",mesg.UID);
    printf("password:%s\n",mesg.Passwd);

    char sql[200];
    sprintf(sql,"select UID,Passwd from UserTable where UID='%s'\
            and Passwd ='%s' ",mesg.UID,mesg.Passwd);
    
    
    /* 用户名或密码检验通过 */
    if( select_result(CONN_MYSQL,sql) == 0)
    {
        replay.res = 0;
        sprintf(replay.message,"登录成功!");
    }
    /* 用户名密码检验失败 */
    else
    {
        replay.res = -1;
        sprintf(replay.message,"登录失败!用户名或密码错误!");

    }


    /* 通知用户结果 */
    n = send(fd,&replay,sizeof(replay),0 );
    if(n == -1)
    {
        perror("send in sign in:");
        close(fd);
    }


    /* 将fd事件回写成可读 */
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event) == -1) 
    {
        fprintf(stderr,"%d register failed!",fd);
    }
}
