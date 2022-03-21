#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "graph.h"

set<int> B[MAXN];
int tot;
set<int, less<int>> Q; //用于存放非空的桶编号

void delta_stepping(graph &G, int s, int delta);
void relax(graph &G, int delta, set<int> &V, edge_kind e_kind);

void delta_stepping(graph &G, int s, int delta)
{
    fill(dis, dis + MAXN, inf);
    memset(father, -1, sizeof(father));
    tot = 0;
    dis[s] = 0;
    B[0].insert(s);
    Q.insert(0);
    tot++;
    while (tot != 0)
    {
        int index = *Q.begin();
        set<int> R;
        while (!B[index].empty())
        {
            set_union(R.begin(), R.end(), B[index].begin(), B[index].end(), inserter(R, R.begin()));
            set<int> S(B[index]);
            tot -= B[index].size();
            B[index].clear();
            Q.erase(index);
            relax(G, delta, S, light);
        }
        relax(G, delta, R, heavy);
    }
}
void relax(graph &G, int delta, set<int> &V, edge_kind e_kind)
{
    switch (e_kind)
    {
    case light:
        for (set<int>::iterator it = V.begin(); it != V.end(); it++)
        {
            for (int i = 0; i < G.edge_list[*it].size(); i++)
            {
                edge p = G.edge_list[*it][i];
                if (p.w <= delta)
                {
                    if (dis[p.to] > dis[*it] + p.w)
                    {
                        int bucket_index = dis[p.to] / delta;
                        if (bucket_index < 100)
                        {
                            if (B[bucket_index].find(p.to) != B[bucket_index].end())
                            {
                                B[bucket_index].erase(p.to);
                                tot--;
                                if (B[bucket_index].empty())
                                {
                                    Q.erase(bucket_index);
                                }
                            }
                        }
                        dis[p.to] = dis[*it] + p.w;
                        father[p.to] = *it;
                        bucket_index = dis[p.to] / delta;
                        if (B[bucket_index].find(p.to) == B[bucket_index].end())
                        {
                            B[bucket_index].insert(p.to);
                            tot++;
                            Q.insert(bucket_index);
                        }
                    }
                }
            }
        }
        break;
    default:
        for (set<int>::iterator it = V.begin(); it != V.end(); it++)
        {
            for (int i = 0; i < G.edge_list[*it].size(); i++)
            {
                edge p = G.edge_list[*it][i];
                if (p.w > delta)
                {
                    if (dis[p.to] > dis[*it] + p.w)
                    {
                        int bucket_index = dis[p.to] / delta;
                        if (bucket_index < 100)
                        {
                            if (B[bucket_index].find(p.to) != B[bucket_index].end())
                            {
                                B[bucket_index].erase(p.to);
                                tot--;
                                if (B[bucket_index].empty())
                                {
                                    Q.erase(bucket_index);
                                }
                            }
                        }
                        dis[p.to] = dis[*it] + p.w;
                        father[p.to] = *it;
                        bucket_index = dis[p.to] / delta;
                        if (B[bucket_index].find(p.to) == B[bucket_index].end())
                        {
                            B[bucket_index].insert(p.to);
                            tot++;
                            Q.insert(bucket_index);
                        }
                    }
                }
            }
        }
        break;
    }
}