#include "../include/wechat.h"

int sign_up(int fd)
{

    int res  = -1;  /* return of function */
    char ch;

    struct 
    {
        int res;
        char message[100];
    }reply;

    struct
    {
        int request;
        char UID[16];
        char Uname[16];
        char Passwd[16];
        char Usex;
        char PhoneNumber[11];
    }message;

    message.request = SIGNUP;


    printf("\n注册时您需要注意一下几点:\n\t1.用户名和密码只能是字母或汉子或下划线\n\
\t2.姓名由于系统原因暂时不支持汉字\n");
    printf("\n请输出您的用户名:");
    scanf("%s",message.UID);
    while((ch = getchar()) != '\n' && ch != EOF);

    printf("请输入密码:");
    scanf("%s",message.Passwd);
    while((ch = getchar()) != '\n' && ch != EOF);

    printf("请输入您的名字:");
    scanf("%s",message.Uname);
    while((ch = getchar()) != '\n' && ch != EOF);

    printf("请选择性别：T(boy)  F(girl):");
    while((message.Usex = getchar()) != 'T' && message.Usex !='F' )
    {
        while((ch = getchar()) != '\n' && ch != EOF);
        printf("输入错误,请重新输入(T or F):");
    }

    printf("请输入电话号码：");
    scanf("%s",message.PhoneNumber);
    while((ch = getchar()) != '\n' && ch != EOF);

    printf("正在为您注册,请稍等......\n");
    int n = send(fd,&message,sizeof(message),0);
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
        fprintf(stdout,"\n\033[;31m**********%s*************\033[0m\n",reply.message);
    }
    if(reply.res == 0)
        res = 0;

    return res;
}
