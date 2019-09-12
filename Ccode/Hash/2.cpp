#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 10;
const int mod = 1004535809;
const int mod1 = 1e9 + 7;
struct Edge {
    int to, next;
    pair<int, int>w;
}edge[maxn << 1];

int tot, head[maxn];
bool vis[maxn];
map<pair<int, int>, int>mp;

int fast_pow(int a, int b, int mod) {
    int res = 1;
    while(b > 0) {
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

void init(int n) {
    tot = 0;
    for(int i = 0; i <= n; ++i) {
        head[i] = -1;
        vis[i] = 0;
    }
    mp.clear();
}

inline void addedge(int u, int v, int fir, int sec) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].w.first = fir;
    edge[tot].w.second = sec;
    head[u] = tot++;
}

void dfs(int u, int fir, int sec) {
    ++mp[make_pair(fir, sec)];
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if(vis[v]) continue ;
        dfs(v, fir ^ edge[i].w.first, sec ^ edge[i].w.second);
    }
}

int main() {
    int u, v, w;
    int n;
    scanf("%d",&n);
    init(n);
    for(int i = 1; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        int fir = fast_pow(2, w, mod);
        int sec = fast_pow(2, w, mod1);
        addedge(u, v, fir, sec);
        addedge(v, u, fir, sec);
    }
    dfs(1, 0, 0);
    ll tmp = 0;
    for(auto it : mp){
        tmp += (ll)it.second * (it.second - 1);
    }
    tmp /= 2;
    ll ans = (ll)n * (n - 1) / 2 - tmp;
    printf("%lld\n", ans);
    return 0;
}