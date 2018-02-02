#ifndef _DATABASE_H
#define _DATABASE_H
#include "wechat.h"
extern int exc_sql(MYSQL *,const char *) ;   /* 执行sql语句 */
extern void connect_mysql(MYSQL *);

#endif
