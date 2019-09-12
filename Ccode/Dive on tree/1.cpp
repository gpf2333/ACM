#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int maxn = 10000 + 10;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to, next, w;
}edge[maxn << 1];

int n, k, root;
int head[maxn], tot;
int siz[maxn], maxson[maxn];
bool vis[maxn];
int dis[maxn];      // dis[]存储到根节点的距离
int dist[maxn];  // dist[] 用于排序
int total;
ll ans;

void init(int n) {
    tot = 0;
    total = n;
    ans = 0;
    for(int i = 0; i <= n; ++i) {
        head[i] = - 1;
        vis[i] = 0;
    }
}

inline void addedge(int u, int v, int w) {
    edge[tot] = {v, head[u], w};
    head[u] = tot++;
}

void getroot(int u, int fa) {
    siz[u] = 1, maxson[u] = 0;
    for(int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if(v == fa || vis[v]) continue ;
        getroot(v, u);
        siz[u] += siz[v];
        maxson[u] = max(maxson[u], siz[v]);
    }
    maxson[u] = max(maxson[u], total - siz[u]);
    if(maxson[u] < maxson[root]) root = u;
}

void getdis(int u, int fa) {
    dist[++dist[0]] = dis[u];
    for(int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if(v == fa || vis[v]) continue ;
        dis[v] = dis[u] + edge[i].w;
        getdis(v, u);
    }
}

ll calc(int u, ll init) {
    dist[0] = 0;
    dis[u] = init;
    getdis(u, 0);
    sort(dist + 1, dist + dist[0] + 1);
    ll res = 0;
    for(int l = 1, r = dist[0]; l < r; ){
        if(dist[l] + dist[r] <= k) {
            res += r - l;
            ++l;
        } else {
            --r;
        }
    }
    return res;
}

void solve(int u) {
    ans += calc(u, 0);
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(!vis[v]) {
            ans -= calc(v, edge[i].w);
            maxson[u] = total = siz[v];
            getroot(v, root = 0);
            solve(root);
        }
    }
}

int main() {
    int u, v, w;
    while(~scanf("%d%d",&n,&k)) {
        if(!n && !k) break ;
        init(n);
        for(int i = 1; i < n; ++i){
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        root = 0;
        maxson[root] = n;
        getroot(1, root);
        ans = 0;
        solve(root);
        printf("%lld\n", ans);
    }
    return 0;
}

