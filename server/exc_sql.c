#include "../include/wechat.h"
#include "../include/database.h"

void exc_sql(MYSQL *conn,const char *sql) 
{
    int res = mysql_query(conn,sql );
    if (!res) 
    {
        printf("Inserted %lu rows\n", (unsigned long)mysql_affected_rows(conn));
    } 
    else 
    {
        fprintf(stderr, "error %d: %s\n", mysql_errno(conn), mysql_error(conn));
    }
}
