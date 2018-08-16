/*************************************************************************
	> Motto : Be better!
	> Author: ShadowsGtt 
	> Mail  : 1025814447@qq.com
	> Time  : 2018年08月16日 星期四 11时42分35秒
 ************************************************************************/
#include "../include/Server.h"
#include "../include/ReadConfig.h"
#include "../include/ThreadPool.h"


Server * Server::_Server = NULL;
void Server::Run()
{
    ReadConfig(string("wechat.conf"),_servConfig);
    PrintConfig(_servConfig);
    ThreadPool tp;
    tp.PrintThreadPool();
    
    
}
