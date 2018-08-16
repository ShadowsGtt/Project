/*************************************************************************
	> Motto : Be better!
	> Author: ShadowsGtt 
	> Mail  : 1025814447@qq.com
	> Time  : 2018年08月05日 星期日 21时43分03秒
 ************************************************************************/

#include "./C_MyRedis.h"
#include<iostream>
#include <string>


using namespace std;

int main()
{
    
    CMyRedis redis;
    string ip("127.0.0.1");
    redis.Connect(ip,6379);


    string cmd("hmset 1 business Plugin category_name Agent rule 1 merge 60 sender wx_plug reciver lonnyliu:horsema");

    vector<pair<string,string> > vec;
    vec.push_back(pair<string,string>("business","Plugin"));
    vec.push_back(pair<string,string>("category_name","Agent"));
    vec.push_back(pair<string,string>("rule","1"));

    int key = 1;
    redis.Hmset(key,vec);
    vector<pair<string,string> > ret;
    
    ret = redis.Hmget(key,vec);
    cout<<"return of Hmget"<<endl;
    for(auto &c : ret)
    {
        cout<<"filed:"<<c.first<<"          value:"<<c.second<<endl;
    }
    return 0;
}
