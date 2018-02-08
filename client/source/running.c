#include "../include/wechat.h"
void running()
{
    char str[101]={0};  
    char arr[4]={'|','/','-','\\'};  
    int i=0;  
    for(i;i<101;++i)  
    {  
        str[i]='>';  
        printf("[%d][%-100s][%c]",i%101,str,arr[i%4]);  
        printf("\r");  
        usleep(100000);  
        fflush(stdout);
    }  
    printf("\n");   
}  
