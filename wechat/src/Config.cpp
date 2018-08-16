#include "../include/Config.h"


conf_t config;
conf_t DefaultConf ;
char *configString[MAX_CONF_LINE] ;

void InitDefaultConf()
{
    char *p;

    strcpy(DefaultConf.ip,"0.0.0.0");
    DefaultConf.port = 40000;
    DefaultConf.max_conn = 1024;
    DefaultConf.daemon = 1;

    /* ip */
    p = (char *)malloc(MAX_NAME_BYTES);
    bzero(p,MAX_NAME_BYTES);
    strcpy(p,"ip");
    configString[0] = p;

    /* port */
    p = (char *)malloc(MAX_NAME_BYTES);
    bzero(p,MAX_NAME_BYTES);
    strcpy(p,"port");
    configString[1] = p;

    /* max-conn */
    p = (char *)malloc(MAX_NAME_BYTES);
    bzero(p,MAX_NAME_BYTES);
    strcpy(p,"max-conn");
    configString[2] = p;

    /* daemon */
    p = (char *)malloc(MAX_NAME_BYTES);
    bzero(p,MAX_NAME_BYTES);
    strcpy(p,"daemon");
    configString[3] = p;

    configString[4] = NULL;

}

int ReadConfig(char *filename,int argc)
{
    InitDefaultConf();
    if(argc == 1 || !filename){
        config = DefaultConf;
        return 0;
    }

    FILE *fp;
    char buff[MAX_LINE_BYTES];
    char name[MAX_NAME_BYTES] = {0};
    char value[16] = {0};

    fp = fopen(filename,"r");
    if(!fp)
        return -1;

    while(fgets(buff,sizeof(buff),fp) != NULL)
    {
        RemoveSpace(buff);
        buff[strlen(buff) - 1] = '\0';
        if(buff[0] == '#' || buff[0] == '\0')
            continue;
        SplitString(buff,name,value);
        if(IsConfigStr(name)){
            printf("error in file: %s\n",filename);
            printf("\t\t\tname:[%s] is illegal\n",name);
            return -1;
        }

        if(!strcasecmp(name,"ip")){
            if(!NullString(value)){
                strcpy(config.ip,DefaultConf.ip);
            }
            else{
                strcpy(config.ip,value);
            }
        }
        else if(!strcasecmp(name,"port")){
            if(!NullString(value)){
                config.port = DefaultConf.port;
            }
            else{
                config.port = atoi(value);
            }
        }
        else if(!strcasecmp(name,"daemon")){
            if(!NullString(value)){
                config.daemon = DefaultConf.daemon;
            }
            else{
                if(!strcasecmp(value,"yes"))
                    config.daemon = 1;
                else if(!strcasecmp(value,"no"))
                    config.daemon = 0;
                else
                    return -1;
            }
        }
        else if(!strcasecmp(name,"max-conn")){
            if(!NullString(value)){
                config.max_conn = DefaultConf.max_conn;
            }
            else{
                config.max_conn = atoi(value);
            }
        }


        bzero(buff,sizeof(buff));
        bzero(name,sizeof(name));
        bzero(value,sizeof(value));
    }

    return 0;
}

int NullString(char *str)
{
    if(*str == '\0')
        return 0;
    return 1;
}
void SplitString(char *str,char *name,char *value)
{
    if(!str || *str == '\0')
        return;

    while(*str != ' ' && *str != '\0')
        *name++ = *str++;
    if(*str == '\0')
        return;

    str++;
    while(*str != '\0')
        *value++ = *str++;
}
/* 
 * 某字符串是否是规定字符串 
 * 是：返回0
 * 否：返回１
 * */
int IsConfigStr(char *str)
{
    int index = 0;

    while(configString[index])
    {
        if(!strcasecmp(str,configString[index]))
            return 0;
        index++;
    }
    return 1;
}


/* 移除字符串中多余的空格 */
void RemoveSpace(char *str)
{
    if(!str)
        return;

    int midSpaceNum = 0;
    int headSpaceNum = 0;
    char *p = str;
    char *d = str;
    char *s = str;

    while(*p++ == ' ')
        headSpaceNum++;

    while(*p != ' ')
        p++;

    while(*p++ == ' ')
        midSpaceNum++;

    if(!(midSpaceNum - 1) && !headSpaceNum)
       return;

    if(headSpaceNum){
        s += headSpaceNum;
        while(*s != ' ')
            *d++ = *s++;
    }
    else{ 
        while(*s++ != ' ')
            d++;
    }
    

    *d++ = *s++;
    s += (midSpaceNum - 1);

    while(*s != ' ' && *s != '\0')
    {
        *d++ = *s++;
    }
    *d = '\0';
}

