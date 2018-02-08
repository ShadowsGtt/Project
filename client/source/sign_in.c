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
        recv(fd,&reply,sizeof(reply),0);
        fprintf(stdout,"%s",reply.message);
        if(reply.res == -1)
            sign_in(fd);
    }
}
