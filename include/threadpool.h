#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#define MAX_THREADS 64   /**/
#define MAX_QUEUE 65536
/* 线程池关闭的方式 */
typedef enum {
    immediate_shutdown = 1,
    graceful_shutdown  = 2
} threadpool_shutdown_t;

/**
 * 线程池一个任务的定义
 */
typedef struct 
{
    void (*function)(int);
    int argument;
}threadpool_task_t;

/* 错误码 */
typedef enum {
    threadpool_invalid        = -1,
    threadpool_lock_failure   = -2,
    threadpool_queue_full     = -3,
    threadpool_shutdown       = -4,
    threadpool_thread_failure = -5
} threadpool_error_t;

typedef enum {
    threadpool_graceful       = 1
} threadpool_destroy_flags_t;


typedef struct threadpool 
{
  pthread_mutex_t lock;     //互斥锁
  pthread_cond_t notify;    //线程等待的条件变量
  pthread_t *threads;       //指向线程数组的
  threadpool_task_t *queue; //指向任务队列头的指针
  int thread_count;         //线程数量
  int queue_size;           //任务数量最大值
  int head;                 //任务队列头
  int tail;                 //任务队列尾
  int count;                //已经存在的任务数量
  int shutdown;             //标记线程迟是否关闭
  int started;              //线程池现有线程数量
}threadpool_t;

extern int threadpool_destroy(threadpool_t *pool, int flags);

extern void *threadpool_thread(void *);

extern int threadpool_free(threadpool_t *);

extern threadpool_t *threadpool_create(int , int , int);

extern int threadpool_add(threadpool_t *, void (*)(int),int , int );

extern int threadpool_add(threadpool_t *, void (*)(int),int , int );

#endif
