#include "../include/wechat.h"
#include "../include/threadpool.h"

int sign_in(int fd)
{
    struct 
    {
        int request;
        char UID[16];
        char Passwd[16];
    }message;

    struct 
    {
        int res;
        char message[100];
    }reply;

    message.request = SIGNIN;


    char ch;
    printf("\n请输出您的用户名:");
    scanf("%s",message.UID);
    while((ch = getchar()) != '\n' && ch != EOF);

    printf("请输入密码:");
    
    get_password(message.Passwd);
    /*
    scanf("%s",message.Passwd);
    while((ch = getchar()) != '\n' && ch != EOF);
    */
    int n = send(fd,&message,sizeof(message),0 );

    if(n == 0)
    {
        printf("server is too busy\n");
    }
    else if(n == -1)
    {
        perror("error:");
    }
    else
    {
        /* 输出服务器回馈消息  */
        recv(fd,&reply,sizeof(reply),0);
        fprintf(stdout,"\n\033[;31m***********%s***************\033[0m\n",reply.message);
        if(reply.res == -1)   /* 登录失败,重新输入 */
            sign_in(fd);
    }
    if(reply.res == 0)
        return reply.res;
}
