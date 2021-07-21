#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string data; //存储的字符串
    int cnt;     //字符串出现的次数
    Node *next;
    Node(string data = "", int cnt = 0, Node *next = nullptr) : data(data), cnt(cnt), next(next) {}
    void insert(Node *node)
    {
        node->next = this->next;
        this->next = node;
        return;
    }
};

class hash_table
{
private:
    vector<Node> data;
    int cnt;
    int hash_map(string s)
    {
        int hash = 0, seed = 131;
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
        hash_table h(n);
        for (int i = 0; i < data.size(); i++)
        {
            Node *p = data[i].next;
            while (p)
            {
                h.insert(p->data);
            }
        }
        *this = h;
        return;
    }

public:
    hash_table(int n = 100) : data(n), cnt(0) {}
    void insert(string s)
    {
        int ind = hash_map(s) % data.size();
        conflict_deal(ind, s);
        Node *p = &data[ind];
        while (p->next && p->next->data != s)
        {
            p = p->next;
        }
        if (p->next == nullptr)
        {
            p->insert(new Node(s));
            cnt++;
            if (cnt > data.size() * 3)
            {
                expand();
            }
        }
        return;
    }
    int search(string s)
    {
        int ind = hash_map(s) % data.size();
        conflict_deal(ind, s);
        Node *p = &data[ind];
        while (p->next && p->next->data != s)
        {
            p = p->next;
        }
        if (p->next == nullptr)
        {
            return -1;
        }
        else if (p->next->cnt == 0)
        {
            p->next->cnt++;
            return 0;
        }
        return p->next->cnt;
    }
};

int main()
{
    int n, m;
    string s;
    hash_table h;
    vector<string> result;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        h.insert(s);
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> s;
        int signal = h.search(s);
        switch (signal)
        {
        case -1:
            result.push_back("WRONG");
            break;
        case 0:
            result.push_back("OK");
            break;
        case 1:
            result.push_back("REPEAT");
            break;
        }
    }
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
}