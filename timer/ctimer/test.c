#include "C_tw_timer.h"

void callback_func(client_data_t *data)
{
    printf("正在调用回调函数.....\n");
}

int main()
{
    client_data_t data;
    time_wheel_t *tw = CreateTimeWheel(60,1);

    sleep(4);
    printf("wake up\n");
    tw->add_timer(tw,10,callback_func,&data);
    tw->add_timer(tw,70,callback_func,&data);
    tw->add_timer(tw,60,callback_func,&data);
    pthread_join(g_tid, NULL);
}
