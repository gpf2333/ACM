#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 1e5 + 10;
vector<pair<int, int> >q[maxn];
int fa[maxn], dp[maxn], res[maxn];
bool vis[maxn];

struct Edge{
    int to, next;
}edge[maxn << 1];
int tot, head[maxn];

inline void addedge(int u, int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void init(int n){
    tot = 0;
    for(int i = 0; i <= n; ++i){
        q[i].clear();
        dp[i] = 0;
        vis[i] = 0;
        head[i] = -1;
        fa[i] = i;
    }
}

int Find(int x){
    return (x == fa[x]) ? x : (fa[x] = Find(fa[x]));
}

inline void addquery(int id, int u, int v){
    q[u].push_back(make_pair(v, id));
    q[v].push_back(make_pair(u, id));
}

void tarjian(int u){
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue ;
        tarjian(v);
        fa[v] = u;
    }
    for(int i = 0; i < q[u].size(); ++i){
        int v = q[u][i].first, id = q[u][i].second;
        if(vis[v]){
            res[id] = Find(v);
        }
    }
}

void dfs(int u){
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue ;
        dfs(v);
        dp[u] += dp[v];
    }
}

int main(){
    int n, m;
    while(~scanf("%d%d",&n,&m)){
        int u, v;
        init(n);
        for(int i = 1; i < n; ++i){
            scanf("%d%d",&u,&v);
            addedge(u, v);
            addedge(v, u);
        }
        for(int i = 0; i < m; ++i){
            scanf("%d%d",&u,&v);
            ++dp[u], ++dp[v];
            if(u == v){
                res[i] = u;
            }else{
                addquery(i, u, v);
                addquery(i, v, u);
            }
        }
        tarjian(1);
        for(int i = 0; i < m; ++i){
            dp[res[i]] -= 2;
        }
        for(int i = 0; i <= n; ++i) vis[i] = 0;
        dfs(1);
        int ans = 0;
        for(int i = 2; i <= n; ++i){
            if(!dp[i]){
                ans += m;
            }else if(dp[i] == 1){
                ++ans;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}