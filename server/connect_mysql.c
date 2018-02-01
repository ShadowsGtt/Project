#include "../include/wechat.h"
#include "../include/database.h"

void connect_mysql(MYSQL *conn)
{
    const char *IP = "127.0.0.1";
    const char *username = "wechat";
    const char *password = "wechat123";
    const char *database = "wechat";
    if (mysql_real_connect(conn,IP, username, password, database, 0, NULL, 0)) 
        fprintf(stdout,"connect mysql success\n");
    else 
    {
        fprintf(stderr,"connect mysql failed:%s\n",mysql_error(conn));
        mysql_close(conn);
    }
    
}
