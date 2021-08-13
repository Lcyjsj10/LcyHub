#include <bits/stdc++.h>
using namespace std;

const int inf = 0x7fffffff;
const int MAXN = 1e5;
const int MAXM = 1e6;

int dis[MAXN];
int father[MAXN];
bool vis[MAXN];
set<int> B[MAXN];
int tot;
set<int, less<int>> Q; //用于存放非空的桶编号

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

void print_dis(graph &G, int s);
void delta_stepping(graph &G, int s, int delta);
void relax(graph &G, int delta, set<int> &V, edge_kind e_kind);
void print_shortest_path(graph &G, int s);
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
    delta_stepping(G, s, delta);
    // print_dis(G, s);
    print_shortest_path(G, s);
}

void print_dis(graph &G, int s)
{
    for (int i = 1; i <= G.n; ++i)
    {
        cout << i << ": " << dis[i] << endl;
    }
}
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