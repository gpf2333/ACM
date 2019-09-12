#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;
struct Edge{
    int to, next, w;
}edge[maxn << 1];

int n, m, root, total;
int head[maxn], tot;
int siz[maxn], maxson[maxn];
bool vis[maxn];
int dis[maxn];
int cnt[maxn];
bool mark[10000500];
bool ans[maxn];

struct Query{
    int id, k;
}query[maxn];

bool cmp(const Query &a, const Query &b){
    return a.k < b.k;
}

void init(int n){
    tot = 0, total = n;
    for(int i = 0; i <= n; ++i){
        head[i] = -1, vis[i] = 0;
    }
}

inline void addedge(int u, int v, int w){
    edge[tot] = {v, head[u], w};
    head[u] = tot++;
}

void getroot(int u, int fa){
    siz[u] = 1, maxson[u] = 0;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == fa || vis[v]) continue ;
        getroot(v, u);
        siz[u] += siz[v];
        maxson[u] = max(maxson[u], siz[v]);
    }
    maxson[u] = max(maxson[u], total - siz[u]);
    if(maxson[u] < maxson[root]) root = u;
}

void getdis(int u, int fa, int d){
    dis[++dis[0]] = d;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == fa || vis[v]) continue ;
        getdis(v, u, d + edge[i].w);
    }
}

void calc(int u){
    cnt[0] = 0;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue ;
        dis[0] = 0;
        getdis(v, u, edge[i].w);
        sort(dis + 1, dis + dis[0] + 1);
        for(int j = dis[0]; j; --j){ // note: j从大到小, 不能从小到大orz
            for(int k = m; k >= 1; --k){
                if(query[k].k >= dis[j]){
                    ans[query[k].id] |= mark[query[k].k - dis[j]];
                }else{
                    break ;
                }
            }
        }
        for(int j = 1; j <= dis[0]; ++j){
            cnt[++cnt[0]] = dis[j];
            mark[dis[j]] = 1;
        }
    }
    for(int i = 1; i <= cnt[0]; ++i){
        mark[cnt[i]] = 0;
    }
}

void solve(int u){
    mark[0] = 1;
    calc(u);
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue ;
        maxson[0] = total = siz[v];
        getroot(v, root = 0);
        solve(root);
    }
}

int main(){
    int u, v, w;
    scanf("%d%d", &n, &m);
    init(n);
    for(int i = 1; i < n; ++i){
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w);
        addedge(v, u, w);
    }
    for(int i = 1; i <= m; ++i){
        scanf("%d", &query[i].k);
        query[i].id = i;
    }
    sort(query + 1, query + m + 1, cmp);
    root = 0;
    maxson[root] = n;
    getroot(1, root);
    solve(root);
    for(int i = 1; i <= m; ++i){
        puts(ans[i] ? "AYE" : "NAY");
    }
    return 0;
}