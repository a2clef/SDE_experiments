#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#define N 100 
#define maxx 9999999
#define minn -1
using namespace std;
typedef struct No
{
	int u, v, w;
	No(int a, int b, int c){ u = a, v = b, w = c; }
} No;
vector<No> T[N];
vector<int> topol;
int dist[N];
bool vis[N];

void topo(int now)
{
	if (!vis[now]) vis[now] = 1;
	for (unsigned int i = 0; i<T[now].size(); i++)
	{
		if (!vis[T[now][i].v]) topo(T[now][i].v);
	}
	topol.push_back(now);
}
void DAG(int n, int k)
{
	for (int i = 1; i <= n; i++) dist[i] = maxx;
	dist[k] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (unsigned int j = 0; j<T[i].size(); j++)
		{
			int to = T[i][j].v;
			if (dist[to]>dist[i] + T[i][j].w)	dist[to] = dist[i] + T[i][j].w;
		}
	}
	return;
}
int main()
{
	int m, n;
	cin >> n >> m;
	for (int i = 0; i<m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		T[u].push_back(No(u, v, w));
	}
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) if (!vis[i]) topo(i);
	for (int i = topol.size() - 1; i >= 0; i--) cout << topol[i] << " ";
	cout << endl;
	int k;
	cin >> k;
	DAG(n, k);
	for (int i = 1; i <= n; i++)	cout << k << " to " << i << " mincost:" << dist[i] << endl;
	cout << endl;
}


/*
7 11
1 2 7
1 4 5
2 4 9
2 3 8
2 5 7
4 5 -5
4 6 6
5 6 8
6 7 11
5 7 9
3 5 5


*/

