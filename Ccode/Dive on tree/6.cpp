#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
struct Edge{
    int to, next, w;
}edge[maxn << 1];
map<int, int>mp;
int tot, head[maxn];
bool vis[maxn];

void init(int n){
    tot = 0;
    mp.clear();
    for(int i = 0; i <= n; ++i){
        head[i] = -1, vis[i] = 0;
    }
}

inline void addedge(int u, int v, int w){
    edge[tot] = {v, head[u], w};
    head[u] = tot++;
}

void dfs(int u, int dis){
    ++mp[dis];
    vis[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        if(vis[edge[i].to]) continue ;
        dfs(edge[i].to, edge[i].w ^ dis);
    }
}

int main(){
    int T, n, q, s;
    int u, v, w;
    scanf("%d",&T);
    while(T--){
        scanf("%d", &n);
        init(n);
        for(int i = 1; i < n; ++i){
            scanf("%d%d%d", &u, &v, &w);
            addedge(u, v, w);
            addedge(v, u, w);
        }
        dfs(1, 0);
        scanf("%d", &q);
        while(q--){
            scanf("%d", &s);
            ll ans = 0;
            for(auto it: mp){
                if(!s){
                    ans += (ll)it.second * (it.second - 1);
                }else if(mp.count(s ^ it.first)){
                    ans += (ll)it.second * mp[s ^ it.first];
                }
            }
            ans /= 2LL;
            if(!s) ans += n;
            printf("%lld\n", ans);
        }
    }
    return 0;
}