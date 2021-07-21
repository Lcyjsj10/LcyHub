#pragma once
/*定义全局参数*/
const int MAX_PROCESS_NUM = 20;//假设最多可以容纳20个进程
int create_num = 0;    //记录创建进程的总数
int current_num = 0;   //记录现有进程的总数
int current_running_process = -1; //表示正在运行的进程ID号