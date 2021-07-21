#include <bits/stdc++.h>
using namespace std;

class hashtable2
{
private:
    vector<string> data;
    vector<bool> flag;
    set<string> buff;
    int cnt;
    int hash_map(string s)
    {
        int seed = 131, hash = 0;
        for (int i = 0; s[i]; i++)
        {
            hash = hash * seed + s[i];
        }
        return hash & 0x7fffffff;
    }
    void conflict_deal(int &ind, string &s)
    {
        return;
    }
    void expand()
    {
        int n = data.size() * 2;
        hashtable2 h(n);
        for (int i = 0; i < data.size(); i++)
        {
            if (flag[i] == false)
            {
                continue;
            }
            h.insert(data[i]);
        }
        for (auto x : buff)
        {
            h.insert(x);
        }
        *this = h;
        return;
    }

public:
    hashtable2(int n = 100) : data(n), flag(n), cnt(0) {}
    void insert(string s)
    {
        int ind = hash_map(s) % data.size();
        conflict_deal(ind, s);
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
        else if (data[ind] != s)
        {
            buff.insert(s);
        }
        return;
    }
    bool find(string s)
    {
        int ind = hash_map(s) % data.size();
        conflict_deal(ind, s);
        if (flag[ind] == false)
        {
            return false;
        }
        if (flag[ind] == true && data[ind] == s)
        {
            return true;
        }
        return buff.find(s) != buff.end();
    }
};

int main()
{
    int op;
    string s;
    hashtable2 h;
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
            break;
        }
    }
}