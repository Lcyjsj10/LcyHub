#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string data;
    Node *next;
    Node(string data = "", Node *next = nullptr) : data(data), next(next) {}
    void insert(Node *node)
    {
        node->next = this->next;
        this->next = node;
        return;
    }
};

class hashtable3
{
private:
    vector<Node> data;
    int cnt;
    int hash_map(string s)
    {
        int seed = 131, hash = 0;
        for (int i = 0; s[i]; i++)
        {
            hash = seed * hash + s[i];
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
        hashtable3 h(n);
        for (int i = 0; i < data.size(); i++)
        {
            Node *p = data[i].next;
            while (p)
            {
                h.insert(p->data);
                p = p->next;
            }
        }
        return;
    }

public:
    hashtable3(int n = 100) : data(n), cnt(0) {}
    void insert(string &s)
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
    bool find(string s)
    {
        int ind = hash_map(s) % data.size();
        conflict_deal(ind, s);
        Node *p = &data[ind];
        while (p->next && p->next->data != s)
        {
            p = p->next;
        }
        return p->next != nullptr;
    }
};

int main()
{
    int op;
    string s;
    hashtable3 h;
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
        default:
            break;
        }
    }
}
