#include "../include/wechat.h"

void sign_up(int fd)
{

    char reply[100];
    char ch;

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
        printf("输入错误,请重新输入(T or F):");
    }
    while((ch = getchar()) != '\n' && ch != EOF);

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
        recv(fd,&reply,sizeof(reply),0);
        fprintf(stdout,"%s",reply);
    }



}
