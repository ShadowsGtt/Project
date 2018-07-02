#ifndef _CONFIG_H
#define _CONFIG_H

#include "wechat.h"
#define MAX_LINE_BYTES  50      //每行字符数最大值
#define MAX_NAME_BYTES  30     //NAME最大值
#define MAX_VALUE_BYTES 30     //value 最大值
#define MAX_CONF_LINE   100     //config文件最大行数


typedef struct ServConf
{
    char ip[16];
    unsigned short port;
    int max_conn;
    int daemon;
}conf_t;

conf_t config;


conf_t DefaultConf ;
char *configString[MAX_CONF_LINE] ;

extern void SplitString(char *,char *,char *);
extern int ReadConfig(char *,int);
extern int IsConfigStr(char *);
extern void RemoveSpace(char *str);
extern int NullString(char *str);


#endif
