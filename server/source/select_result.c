#include "../include/wechat.h"
#include "../include/database.h"
int select_result(MYSQL *conn,const char *sql)
{
    printf("\n**********in select_result************\n");
    int ret = -1;
    MYSQL_RES *result; // mysql 记录集
    MYSQL_ROW row;
    
    
    int res = mysql_query(conn,sql);
    if (!res) 
    {
        //printf("Inserted %lu rows\n", (unsigned long)mysql_affected_rows(conn));
    } else 
    {
        fprintf(stderr, "error %d: %s\n", mysql_errno(conn), mysql_error(conn));
        return -1;
    }
    
    
    result = mysql_store_result(conn);
    if( ( row=mysql_fetch_row(result) ) != NULL  ) 
    {
        printf("row:%s,%s\n",row[0],row[1]);
        ret = 0;
        
    }
    //while ((row=mysql_fetch_row(result))) // 打印结果集
    //{
        //printf("%s,%s\n",row[0],row[1]);
        //if((strcmp(username,row[0])==0) && (strcmp(password,row[1])==0))
    //}
    mysql_free_result(result); // 释放结果集
    return ret;
}
