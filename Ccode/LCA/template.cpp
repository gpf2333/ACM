#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50000 + 5;
struct Edge{
    int to, next, w;
}edge[maxn << 1];
int tot, head[maxn];
vector<int>sp;
int dep[maxn], dfn[maxn];
int dist[maxn];
pair<int, int>dp[21][maxn << 1];
void init(int n){
    tot = 0;
    for(int i = 0; i <= n; ++i){
        head[i] = -1;
        dep[i] = dist[i] = 0;
    }
    sp.clear();
}

inline void addedge(int u, int v, int w){
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int u, int fa){
    dep[u] = dep[fa] + 1;
    dfn[u] = sp.size();
    sp.push_back(u);
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == fa) continue ;
        dist[v] = dist[u] + edge[i].w;
        dfs(v, u);
        sp.push_back(u);
    }
}

void initrmq(){
    int n = sp.size();
    for(int i = 0; i < n; ++i){
        dp[0][i] = {dfn[sp[i]], sp[i]};
    }
    for(int i = 1; (1 << i) <= n; ++i){
        for(int j = 0; j + (1 << i) - 1 < n; ++j){
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int lca(int u, int v){
    int l = dfn[u], r = dfn[v];
    if(l > r) swap(l, r);
    int k = 0;
    //while((1 << (k + 1)) <= (r - l + 1)) ++k;
    k = 31 - __builtin_clz(r - l + 1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]).second;
}

int main(){
    int T, n, m;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d", &n, &m);
        init(n);
        for(int i = 1; i < n; ++i){
            int u, v, w;
            scanf("%d%d%d",&u,&v,&w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        dfs(1, 0);
        initrmq();
        while(m--){
            int u, v;
            scanf("%d%d",&u,&v);
            printf("%d\n", dist[u] + dist[v] - 2 * dist[lca(u, v)]);
        }
    }
    return 0;
}

