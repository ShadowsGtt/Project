#include "../../include/head.h"
//#include "../../include/wechat.h"
#include "../../include/threadpool.h"


threadpool_t *threadpool_create(int thread_count, int queue_size, int flags)
{
    if(thread_count <= 0 || thread_count > MAX_THREADS || queue_size <= 0 || queue_size > MAX_QUEUE) {
        return NULL;
    }

    threadpool_t *pool;
    int i;

    /* 申请内存创建内存池对象 */
    if((pool = (threadpool_t *)malloc(sizeof(threadpool_t))) == NULL) {
        goto err;
    }

    /* Initialize */
    pool->thread_count = 0;
    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;

    /* 申请线程数组和任务队列所需的内存 */
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);
    pool->queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * queue_size);

    /* 初始化互斥锁和条件变量 */
    if((pthread_mutex_init(&(pool->lock), NULL) != 0) ||
       (pthread_cond_init(&(pool->notify), NULL) != 0) ||
       (pool->threads == NULL) ||
       (pool->queue == NULL)) {
        goto err;
    }

    /* 创建指定数量的线程开始运行 */
    for(i = 0; i < thread_count; i++) {
        if(pthread_create(&(pool->threads[i]), NULL,threadpool_thread, (void*)pool) != 0) {
            threadpool_destroy(pool, 0);
            return NULL;
        }
        pool->thread_count++;
        pool->started++;
    }

    return pool;

 err:
    if(pool) {
        threadpool_free(pool);
    }
    return NULL;
}

int threadpool_add(threadpool_t *pool, void (*function)(int ),
                   int argument, int flags)
{
    int err = 0;
    int next;

    if(pool == NULL || function == NULL) {
        return threadpool_invalid;
    }

    /* 必须先取得互斥锁所有权 */
    
    if(pthread_mutex_lock(&(pool->lock)) != 0) {
        return threadpool_lock_failure;
    }

    /* 计算下一个可以存储 task 的位置 */
    next = pool->tail + 1;
    next = (next == pool->queue_size) ? 0 : next;

    do {
        /* Are we full ? */
        /* 检查是否任务队列满 */
        if(pool->count == pool->queue_size) {
            err = threadpool_queue_full;
            break;
        }

        /* 检查当前线程池状态是否关闭 */
        if(pool->shutdown) {
            err = threadpool_shutdown;
            break;
        }

        /* 在 tail 的位置放置函数指针和参数，添加到任务队列 */
        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].argument = argument;
        /* 更新 tail 和 count */
        pool->tail = next;
        pool->count += 1;
        printf("task count:%d\n",pool->count);

        if(pool->count == 20)
        for(int k = 0;k < pool->count;k++)
        {
            if(pthread_cond_signal(&(pool->notify)) != 0) 
            {
                err = threadpool_lock_failure;
                break;
            }

        }
    } while(0);

    /* 释放互斥锁资源 */
    if(pthread_mutex_unlock(&pool->lock) != 0) {
        err = threadpool_lock_failure;
    }

    return err;
}

void *threadpool_thread(void *threadpool)
{
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t task;
    printf("%lu线程开始运行\n",pthread_self());
    for(;;) 
    {

        printf("before wait\n");
        pthread_mutex_lock(&(pool->lock));
        printf("%ld get lock\n",pthread_self());
        /* 线程池开启并且没有任务可以执行,则睡眠 */
        //while(pool->count == 0 && (!pool->shutdown) )
        

        //while(pool->count < 20 && (!pool->shutdown) )
wait:pthread_cond_wait(&(pool->notify), &(pool->lock));
            printf("thread:%ld accept signal\n",pthread_self());
            if(pool->count == 0)
            {
                printf("count == %d,thread:%ld sleep\n",pool->count,pthread_self());
                goto wait;
            }

        printf("after wait\n");
        /* 关闭的处理 */
        if((pool->shutdown == immediate_shutdown) ||
           ((pool->shutdown == graceful_shutdown) &&
            (pool->count == 0))) {
            break;
        }

        printf("%lu线程取得%d号任务\n",pthread_self(),pool->head);

        /* 取得任务队列的第一个任务 */
        task.function = pool->queue[pool->head].function;
        task.argument = pool->queue[pool->head].argument;
        /* 更新 head 和 count */
        pool->head += 1;
        pool->head = (pool->head == pool->queue_size) ? 0 : pool->head;
        pool->count -= 1;

        printf("剩余任务:%d\n",pool->count);

        pthread_mutex_unlock(&(pool->lock));


        /* 开始运行任务 */
        (task.function)(task.argument);
        /* 执行完任务后继续下一轮循环  */
        /* 等待下一次任务 */
    }

    /* 线程将结束，更新运行线程数 */
    pool->started--;

    pthread_exit(NULL);
    return(NULL);
}

int threadpool_destroy(threadpool_t *pool, int flags)
{
    int i, err = 0;

    if(pool == NULL) {
        return threadpool_invalid;
    }

    /* 取得互斥锁资源 */
    if(pthread_mutex_lock(&(pool->lock)) != 0) {
        return threadpool_lock_failure;
    }

    do {
        /* 判断是否已在其他地方关闭 */
        if(pool->shutdown) {
            err = threadpool_shutdown;
            break;
        }

        /* 获取指定的关闭方式 */
        pool->shutdown = (flags & threadpool_graceful) ?
            graceful_shutdown : immediate_shutdown;

        /* 唤醒所有因条件变量阻塞的线程，并释放互斥锁 */
        if((pthread_cond_broadcast(&(pool->notify)) != 0) ||
           (pthread_mutex_unlock(&(pool->lock)) != 0)) {
            err = threadpool_lock_failure;
            break;
        }

        /* 等待所有线程结束 */
        for(i = 0; i < pool->thread_count; i++) {
            if(pthread_join(pool->threads[i], NULL) != 0) {
                err = threadpool_thread_failure;
            }
        }
        /* 同样是 do{...} while(0) 结构*/
    } while(0);

    if(!err) {
        /* 释放内存资源 */
        threadpool_free(pool);
    }
    return err;
}

/* 释放线程池占用内存 */
int threadpool_free(threadpool_t *pool)
{
    if(pool == NULL || pool->started > 0) {
        return -1;
    }

    /* 释放线程 任务队列 互斥锁 条件变量 线程池所占内存资源 */
    if(pool->threads) {
        free(pool->threads);
        free(pool->queue);

        pthread_mutex_lock(&(pool->lock));
        pthread_mutex_destroy(&(pool->lock));
        pthread_cond_destroy(&(pool->notify));
    }
    free(pool);
    return 0;
}


