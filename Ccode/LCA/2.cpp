#include<bits/stdc++.h>
using namespace std;
const int INF = 1 << 30;
const int maxn = 50000 + 5;
struct Edge{
    int to, w, next;
}edge[maxn << 1];
int tot, head[maxn];
int fa[maxn], dist[maxn];
int ans[maxn];
bool vis[maxn];
vector<pair<int, int> >q[maxn];
void init(int n){
    tot = 0;
    for(int i = 0; i <= n; ++i){
        q[i].clear();
        fa[i] = i, head[i] = -1, dist[i] = 0, vis[i] = 0;
    }
}

inline void addedge(const int u, const int v, const int w){
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}

inline void addquery(int id, int u, int v){
    q[u].emplace_back(v, id);
    q[v].emplace_back(u, id);
}

int Find(int x){
    return (x == fa[x]) ? x : (fa[x] = Find(fa[x]));
}

void tarjan(int u){
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue ;
        dist[v] = dist[u] + edge[i].w;
        tarjan(v);
        fa[v] = u;
    }
    for(int i = 0; i < q[u].size(); ++i){
        int v = q[u][i].first, id = q[u][i].second;
        if(vis[v]){
            ans[id] = min(ans[id], dist[u] + dist[v] - 2 * dist[Find(v)]);
        }
    }
    //vis[u] = 2;
}

int main(){
    int T, n, m, u, v, w;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n, &m);
        init(n);
        for(int i = 1; i < n; ++i){
            scanf("%d%d%d",&u,&v,&w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        for(int i = 0; i < m; ++i){
            scanf("%d%d",&u,&v);
            if(u == v){
                ans[i] = 0;
            }else{
                ans[i] = INF;
                addquery(i, u, v);
            }
        }
        tarjan(1);
        for(int i = 0; i < m; ++i){
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}