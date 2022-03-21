#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int inf = 100;
const int MAXN = 1e5;
const int MAXM = 1e6;

int dis[MAXN];
int father[MAXN];
bool vis[MAXN];
struct edge
{
    int to; //弧头
    int w;  //边权
    edge(int to, int w)
    {
        this->to = to;
        this->w = w;
    }
    bool operator<(const edge &obj) const
    {
        return w > obj.w;
    }
};

enum edge_kind
{
    light = 1,
    heavy
};
class graph
{
private:
public:
    int n; //点数
    int m; //边数
    vector<vector<edge>> edge_list;
    graph(int n = 0, int m = 0)
    {
        this->n = n;
        this->m = m;
        this->edge_list.resize(n + 1);
    }
    void input()
    {
        cout << "Please input the vertex number: ";
        cin >> this->n;
        cout << "Please input the edge number: ";
        cin >> this->m;
        edge_list.resize(n + 1);
        int u, v;
        int w;
        for (int i = 0; i < m; i++)
        {
            cout << "Please input the " << i + 1 << " th edge: ";
            cin >> u >> v >> w;
            add_edge(u, v, w);
        }
    }
    void file_input(string file_path)
    {
        ifstream fin;
        fin.open(file_path);
        fin >> this->n >> this->m;
        int u, v, w;
        while (true)
        {
            fin >> u >> v >> w;
            add_edge(u, v, w);
            if (fin.eof())
            {
                break;
            }
        }
        fin.close();
    }
    void file_input2(string file_path)
    {
        ifstream fin;
        fin.open(file_path);
        fin >> this->n >> this->m;
        int u, v;
        while (true)
        {
            fin >> u >> v;
            add_edge(u, v, 1);
            if (fin.eof())
            {
                break;
            }
        }
        fin.close();
    }
    void expand(int i)
    {
        if (this->edge_list.size() < i + 1)
        {
            this->edge_list.resize(i + 1);
            this->n = i;
        }
    }
    void add_edge(int u, int v, int w)
    {
        expand(u), expand(v);
        edge_list[u].push_back(edge{v, w});
    }
    void display()
    {
        cout << "vertex number is: " << this->n << endl;
        cout << "edge number is: " << this->m << endl;
        cout << "all the edges are:" << endl;
        for (int i = 1; i <= this->n; i++)
        {
            for (int j = 0; j < edge_list[i].size(); j++)
            {
                edge p = edge_list[i][j];
                cout << i << " -> " << p.to << " " << p.w << endl;
            }
        }
    }
    ~graph()
    {
        n = m = 0;
        edge_list.resize(0);
    }
};
