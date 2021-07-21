#pragma once
#include<cstring>
#include<map>
#include<vector>
#include<list>
#include <string>
#include<iostream>
#include"parameter.h"
using namespace std;
/*定义结构体*/
struct RCB {
    int r_id = -1;    //定义资源编号
    bool r_valid = false; //资源一开始无效
    string r_name = "";   //资源名称为空
    int r_initial = 0;  //资源初始量
    int r_remain = 0;   //资源剩余量
    std::list<int> wait_list[3];//表示因为请求不到该资源而等待的进程队列（按３个优先级划分）
};
struct PCB {
    int p_id = -1;     //进程编号
    int create_id = -1; //进程被创建的次序（注意与进程id不同，进程id记录的是进程在进程队列中的序号）
    bool p_valid = false; //标记进程是否有效，若有效valid=true;若无效valid = false
    string p_name = "";     //进程名初始为空
    string p_status = "";    //进程状态初始设为空
    int p_priority = -1;     //进程优先级初始为-1
    int occupied_resources[4] = { 0,0,0,0 };//进程占用的资源数
    int block_resource_id = -1, r_need = 0;//block_id表示引起阻塞的资源id，need表示需要的资源数（假设一旦阻塞则不能再请求资源）
    int parent = -1;
    list<int> child_list; //子进程队列（用子进程ID号表示）
};

PCB p_list[MAX_PROCESS_NUM];  //分配20个进程控制块的空间
RCB r_list[4];             //分配4个资源控制块的空间
vector<int> ready_list[3];    //定义就绪队列，分为3个优先级
vector<pair<int, string>> run_list;//用于存储系统中所有存在过的运行进程
list<int> destroy_list;       //用于存储要删除的进程编号
map<string, int> r_map;    //用于将资源名称与资源序号对应
