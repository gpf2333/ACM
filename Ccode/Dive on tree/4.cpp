#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 20000 + 5;
const int mod = 3;
struct Edge{
    int to, next, w;
}edge[maxn << 1];

int n, root, total;
int head[maxn], tot;
int siz[maxn], maxson[maxn];
bool vis[maxn];
int dis[4];
int ans;

void init(int n){
    tot = 0, total = n; ans = 0;
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
    ++dis[d];
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(v == fa || vis[v]) continue ;
        getdis(v, u, (d + edge[i].w) % mod);
    }
}

int calc(int u, int init){
    memset(dis, 0, sizeof(dis));
    getdis(u, 0, init);
    return dis[0] * dis[0] + 2 * dis[1] * dis[2];
}

void solve(int u){
    ans += calc(u, 0);
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        if(vis[v]) continue ;
        ans -= calc(v, edge[i].w % mod);
        maxson[0] = total = siz[v];
        getroot(v, root = 0);
        solve(root);
    }
}

int gcd(int a, int b){
    return b == 0 ? a : gcd(b, a % b);
}

int main(){
    int u, v, w;
    scanf("%d", &n);
    init(n);
    for(int i = 1; i < n; ++i){
        scanf("%d%d%d", &u, &v, &w);
        w %= mod;
        addedge(u, v, w);
        addedge(v, u, w);
    }
    root = 0, ans = 0;
    maxson[root] = n;
    getroot(1, root);
    solve(root);
    int d = gcd(ans, n * n);
    printf("%d/%d\n", ans / d, n * n / d);
    return 0;
}