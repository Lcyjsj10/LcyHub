#include <bits/stdc++.h>
using namespace std;

class trie_node
{
public:
    int cnt;
    trie_node *son[128]; //ASCII码有128个
    trie_node() : cnt(0)
    {
        for (int i = 0; i < 128; i++)
        {
            son[i] = nullptr;
        }
    }
};

class trie
{
private:
    trie_node *root;

public:
    trie()
    {
        this->root = new trie_node();
    }
    void insert(string s)
    {
        trie_node *p = this->root;
        for (int i = 0; s[i]; i++)
        {
            if (p->son[s[i]] == nullptr)
            {
                p->son[s[i]] = new trie_node();
            }
            p = p->son[s[i]];
        }
        p->cnt++; //在树叶处存储单词出现的次数
    }
    int search(string s)
    {
        trie_node *p = root;
        for (int i = 0; s[i]; i++)
        {
            p = p->son[s[i]];
        }
        if (p != nullptr)
        {
            return p->cnt;
        }
        return 0;
    }
    ~trie();
};

trie::~trie()
{
    delete root;
}

int main()
{
    int op;
    string s;
    trie t;
    while (cin >> op >> s)
    {
        switch (op)
        {
        case 1:
            t.insert(s);
            break;
        case 2:
            cout << "find"
                 << " " << s << ":" << t.search(s) << endl;
            break;
        }
    }
}