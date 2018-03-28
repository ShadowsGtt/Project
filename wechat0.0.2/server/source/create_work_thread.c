#include "../include/wechat.h"
#include "../include/database.h"

/* @count:the number of working thread */
thread_t * create_work_thread(int count)
{
    if(count <= 0 )
        return NULL;
    thread_t *p = (thread_t *)malloc(sizeof(thread_t)*count);
    if(NULL == p)
        return NULL;

    for(int i = 0;i < count;i++)
    {
        
        if(pthread_create(&(p[i]->tid), NULL,thread_run, NULL) != 0) 
        {
            perror("thread_create");
            free(p);
            return NULL;
        }
        if(pipe(p[i].pipe) != 0)
        {
            perror("pipe create");
            return NULL;
        }

    }
    return p;
}
