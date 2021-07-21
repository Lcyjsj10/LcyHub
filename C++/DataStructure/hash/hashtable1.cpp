#include <bits/stdc++.h>
using namespace std;

class hashtable1
{
private:
    vector<string> data;
    vector<bool> flag;
    int cnt;
    int hash_map(string s) //哈希映射
    {
        int seed = 131, hash = 0;
        for (int i = 0; s[i]; i++)
        {
            hash = seed * hash + s[i];
        }
        return hash & 0x7fffffff;
    }
    void conflict_deal(int &ind, string &s) //冲突处理函数
    {
        int t = 1; //冲突处理次数
        while (flag[ind] && data[ind] != s)
        {
            ind += t * t;
            t++;
            ind % data.size();
        }
        return;
    }
    void expand()
    {
        int n = data.size() * 2;
        hashtable1 h(n);
        for (int i = 0; i < data.size(); i++)
        {
            if (flag[i] == false)
            {
                continue;
            }
            h.insert(data[i]);
        }
        *this = h;
        return;
    }

public:
    hashtable1(int n = 100) : data(n), flag(n), cnt(0) {}
    void insert(string &s)
    {
        int ind = hash_map(s) % data.size(); //计算哈希值
        conflict_deal(ind, s);               //冲突处理
        if (flag[ind] == false)
        {
            data[ind] = s;
            flag[ind] = true;
            cnt++;
            if (cnt * 100 > data.size() * 75)
            {
                expand();
            }
        }
    }
    bool find(string s)
    {
        int ind = hash_map(s) % data.size(); //计算哈希值
        conflict_deal(ind, s);               //冲突处理
        return flag[ind];
    }
};

int main()
{
    int op;
    string s;
    hashtable1 h;
    while (cin >> op >> s)
    {
        switch (op)
        {
        case 1:
            h.insert(s);
            break;
        case 2:
            cout << "find"
                 << " " << s << ":" << h.find(s) << endl;
        }
    }
}