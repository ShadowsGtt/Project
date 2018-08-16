/*************************************************************************
	> Motto : Be better!
	> Author: ShadowsGtt 
	> Mail  : 1025814447@qq.com
	> Time  : 2018年08月06日 星期一 17时33分59秒
 ************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

#define MAX_LINE_BYTES  50      //每行字符数最大值
#define MAX_NAME_BYTES  30     //NAME最大值
#define MAX_VALUE_BYTES 30     //value 最大值
#define MAX_CONF_LINE   100     //config文件最大行数

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
class WeChatConfig
{
public :
    WeChatConfig()
    {
        Config.push_back(pair<string,string>("ip","0.0.0.0"));
        Config.push_back(pair<string,string>("port","40000"));
        Config.push_back(pair<string,string>("daemon","no"));
        Config.push_back(pair<string,string>("max-conn","102400"));
    }
    ~WeChatConfig(){}
    void ReadConfig(const char *filename)
    {
        std::ifstream in;
        try
        {
            in.open(filename)
            
            while(in.eof())
            {
                string readline ;
                in>>readline;
                std::cout<<"readline"<<readline<<endl;
            }
        }
        catch(exception &e)
        {
            cout<<e.what()<<endl;
            exit(1);
        }
    }
    string GetIpValue()
    {
        for(auto &c : Config)
        {
            if(c.first == "ip")
                return c.second;
        }
        return "";
    }
    string GetPortValue()
    {
        for(auto &c : Config)
        {
            if(c.first == "port")
                return c.second;
        }
        return "";
    }
    string GetDaemonValue()
    {
        for(auto &c : Config)
        {
            if(c.first == "daemon")
                return c.second;
        }
        return "";
    }
    string GetMaxConnValue()
    {
        for(auto &c : Config)
        {
            if(c.first == "max-conn")
                return c.second;
        }
        return "";
    }
private :
        vector<pair<string,string> > Config;
};
#endif
