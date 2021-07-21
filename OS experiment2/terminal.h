#pragma once
/*声明函数*/
#include"parameter.h"
#include"datastructure.h"
#include"kernel.h"
bool resource_display(int id);
bool process_display(int id);
void list_all_process();
void list_all_resource();
void list_all_run();
void push_running_process();
void show_running_process();
void show_ready_process();
void show_block_process();
vector<int> search_process(string p_name);  //将查询的进程放入队列中
int search_resource(string r_name);
void out_run_file(string file_path);
void shell_command();
void shell_file();
void shell();

/*定义函数*/
bool resource_display(int id) {
    if (id <= -1 || id >= 4) {
        printf("\033[0;37;40m输入的资源序号超出范围，无效！\n");
        return false;
    }
    if (r_list[id].r_valid == false) {
        printf("\033[0;37;40m该资源是无效资源，资源序号为：%d\n", r_list[id].r_id);
        return false;
    }
    else {
        printf("\033[0;37;40m该资源是有效资源，资源序号为：%d\n", r_list[id].r_id);
        printf("\033[0;37;40m该资源名称为：%s\n", r_list[id].r_name.c_str());
        printf("\033[0;37;40m该资源初始数量为：%d\n", r_list[id].r_initial);
        printf("\033[0;37;40m该资源剩余数量为：%d\n", r_list[id].r_remain);
        for (int i = 0; i < 3; ++i) {
            printf("\033[0;37;40m因请求不到该资源而阻塞的优先级为%d的进程数量为%d", i, r_list[id].wait_list[1].size());
            if (!r_list[id].wait_list[i].empty()) {
                printf("\033[0;37;40m, 阻塞进程序号依次为：");
                for (list<int>::iterator it = r_list[id].wait_list[i].begin(); it != r_list[id].wait_list[i].end(); ++it) {
                    printf("%d ", *it);
                }
            }
            printf("\n");
        }
        return true;
    }
}
bool process_display(int id) {
    if (id <= -1 || id >= 20) {
        printf("进程序号超出范围，无效！\n");
        return false;
    }
    if (p_list[id].p_valid == false) {
        printf("该进程是无效进程，进程序号为：%d\n", p_list[id].p_id);
        return false;
    }
    else {
        printf("该进程是有效进程，进程编号为：%d\n", p_list[id].p_id);
        printf("该进程的创建序号为：%d\n", p_list[id].create_id);
        printf("该进程状态为：%s\n", p_list[id].p_status.c_str());
        printf("该进程名称为：%s\n", p_list[id].p_name.c_str());
        printf("该进程的优先级为：%d\n", p_list[id].p_priority);
        printf("该进程占用资源情况如下：\n");
        for (int i = 0; i < 4; ++i) {
            printf("              ");
            printf("该进程资源%s占有量为：%d\n", r_list[i].r_name, p_list[id].occupied_resources[i]);
        }
        if (p_list[id].p_status == "block") {    //如果该进程处于阻塞态
            printf("\033[0;37;40m引起该进程阻塞的资源为R%d，还需要资源R%d的数量为%d\n", p_list[id].block_resource_id, p_list[id].block_resource_id, p_list[id].r_need);
        }
        if (p_list[id].parent == -1) {
            printf("\033[0;37;40m该进程没有父进程\n");
        }
        else {
            printf("\033[0;37;40m该进程的父进程进程序号是：%d\n", p_list[id].parent);
        }
        if (p_list[id].child_list.empty()) {  //若子进程队列为空则给出提示信息
            printf("\033[0;37;40m该进程没有子进程\n");
        }
        else {
            printf("\033[0;37;40m该进程的子进程有%d个，进程序号为：", p_list[id].child_list.size());
            for (list<int>::iterator it = p_list[id].child_list.begin(); it != p_list[id].child_list.end(); ++it) {
                printf("%d, ", *it);
            }
            printf("\n");
        }
        return true;
    }
}
void list_all_process() {
    printf("\033[0;37;40m==============================\n");
    if (current_num == 0) {
        printf("\033[0;37;40m该系统中目前没有有效进程\n");
    }
    else {
        printf("\033[0;37;40m目前有%d个有效进程，各进程信息如下[p_id, p_name]：\n", current_num);
        show_running_process();
        show_ready_process();
        show_block_process();
    }
    printf("\033[0;37;40m==============================\n");
}
void show_running_process() {
    printf("\033[0;32;40m------------------------------\n");
    if (current_running_process == -1) {
        printf("没有正在运行的进程\n");
    }
    else {
        printf("正在运行的进程为[p_id, p_name]：[%d, %s]\n", current_running_process, p_list[current_running_process].p_name.c_str());
    }
    printf("\033[0;32;40m------------------------------\n");
}
void list_all_resource() {
    printf("\033[0;37;40m==============================\n");
    for (int i = 0; i < 4; ++i) {
        resource_display(i);
        if (i < 3) {
            printf("------------------------------\n");
        }
    }
    printf("\033[0;37;40m==============================\n");
}
void list_all_run() {
    printf("\033[0;37;40m===============================================================\n");
    if (run_list.empty()) {
        printf("截止目前没有运行的进程\n");
    }
    else {
        printf("所有的运行进程为：");
        for (int i = 0; i < run_list.size(); ++i) {
            if (i < run_list.size() - 1) {
                printf("[%d, %s], ", run_list[i].first, run_list[i].second.c_str());
            }
            else {
                printf("[%d, %s]", run_list[i].first, run_list[i].second.c_str());
            }
        }
        printf("\n");
    }
    printf("\033[0;37;40m===============================================================\n");
}
void push_running_process() {
    if (current_running_process != -1) {
        int r = current_running_process;
        run_list.push_back(pair<int, string>(p_list[r].create_id, p_list[r].p_name));
    }
    return;
}
void show_ready_process() {
    printf("\033[0;33;40m------------------------------\n");
    for (int i = 0; i < 3; ++i) {
        if (!ready_list[i].empty()) {
            printf("优先级为%d的就绪队列中进程数量为%d，进程为：", i, ready_list[i].size());
            for (int j = 0; j < ready_list[i].size(); ++j) {
                printf("[%d, %s] ", ready_list[i][j], p_list[ready_list[i][j]].p_name.c_str());
            }
            printf("\n");
        }
        else {
            printf("优先级为%d的就绪队列为空\n", i);
        }
    }
    printf("\033[0;33;40m------------------------------\n");
    return;
}
void show_block_process() {
    printf("\033[0;31;40m------------------------------\n");
    for (int i = 0; i < 4; ++i) {
        if (r_list[i].wait_list[2].empty() && r_list[i].wait_list[1].empty() && r_list[i].wait_list[0].empty()) {
            printf("资源%s的阻塞队列为空\n", r_list[i].r_name.c_str());
        }
        else {
            printf("资源%s的阻塞队列如下：\n", r_list[i].r_name.c_str());
            for (int j = 2; j >= 0; --j) {
                if (r_list[i].wait_list[j].empty()) {
                    printf("优先级为%d的阻塞队列为空\n", j);
                }
                else {
                    printf("优先级为%d的阻塞队列为：", j);
                    for (list<int>::iterator it = r_list[i].wait_list[j].begin(); it != r_list[i].wait_list[j].end(); ++it) {
                        printf("[%d, %s]", *it, p_list[*it].p_name.c_str());
                    }
                    printf("\n");
                }
            }
        }

    }
    printf("\033[0;31;40m------------------------------\n");
    return;
}
vector<int> search_process(string name) {
    vector<int> result_list;
    for (int i = 0; i < MAX_PROCESS_NUM; ++i) {
        if (p_list[i].p_name == name) {
            result_list.push_back(i);
        }
    }
    return result_list;
}

