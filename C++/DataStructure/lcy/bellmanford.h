#pragma once
#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

bool bellmanford(graph &G, int s);

bool bellmanford(graph &G, int s)
{
    fill(dis, dis + MAXN, inf);
    dis[s] = 0;
    fill(father, father + MAXN, -1);
    bool flag; //to judge if there is a cycle
    for (int i = 0; i < G.n; i++)
    {
        flag = false;
        for (int j = 0; j < G.n; j++) //这里源点问题要注意
        {
            for (int k = 0; k < G.edge_list[j].size(); k++)
            {
                edge p = G.edge_list[j][k];
                if (dis[p.to] > dis[j] + p.w)
                {
                    dis[p.to] = dis[j] + p.w;
                    father[p.to] = j;
                    flag = true;
                }
            }
        }
        if (!flag)
        {
            break;
        }
    }
    return flag;
}