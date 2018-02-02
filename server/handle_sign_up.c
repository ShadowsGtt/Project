#include "../include/wechat.h"
#include "../include/database.h"

void handle_sign_up(int fd)
{
    struct 
    {
        char UID[17];
        char Uname[17];
        char Passwd[17];
        char Usex;
        char PhoneNumber[12];
    }msg;
    int n = recv(fd,&msg,sizeof(msg),0);
    char *sql;
    sprintf(sql,"insert into \
            UserTable(UID,Uname,Passwd,Usex,PhoneNumber)\
            values('%s','%s','%s','%c','%s')",\
            msg.UID,msg.Uname,msg.Passwd,msg.Usex,msg.PhoneNumber);
    exc_sql(CONN_MYSQL,sql);
}
