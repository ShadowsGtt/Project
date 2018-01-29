#include "wechat.h" 
void Connect_mysql()
{
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) 
    { 
        printf("mysql_init failed!\n"); 
        
    }
    const char *IP = "localhost";
    const char *username = "root";
    const char *password = "gaotian1314";
    const char *database = "wechat";

    if (mysql_real_connect(conn,IP, username, password, database, 0, NULL, 0)) 
    {
        printf("mysql connect success\n");
    }
    else 
    {
        
        printf("connect failed!  %d:%s\n",mysql_errno(conn),mysql_error(conn));
        exit(-1);
    }
    
}
