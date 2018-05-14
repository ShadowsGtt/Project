#include<iostream>
using namespace std;


#include "tw_timer.h"

time_wheel::time_wheel():cur_slot(0)
{
    //初始化每个槽的头结点
    for (int i = 0; i < N; ++i)
        slots[i] = NULL;
}

time_wheel::~time_wheel()
{
    //遍历每个槽，并销毁定时器
    for (int i = 0; i < N; ++i) {
        tw_timer *tmp = slots[i];
        while (tmp) {
            slots[i] = tmp->next;
            delete tmp;
            tmp = slots[i];
        }
    }
}

void func(client_data *client)
{
    printf("调用回调函数,正在处理相应事件......\n");

}
tw_timer* time_wheel::add_timer(int timeout,client_data *data,
                               void (*callback)(client_data *))
{
    if (timeout < 0)
        return NULL;

    int ticks = 0;              //待插入定时器所需要总ticks
    if (timeout < TI)
        ticks = 1;
    else
        ticks = timeout / TI;

    int rotation = ticks / N;   //计算待插入的定时器在时间轮上要转动多少圈后触发
    int ts = (cur_slot + ticks) % N; //计算待持入定时器应该被插入的位置
    //int ts = (cur_slot + (ticks %N)) % N;

    //创建定时器，它在时间轮转动rotation圈之后触发，且位于第ts个槽上
    tw_timer *timer = new tw_timer(rotation, ts);
    //如果槽为空，则它新定时器插入，并设置为该槽的头节点
    
    timer->user_data = data;
    timer->callback_func = callback;    //定时器到期之后执行的处理函数
    if (!slots[ts]) {
        printf("新定时器:%d 分 %d 秒 ,秒钟所在位置: %d\n",rotation, ts, cur_slot);
        slots[ts] = timer;
    }
    else {
        printf("新定时器:%d 分 %d 秒 ,秒钟所在位置: %d\n",rotation, ts, cur_slot);
        timer->next = slots[ts];
        slots[ts]->prev = timer;
        slots[ts] = timer;
    }
    
    return timer;
}

void time_wheel::del_timer(tw_timer *timer)
{
    printf("in del_timer\n");
    if (!timer)
        return;

    int ts = timer->time_slot;
    if (timer == slots[ts]) {   //如果是头结点
        slots[ts] = slots[ts]->next;
        if (slots[ts])
            slots[ts]->prev = NULL;

        delete timer;
    }
    else {
        timer->prev->next = timer->next;
        if (timer->next)
            timer->next->prev = timer->prev;

        delete timer;
    }
}

void time_wheel::tick()
{
   //取得时间轮上当前槽的头结点
   tw_timer *tmp = slots[cur_slot];
   printf("秒针位置: %d\n", cur_slot);

   while (tmp) {
       //printf("tick the timer once\n");

       //如果定时器的rotation值大于0，则未到时，不处理
       if (tmp->rotation > 0) {
           tmp->rotation--;
           tmp = tmp->next;
       }
       else {

           printf("定时器到时,即将调用回调函数\n");
           tmp->callback_func(tmp->user_data);
           tw_timer *tmp2 = tmp->next;
           del_timer(tmp);
           tmp = tmp2;
       }
   }

   //更新时间轮的当前槽，以反映时间轮的转动
   cur_slot = ++cur_slot % N;
}
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>
time_wheel wheel;
void * clock(void *arg)
{
    printf("thread has run\n");

    struct timeval val;
    while(1)
    {
        val.tv_sec = 1;
        val.tv_usec = 0;
        int res = select(1,NULL,NULL,NULL,&val);
        if(!res)
            wheel.tick();
    }
}
int main()
{
    client_data client;

    pthread_t tid;
    pthread_create(&tid,NULL,clock,NULL);

    sleep(10);
    printf("wake up\n");
    wheel.add_timer(8,&client,func);
    wheel.add_timer(20,&client,func);
    wheel.add_timer(15,&client,func);
    wheel.add_timer(13,&client,func);
    wheel.add_timer(8,&client,func);
    wheel.add_timer(8,&client,func);
    while(1);
}
