#include "../include/head.h"
#include "../include/wechat.h"

void get_fritab(int fd)
{
    int n = -1,file_fd = -2;
    char file_name[26]={0}; 
    sprintf(file_name,"%sFRITAB.txt",username);

    char friend[10][16];
    bzero(friend,sizeof(friend));


    /* 接收好友表 */
    n = recv(fd,friend,32768,0);
    if(n == -1)
        perror("recv in get_fritab");
    
    /* //测试
    int num = 0;
    for(int i = 0;i < 160;i++)
    {
        if(i%16 == 0)
            putchar(10);
        printf("'[%d]%c'",i%16+1,buf[i]);
        
    }
    int num = 0;
    while(friend[num][0] != 0 )
    {
        printf("friend[%d]:%s\n",num,friend[num]);
        num++;
    }
    */


    /* 好友表存入文件 */
    file_fd = open(file_name,O_WRONLY|O_CREAT|O_TRUNC,S_IWUSR|S_IRUSR);
    
    if(fd == -1)
        perror("open");
    
    int k = 0;
    while(friend[k][0] != 0 )
    {
        n = write(file_fd,friend[k],16);
        if(n == -1)
            perror("write in file");
        k++;
    }
    fflush( fdopen(file_fd,"w") );
    close(file_fd);
}
