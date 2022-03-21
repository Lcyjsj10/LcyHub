#include <bits/stdc++.h>
#include <chrono>
#include <time.h>
using namespace std;
#include "graph.h"
#include "delta_stepping.h"
#include "bellmanford.h"
#include "display.h"

void file_input2(string file_path)
{
    fstream fin;
    fin.open(file_path);
    int n, m;
    int u, v, w;
    fin >> n >> m;
    while (true)
    {
        fin >> u >> v >> w;
        cout << u << " " << v << " " << w << endl;
        if (fin.eof())
        {
            break;
        }
    }
}

int main()
{
    graph G;
    //    G.input();
    string file_path;
    cout << "Please input the file path:";
    cin >> file_path;
    // G.file_input(file_path);
    G.file_input2(file_path);
    // G.display();
    cout << "Please input the delta:";
    int delta;
    cin >> delta;
    cout << "Please input the source point:";
    int s;
    cin >> s;
    auto start_time = chrono::high_resolution_clock::now();
    bellmanford(G, s);
    auto end_time = chrono::high_resolution_clock::now();
    printf("The running time is %.2f microseconds\n", chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1e6);
    start_time = chrono::high_resolution_clock::now();
    delta_stepping(G, s, delta);
    end_time = chrono::high_resolution_clock::now();
    printf("The running time is %.2f microseconds\n", chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1e6);
}