int search_resource(string r_name) {
    if (r_map.find(r_name) == r_map.end()) {
        return -1;    //没找到
    }
    else {
        return r_map[r_name];
    }
}
void out_run_file(string file_path) {
    ofstream out_file;
    out_file.open(file_path);
    out_file << "=============================================" << endl;
    out_file << "所有的运行进程为[create_id, p_name]：" << endl;
    for (int i = 0; i < run_list.size(); ++i) {
        out_file << "[" << run_list[i].first << "," << " " << run_list[i].second << "]" << endl;
    }
    out_file << "=============================================" << endl;
}
void shell_command() {
    printf("您可以输入'help'查看所有指令\n");
    string cmd;
    do {
        printf("\033[0;37;40mshell_command>");
        cin >> cmd;
        string p_name, r_name;
        string file_path;
        int priority;
        int r_need;
        int r_rel;   //释放的资源量
        if (cmd == "init") {
            create_process("init", 0);
            init();
            printf("\033[0;32;40m成功：资源初始化成功！\n");
            scheduler();
            push_running_process();
        }
        else if (cmd == "cr") {
            cin >> p_name >> priority;
            if (priority > 2 || priority < 0) {
                printf("\033[0;31;40m错误：优先级不正确\n");
                continue;
            }
            if (current_num == MAX_PROCESS_NUM) {
                printf("\033[0;31;40m失败：进程池已满，无法创建新进程\n");
                continue;
            }
            vector<int> search_result;
            search_result = search_process(p_name);
            if (search_result.empty()) {
                create_process(p_name, priority);
                scheduler();
                push_running_process();
                printf("\033[0;32;40m成功：您已成功创建进程名为%s的进程\n", p_name.c_str());
            }
            else {
                printf("\033[0;33;40m警告：进程名为%s的进程已经存在\n",p_name.c_str());
                string if_create;
                do {
                    printf("\033[0;37;40您确定要创建吗？[Y/N]：");
                    cin >> if_create;
                } while (if_create != "Y" && if_create != "N");
                if (if_create == "N") {
                    continue;  //如果输入N则跳过此次循环
                }
                else {
                    create_process(p_name, priority);
                    scheduler();
                    push_running_process();
                    printf("\033[0;32;40m成功：您已成功创建进程名为%s的进程\n", p_name.c_str());
                }
            }
        }
        else if (cmd == "de") {
            cin >> p_name;
            vector<int> search_result;
            search_result = search_process(p_name);
            if (search_result.empty()) {
                printf("\033[0;31;40m错误：删除的进程不存在\n");
                continue;  //执行下一次循环
            }
            else if (search_result.size() == 1) {
                destroy_process(search_result.front());
                scheduler();
                push_running_process();
                printf("\033[0;32;40m成功：成功删除该进程\n");
            }
            else {
                printf("\033[0;37;40进程名为%s的进程有%d个，如下所示[p_id, p_name]：\n", p_name.c_str(), search_result.size());
                for (int i = 0; i < search_result.size(); ++i) {
                    printf("[%d, %s]\n", p_list[i].p_id, p_list[i].p_name.c_str());
                }
                int delete_id;
                vector<int>::iterator it;
                do {
                    printf("\033[0;37;40您想要删除哪一个，请输入要删除的进程编号：");
                    cin >> delete_id;
                    it = find(search_result.begin(), search_result.end(), delete_id);
                } while (it == search_result.end());//如果没有找到则持续输入
                destroy_process(delete_id);
                scheduler();
                push_running_process();
                printf("\033[0;32;40m成功：成功删除该进程\n");
            }
        }
        else if (cmd == "req") {
            cin >> r_name >> r_need;
            if (r_map.find(r_name) == r_map.end()) {
                printf("\033[0;31;40m错误：资源%s不存在\n", r_name.c_str());
                continue;
            }
            if (r_need < 0) {
                printf("\033[0;31;40m错误：资源申请量为负数\n");
                continue;
            }
            int ret = request_resource(r_map[r_name], r_need);
            if (ret == -2) {
                printf("\033[0;31;40m错误：初始进程无法申请资源\n");
                continue;
            }
            if (ret == -1) {
                printf("\033[0;31;40m错误：当前没有运行进程\n");
                continue;
            }
            else if (ret == 0) {
                printf("\033[0;33;40m警告：申请资源超出已有资源，运行进程已阻塞\n");
            }
            else {
                printf("\033[0;32;40m成功：已成功为当前运行进程申请资源\n");
            }
            scheduler();
            push_running_process();
        }
        else if (cmd == "rel") {
            cin >> r_name >> r_rel;
            if (r_map.find(r_name) == r_map.end()) {
                printf("\033[0;31;40m错误：资源%s不存在\n", r_name.c_str());
                continue;
            }
            if (r_rel < 0) {
                printf("\033[0;31;40m错误：资源释放量为负数\n");
                continue;
            }
            if (!release_resource(r_map[r_name], r_rel)) {
                printf("\033[0;31;40m失败：该资源是无效资源！\n");
                continue;
            }
            scheduler();
            push_running_process();
        }
        else if (cmd == "to") {
            if (!time_out()) {
                printf("\033[0;31;40m失败：此时没有正在运行的进程，无法执行超时中断\n");
            }
            else {
                scheduler();
                push_running_process();
                printf("\033[0;32;40m成功：已对正在运行的进程执行了超时中断\n");
            }
        }
        else if (cmd == "lap") {
            list_all_process();
        }
        else if (cmd == "lar") {
            list_all_resource();
        }
        else if (cmd == "schp") {
            cin >> p_name;
            vector<int> search_result;
            search_result = search_process(p_name);
            printf("\033[0;37;40==========================================\n");
            if (search_result.empty()) {
                printf("\033[0;31;40m错误：不存在名称为%s的进程\n", p_name.c_str());
            }
            else {
                printf("\033[0;37;40进程名称为%s的进程有%d个，详细信息如下：\n", p_name.c_str(), search_result.size());
                for (int i = 0; i < search_result.size(); ++i) {
                    process_display(search_result[i]);
                    if (i < search_result.size() - 1) {
                        printf("\033[0;37;40----------------------------------\n");
                    }
                }
            }
            printf("\033[0;37;40==========================================\n");
        }
        else if (cmd == "schr") {
            cin >> r_name;
            printf("\033[0;37;40==========================================\n");
            int ret = search_resource(r_name);
            if (ret == -1) {
                printf("\033[0;31;40m错误：不存在名称为%s的资源\n", r_name.c_str());
            }
            else {
                resource_display(ret);
            }
            printf("\033[0;37;40==========================================\n");
        }
        else if (cmd == "larun") {
            list_all_run();
        }
        else if (cmd == "orf") {
            cin >> file_path;
            out_run_file(file_path);
            printf("\033[0;32;40m成功：已将结果写入路径为%s的txt文件\n", file_path.c_str());
        }
        else if (cmd == "help") {
            printf("-init\t\t\t\t\t\t----创建初始进程并进行资源初始化\n");
            printf("-cr <process name><priority>\t\t\t----创建进程\n");
            printf("-de <process name>\t\t\t\t----删除进程\n");
            printf("-req <resource name> <# of units>\t\t----申请一定数量的资源\n");
            printf("-rel <resource name> <# of units>\t\t----释放一定数量的资源\n");
            printf("-to\t\t\t\t\t\t----中断正在运行的进程\n");
            printf("-lap\t\t\t\t\t\t----列出所有进程和它们的状态\n");
            printf("-lar\t\t\t\t\t\t----列出所有资源和它们的状态\n");
            printf("-schp <process name>\t\t\t\t----查询特定进程的信息\n");
            printf("-schr <resource name>\t\t\t\t----查询特定资源的信息\n");
            printf("-larun\t\t\t\t\t\t----列出所有系统中存在过的运行进程\n");
            printf("-orf\t\t\t\t\t\t----将系统中所有存在过的运行进程输出到文件\n");
            printf("-reset\t\t\t\t\t\t----重置系统\n");
            printf("-exit\t\t\t\t\t\t----推出命令行模式\n");
        }
        else if (cmd == "reset") {
            reset();
            printf("\033[0;37;40系统已重置\n");
        }
        else if (cmd == "exit") {
            break;
        }
        else {
            printf("\033[0;31;40m错误：命令输入不正确，请重新输入！\n");
        }
    } while (1);
    reset();   //重置系统
    printf("\033[0;37;40您已退出命令行模式\n");
    return;
}
void shell_file() {
    printf("\033[0;37;40您已进入文件模式\n");
    string if_exit;
    ifstream fin;
    string file_path;
    string cmd;
    printf("\033[0;37;40请输入要执行的文件路径：");
    cin >> file_path;
    fin.open(file_path);
    int row = 0;
    do {
        string p_name, r_name;
        int priority;
        int r_need;
        int r_rel;   //释放的资源量
        int de_id;   //删除进程的编号
        string rubbish;
        fin >> cmd;
        row++;
        if (cmd == "init") {
            create_process("init", 0);
            init();
            scheduler();
            push_running_process();
        }
        else if (cmd == "cr") {
            fin >> p_name >> priority;
            if (priority > 2 || priority < 0) {
                printf("\033[0;31;40m错误(第%d行)：优先级不正确\n",row);
                break;
            }
            if (current_num == MAX_PROCESS_NUM) {
                printf("\033[0;31;40m失败(第%d行)：进程池已满，无法创建新进程\n",row);
                break;
            }
            getline(fin, rubbish);
            create_process(p_name, priority);
            scheduler();
            push_running_process();
        }
        else if (cmd == "de") {
            fin >> p_name;
            int num = -1;
            for (int i = 0; i < MAX_PROCESS_NUM; ++i) {//删除第一个名称为p_name的进程
                if (p_list[i].p_name == p_name) {
                    num = i;
                }
            }
            if (num == -1) {
                printf("\033[0;31;40m错误(第%d行)：进程名称为%s的进程不存在\n", row, p_name.c_str());
                break;   //退出
            }
            else {
                destroy_process(num);
                scheduler();
                push_running_process();
            }
        }
        else if (cmd == "req") {
            fin >> r_name >> r_need;
            if (r_map.find(r_name) == r_map.end()) {
                printf("\033[0;31;40m错误(第%d行)：资源%s不存在\n", row, r_name.c_str());
                break;
            }
            if (r_need < 0) {
                printf("\033[0;31;40m错误(第%d行)：资源申请量为负数\n", row);
                break;
            }
            int ret = request_resource(r_map[r_name], r_need);
            if (ret == -2) {
                printf("\033[0;31;40m错误(第%d行)：初始进程无法申请资源\n", row);
                continue;
            }
            if (ret == -1) {
                printf("\033[0;31;40m错误(第%d行)：当前没有运行进程\n", row);
                break;
            }
            scheduler();
            push_running_process();
        }
        else if (cmd == "rel") {
            fin >> r_name >> r_rel;
            if (r_map.find(r_name) == r_map.end()) {
                printf("\033[0;31;40m错误(第%d行)：资源%s不存在\n", row, r_name.c_str());
                break;
            }
            if (r_rel < 0) {
                printf("\033[0;31;40m错误(第%d行)：资源释放量为负数\n", row);
                break;
            }
            if (!release_resource(r_map[r_name], r_rel)) {
                printf("\033[0;31;40m失败(第%d行)：该资源是无效资源！\n", row);
                break;
            }
            release_resource(r_map[r_name], r_rel);
            scheduler();
            push_running_process();
        }
        else if (cmd == "to") {
            if (!time_out()) {
                printf("\033[0;31;40m失败(第%d行)：此时没有正在运行的进程，无法执行超时中断\n", row);
            }
            else {
                scheduler();
                push_running_process();
            }
        }
        else if (cmd == "exit") {
            printf("\033[0;32;40m成功：文件成功执行\n");
        }
        else {
            printf("\033[0;31;40m错误(第%d行)：存在语法错误\n", row);
            break;
        }
    } while (cmd != "exit");
    list_all_run();
    printf("\n");
    fin.close();
    reset();      //重置系统
    printf("\033[0;37;40您已退出文件模式\n");
    return;
}
void shell() {
    printf("\033[0;37;40欢迎来到终端！\n");
    string shell_mode;
    string is_continue;
    do {
        do {
            printf("\033[0;37;40您想进入哪种模式进行操作,是文件(file)模式还是命令行(command)模式？[F/C]：");
            cin >> shell_mode;
        } while (shell_mode != "F" && shell_mode != "C");
        if (shell_mode == "F") {
            shell_file();
        }
        else {
            shell_command();
        }
        do {
            printf("\033[0;37;40您想继续在终端操作吗？[Y/N]：");
            cin >> is_continue;
        } while (is_continue != "Y" && is_continue != "N");
        if (is_continue == "N") {
            printf("\033[0;37;40您已退出终端\n");
            break;
        }
    } while (is_continue == "Y");
    return;
}