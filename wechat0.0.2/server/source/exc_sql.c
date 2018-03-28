#include "../include/wechat.h"
#include "../include/database.h"

int exc_sql(MYSQL *conn,const char *sql) 
{
    printf("--------------------in exc_sql-----------------------\n");
    int res = mysql_query(conn,sql);
    if (!res) 
    {
        printf("%lu rows affected\n", (unsigned long)mysql_affected_rows(conn));
        return 0;
    } 
    else 
    {
        fprintf(stderr, "error %d: %s\n", mysql_errno(conn), mysql_error(conn));
        return -1;
    }
    printf("exit exc_sql\n");
}
