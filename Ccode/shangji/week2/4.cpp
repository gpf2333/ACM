#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 100;
int G[maxn][maxn];
int dis[maxn], path[maxn];
bool vis[maxn];
int head[maxn];
void output(const int cur, const int n)
{
    printf("%d:\n", cur);
    printf("s   :");
    for (int i = 0; i <= n; ++i)
    {
        printf("%4d", i);
    }
    printf("\ndis :");
    for (int i = 0; i <= n; ++i)
    {
        if (dis[i] != INF)
            printf("%4d", dis[i]);
        else
            printf("%4s", "INF");
    }
    printf("\npath:");
    for (int i = 0; i <= n; ++i)
    {
        printf("%4d", path[i]);
    }
    printf("\n--------------------------------\n");
}

void dijkstra(const int s, const int n)
{
    for (int i = 0; i <= n; ++i)
    {
        vis[i] = 0;
        if (G[s][i] == INF)
        {
            dis[i] = INF, path[i] = -1;
        }
        else
        {
            dis[i] = G[s][i], path[i] = s;
        }
    }
    path[s] = -1, vis[s] = 1;
    output(s, n);
    for (int i = 0; i < n; ++i)
    {
        int Min = INF, cur = -1;
        for (int j = 0; j <= n; ++j)
        {
            if (!vis[j] && Min > dis[j])
            {
                Min = dis[j], cur = j;
            }
        }
        if (cur == -1)
            return;
        vis[cur] = 1;
        for (int j = 0; j <= n; ++j)
        {
            if (!vis[j] && dis[j] > dis[cur] + G[cur][j])
            {
                dis[j] = dis[cur] + G[cur][j];
                path[j] = cur;
            }
        }
        output(cur, n);
    }
}

void dfs(int s, int x)
{
    if (head[x] == -1)
        return;
    if (x != s)
    {
        dfs(s, head[x]);
    }
    printf("%4d", x);
}

int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m)
    {
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                G[i][j] = INF;
                if (i == j)
                    G[i][j] = 0;
            }
        }
        int u, v, w;
        for (int i = 0; i < m; ++i)
        {
            cin >> u >> v >> w;
            G[u][v] = w;
        }
        int s;
        cin >> s;
        dijkstra(s, n);
        for (int i = 0; i <= n; ++i)
            head[i] = -1;
        head[s] = s;
        for (int i = 0; i <= n; ++i)
        {
            if (dis[i] == INF)
                continue;
            for (int j = 0; j <= n; ++j)
            {
                if (i == j)
                    continue;
                if (dis[j] == INF)
                    continue;
                if (G[i][j] == INF)
                    continue;
                if (dis[i] > dis[j] && (dis[i] - dis[j]) == G[j][i])
                {
                    head[i] = j;
                }
                else if (dis[i] < dis[j] && (dis[j] - dis[i]) == G[i][j])
                {
                    head[j] = i;
                }
            }
        }
        printf("path: \n");
        for (int i = 0; i <= n; ++i)
        {
            if (i == s)
                continue;
            if (head[i] == -1)
                continue;
            dfs(s, i);
            printf("    dist: %d\n", dis[i]);
        }
    }
    return 0;
}

/*
5 11
0 1 45
0 2 50
0 3 15
1 2 5
1 4 20
1 5 15
3 0 10
3 1 10
3 4 79
4 1 20
4 5 20
0
*/