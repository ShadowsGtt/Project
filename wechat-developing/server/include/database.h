#ifndef _DATABASE_H
#define _DATABASE_H
#include "wechat.h"
int exc_sql(MYSQL *,const char *) ;   /* 执行sql语句 */
void connect_mysql(MYSQL *);
 int select_result(MYSQL *,const char *);

#endif
