#include<bits/stdc++.h>
using namespace std;
const int maxn = 50000 + 100;
struct Edge{
    int to, next, w;
}edge[maxn << 1];
int tot, head[maxn];
vector<int>sp;
int dep[maxn], dfn[maxn], dist[maxn];
pair<int, int>dp[21][maxn << 1];
void init(int n){
    tot = 0;
    for(int i = 0; i <= n; ++i){
        head[i] = -1, dist[i] = 0;
    }
    sp.clear();
}

inline void addedge(int u, int v, int w){
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int u, int fa, int d){
    dep[u] = d;
    dfn[u] = sp.size();
    sp.push_back(u);
    for(int i = head[u];  ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == fa) continue ;
        dist[v] = dist[u] + edge[i].w;
        dfs(v, u, d + 1);
        sp.push_back(u);
    }
}

void initrmq(){
    int n = sp.size();
    for(int i = 0; i < n; ++i){
        dp[0][i] = make_pair(dfn[sp[i]], sp[i]);
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
    int k = 31 - __builtin_clz(r - l + 1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]).second;
}

int main(){
    int n;
    bool ok = false;
    while(~scanf("%d",&n)){
        init(n);
        int x, y, z, w;
        for(int i = 1; i < n; ++i){
            scanf("%d%d%d",&x,&y,&w);
            addedge(x, y, w);
            addedge(y, x, w);
        }
        dfs(0, -1, 1);
        initrmq();
        if(ok){
            puts("");
        }
        int m;
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&x,&y,&z);
            int ans = dist[x] + dist[y] + dist[z] - (dist[lca(x, y)] + dist[lca(x, z)] + dist[lca(y, z)]);
            printf("%d\n", ans);
        }
        ok = true;
    }
    return 0;
}