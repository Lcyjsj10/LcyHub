#pragma once
#include"parameter.h"
#include"datastructure.h"

/*声明函数*/
void init();
bool create_process(string name, int priority);
int ready_priority_max();
void scheduler();
bool release_resource(int id, int unit);
bool is_ancestor(int a_id, int d_id);
bool destroy_process(int id);
bool time_out();
int request_resource(int id, int req);
void reset();


/*定义函数*/
void init() {
    //初始化资源名称
    r_list[0].r_name = "R1";
    r_list[1].r_name = "R2";
    r_list[2].r_name = "R3";
    r_list[3].r_name = "R4";
    //初始化资源队列名称和初始量、剩余量
    for (int i = 0; i < 4; ++i) {
        r_list[i].r_valid = true;
        r_list[i].r_id = i;
        r_list[i].r_initial = i + 1;
        r_list[i].r_remain = i + 1;
    }
    //将进程名和进程序号做映射
    r_map.insert(pair<string, int>("R1", 0));
    r_map.insert(pair<string, int>("R2", 1));
    r_map.insert(pair<string, int>("R3", 2));
    r_map.insert(pair<string, int>("R4", 3));
}
bool create_process(string name, int priority) {         //将函数设为bool类型，若创建成功则返回True，否则返回False
    for (int i = 0; i < MAX_PROCESS_NUM; ++i) {
        if (p_list[i].p_valid == false) {                    //若进程列表中第i个进程无效
            p_list[i].p_id = i;                         //进程的ID号等于i
            current_num++;                              //现有进程总数加一
            create_num++;                               //创建进程总数加一
            p_list[i].create_id = create_num;           //创建进程id号等于创建进程总数
            p_list[i].p_valid = true;                     //进程有效
            p_list[i].p_name = name;                    //进程名称等于name
            p_list[i].p_priority = priority;            //进程优先级等于priority
            p_list[i].parent = current_running_process; //该进程的父进程等于当前正在运行的进程
            if (current_running_process >= 0) {
                p_list[current_running_process].child_list.push_back(i);//当前正在运行的进程的子进程列表中插入新创建的进程
            }
            p_list[i].p_status = "ready";               //新创建的进程状态为"ready"
            ready_list[priority].push_back(i);          //将进程放入就绪队列
            return true;                                //创建成功返回true
        }
    }
    return false;                                      //创建失败
}
int ready_priority_max() { //查找就绪队列中最高的优先级
    int ready_max = -1;//初始化为-1
    for (int i = 2; i >= 0; --i) {
        if (!ready_list[i].empty()) {
            ready_max = i;
            return ready_max;
        }
    }
    return ready_max;
}
void scheduler() {
    int ready_max = ready_priority_max();
    if (ready_max < 0) {//若就绪队列为空，直接返回
        return;
    }
    if (current_running_process == -1) {//若此时没有运行的进程，则将就绪队列中优先级最高的运行
        current_running_process = ready_list[ready_max][0];
        ready_list[ready_max].erase(ready_list[ready_max].begin());
    }
    else {
        int p = p_list[current_running_process].p_priority;
        if (p < ready_max) {
            ready_list[p].push_back(current_running_process);
            current_running_process = ready_list[ready_max][0];
            ready_list[ready_max].erase(ready_list[ready_max].begin());
        }
    }
    p_list[current_running_process].p_status = "running";  //将进程的状态变为就绪
    return;
}
bool release_resource(int id, int unit) {
    if (!r_list[id].r_valid) {
        return false;
    }
    r_list[id].r_remain += unit;
    for (int i = 2; i >= 0; --i) {
        if (!r_list[id].wait_list[i].empty()) {
            int temp_p_id = r_list[id].wait_list[i].front();
            while (!r_list[id].wait_list[i].empty() && p_list[temp_p_id].r_need <= r_list[id].r_remain) {
                temp_p_id = r_list[id].wait_list[i].front();
                r_list[id].r_remain -= p_list[temp_p_id].r_need;
                p_list[temp_p_id].r_need = 0;
                p_list[temp_p_id].block_resource_id = -1;
                r_list[id].wait_list[i].pop_front();
                ready_list[p_list[temp_p_id].p_priority].push_back(temp_p_id);
                p_list[temp_p_id].p_status = "ready";
            }
        }
    }
    return true;
}
bool time_out() {
    if (current_running_process == -1) {
        return false;
    }
    else {
        int running_priority = p_list[current_running_process].p_priority;
        ready_list[running_priority].push_back(current_running_process);
        p_list[current_running_process].p_status = "ready";
        current_running_process = -1;             //此时没有正在运行的进程
        return true;
    }
}
bool is_ancestor(int a_id, int d_id) {
    int father_id = p_list[d_id].parent;  //father_id初始化为d_id的父进程
    while (father_id != -1) {
        if (father_id == a_id) {
            return true;
        }
        else {
            father_id = p_list[father_id].parent;
        }
    }
    return false;
}
bool destroy_process(int id) {     //销毁进程ID等于id的进程，仍然定义为bool类型，若释放成功，则返回true否则返回false。
    //先入队列destroy_list
    for (int i = 0; i < MAX_PROCESS_NUM; ++i) {
        if (i == id || is_ancestor(id, i))
        {
            destroy_list.push_back(i);
        }
    }
    //删除destroy_list中的进程
    while (!destroy_list.empty())
    {
        int de_id = destroy_list.front();
        if (p_list[de_id].p_valid == false) {
            return false;             //若编号为de_id的进程不存在，则销毁失败
        }
        else {
            p_list[de_id].p_valid = false; //让进程号为de_id的进程失效
            current_num--;            //现有进程数量减一
            int p = p_list[de_id].p_priority;
            if (p_list[de_id].p_status == "running") {
                current_running_process = -1;
            }
            else {
                if (p_list[de_id].p_status == "ready") {
                    ready_list[p].erase(remove(ready_list[p].begin(), ready_list[p].end(), de_id), ready_list[p].end());//从相应优先级的ready_list中移除进程号为id的PCB
                }
                else {
                    int b_id = p_list[de_id].block_resource_id;
                    //从相应优先级的block_list中移除进程号为de_id的PCB
                    r_list[b_id].wait_list[p].erase(remove(r_list[b_id].wait_list[p].begin(), r_list[b_id].wait_list[p].end(), de_id), r_list[b_id].wait_list[p].end());
                }
            }
            for (int j = 0; j < 4; ++j) {
                release_resource(j, p_list[de_id].occupied_resources[j]);//释放进程de_id的资源
            }
            p_list[de_id].p_id = -1;
            p_list[de_id].create_id = -1;
            p_list[de_id].block_resource_id = -1, p_list[de_id].r_need = 0;
            p_list[de_id].p_name = "";
            p_list[de_id].p_status = "";
            p_list[de_id].p_priority = -1;
            p_list[de_id].parent = -1;
            while (!p_list[de_id].child_list.empty()) {  //清空子进程id号
                p_list[de_id].child_list.pop_front();
            }
        }
        destroy_list.pop_front();     //出队列
    }
    return true;
}
int request_resource(int id, int req) {
    if (current_running_process == 0) {
        return -2;
    }
    if (current_running_process == -1) {
        return -1;
    }
    else {
        if (r_list[id].r_remain >= req) {
            p_list[current_running_process].occupied_resources[id] += req;
            r_list[id].r_remain -= req;
            return 1;
        }
        else {
            p_list[current_running_process].block_resource_id = id;
            p_list[current_running_process].r_need += req;
            p_list[current_running_process].p_status = "blocked";
            int p = p_list[current_running_process].p_priority;
            r_list[id].wait_list[p].push_back(current_running_process);
            current_running_process = -1;
            return 0;
        }
    }
}
void reset() {
    current_running_process = -1;
    current_num = 0;
    create_num = 0;
    for (int i = 0; i < MAX_PROCESS_NUM; ++i) {
        p_list[i].p_id = -1;
        p_list[i].create_id = -1;
        p_list[i].p_valid = false;
        p_list[i].p_name = "";
        p_list[i].p_status = "";
        p_list[i].p_priority = -1;
        for (int j = 0; j < 4; ++j) {
            p_list[i].occupied_resources[j] = 0;
        }
        p_list[i].block_resource_id = -1, p_list[i].r_need = 0;
        p_list[i].parent = -1;
        while (!p_list[i].child_list.empty()) {
            p_list[i].child_list.pop_front();
        }
    }
    for (int i = 0; i < 4; ++i) {
        r_list[i].r_id = -1;
        r_list[i].r_valid = false;
        r_list[i].r_name = "";
        r_list[i].r_initial = 0;
        r_list[i].r_remain = 0;
        for (int j = 0; j < 3; ++j) {
            while (!r_list[i].wait_list[j].empty()) {
                r_list[i].wait_list[j].pop_front();
            }
        }
    }
    while (!run_list.empty()) {
        run_list.pop_back();
    }
    for (int i = 0; i < 3; i++)
    {
        while (!ready_list[i].empty()) {
            ready_list[i].pop_back();
        }
    }
}