#include "../include/wechat.h"

void *heart_beat(void *ag)
{
    printf("heart thread start running\n");

    /* 每隔5s向客户发送心跳包 */
    /* 超过15s未回复心跳的就关闭fd */
    char ht = 248;
    while(1)
    {
        for(int i = 3;i <= maxfd;i++)
        {
            if(sockfd_set[i] != 0)
            {
                if( heart_count[i] == 3)
                {
                    close(i);
                    printf("%d 15s not response,is closed\n",i); 
                    sockfd_set[i] = 0;
                    continue;
                }
                Send(i,&ht,1,0);
                heart_count[i]++; 
            }    
        }
        sleep(5);
    }

}
