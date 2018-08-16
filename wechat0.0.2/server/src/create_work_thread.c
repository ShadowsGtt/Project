#include "../include/wechat.h"
#include "../include/database.h"

/* @count:the number of working thread */
void create_work_thread(int count)
{
    if(count <= 0 )
        return ;

    for(int i = 0;i < count;i++)
    {
        
        if(pthread_create(&(thread[i].tid), NULL,thread_run,NULL) != 0) 
        {
            perror("thread_create");
            return ;
        }
        if(pipe(thread[i].pipe) != 0)
        {
            perror("pipe create");
            return ;
        }

    }
}
