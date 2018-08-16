#include "../include/wechat.h"
#include "../include/config.h"
#include "../include/threadpool.h"
#include "../include/database.h"
int pthread_setconcurrency(int);


/* 这里相当于main函数 */
int main(int argc,char *argv[])
{
    //signal(SIGSEGV,SIG_IGN);

    printf("main thread start running\n");
    printf("reading config...\n");
    if(argc == 1){
        if(ReadConfig(NULL,1))
            exit(-1);
    }
    else
        if(ReadConfig(argv[1],argc))
            exit(-1);

    printf("config :\n");
    printf("ip :%s\n",config.ip);
    printf("port :%d\n",config.port);
    printf("max-conn :%d\n",config.max_conn);
    printf("daemon :%s\n",config.daemon == 1 ? "yes":"no");
    if(config.daemon)
        set_daemon("./server",0);



    /* 设置同时可运行的线程数量 */
    //pthread_setconcurrency(COUNT+1);


    /* 连接redis */
    conn_redis = redisConnect("127.0.0.1", 6379); //redis server默认端口
    if (conn_redis != NULL && conn_redis->err) {
        printf("connect redis error: %s\n", conn_redis->errstr);
    }
    else{
        printf("connect redis success!\n");
    }

    /* 连接mysql */
    CONN_MYSQL =  mysql_init(NULL);  
    if (CONN_MYSQL == NULL)  
        fprintf(stderr,"mysql_init failed!\n"); 

    int opt = 1;
    mysql_options(CONN_MYSQL, MYSQL_OPT_RECONNECT, &opt);
    connect_mysql(CONN_MYSQL);


    /* 创建心跳线程 */
#if 0
    bzero(heart_count,sizeof(heart_count));
    pthread_t heart_tid;
    if(pthread_create((&heart_tid), NULL,heart_beat,NULL) != 0) 
        perror("thread heart create failed");
#endif

    /* 创建工作线程 */
    create_work_thread(COUNT);

    main_thread_event_loop(-1);
    
}
