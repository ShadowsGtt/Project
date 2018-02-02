#include "../include/wechat.h"
#include "../include/database.h"

void handle_sign_up(int fd)
{
    printf("int handle_sign_up\n");
    struct 
    {
        char UID[16];
        char Uname[16];
        char Passwd[16];
        char Usex;
        char PhoneNumber[11];
    }msg;
    int n = recv(fd,&msg,sizeof(msg),0);
    char sql[200];
    sprintf(sql,"insert into UserTable(UID,Uname,Passwd,Usex,PhoneNumber) values('%s','%s','%s','%c','%s')",msg.UID,msg.Uname,msg.Passwd,msg.Usex,msg.PhoneNumber);
    printf("sql:%s\n",sql);

    if(exc_sql(CONN_MYSQL,sql) == 0)
    {
        int n = send(fd,"恭喜!注册成功!",20,0);
    }
}
