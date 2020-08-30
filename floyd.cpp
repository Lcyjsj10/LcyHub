//floyd算法
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 100
int dis[MAXN][MAXN];
int n, m;//n,m分别是图的顶点个数,边数
template<class T>
T min(T a, T b)
{
	return a < b ? a : b;
}
inline void floyd()
{
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	return;
}

int main() 
{
	memset(dis, 0x3f, sizeof(dis));
	cin >> n >> m;
	int u, v, w;
	for (int i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		dis[u][v] = dis[v][u] = min(dis[u][v], w);
	}
	floyd();
	int q;
	cin >> q;
	while (q)
	{
		cin >> u >> v;
		cout << dis[u][v] << endl;
		q--;
	}
}

