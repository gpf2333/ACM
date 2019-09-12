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
int dis[maxn];
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

void getroot(int u, int fa) { // 求重心
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

void getdis(int u, int fa, int d) { //求距离,根据具体题目需要修改
    dis[++dis[0]] = d;
    for(int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if(v == fa || vis[v]) continue ;
        getdis(v, u, d + edge[i].w);
    }
}

ll calc(int u, int init) { //根据具体题目进行修改
    dis[0] = 0;
    getdis(u, 0, init);
    sort(dis + 1, dis + dis[0] + 1);
    ll res = 0;
    for(int l = 1, r = dis[0]; l < r; ){
        if(dis[l] + dis[r] <= k) {
            res += r - l;
            ++l;
        } else {
            --r;
        }
    }
    return res;
}

void solve(int u) { //根据具体题目进行修改
    ans += calc(u, 0);
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(!vis[v]) {
            ans -= calc(v, edge[i].w);
            maxson[0] = total = siz[v];
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
        root = 0; //根初始化，本题中根节点编号为1
        maxson[root] = n; //根节点大小初始化
        getroot(1, root);
        ans = 0;
        solve(root);
        printf("%lld\n", ans);
    }
    return 0;
}