#pragma once
#include <bits/stdc++.h>
#include "graph.h"
using namespace std;

void print_dis(graph &G, int s);
void print_shortest_path(graph &G, int s);

void print_dis(graph &G, int s)
{
    for (int i = 1; i <= G.n; ++i)
    {
        cout << i << ": " << dis[i] << endl;
    }
}

void print_shortest_path(graph &G, int s)
{
    for (int i = 1; i <= G.n; ++i)
    {
        cout << i << ": ";
        cout << i;
        int t = father[i];
        while (t != -1)
        {
            cout << " <- " << t;
            t = father[t];
        }
        cout << " " << dis[i] << endl;
    }
}