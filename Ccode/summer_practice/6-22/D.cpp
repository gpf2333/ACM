#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 100;
const int INF = 2147483647;
int tot,head[maxn],dis[maxn];
bool vis[maxn];
struct Node{
    int to, w, next;
}edge[maxn<<1];

int siz[maxn],we[maxn];


void init(){
    tot = 0;
    memset(head,-1,sizeof(head));
    memset(we, 0, sizeof(we));
    memset(siz, 0, sizeof(siz));
}

inline void addedge(int u, int v, int w){
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs(int u){
    siz[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next){
        int v = edge[i].to;
        we[v] = edge[i].w;
        dfs(v);
        siz[u] += siz[v];
    }
}



int main(){
    int n, k;
    while(~scanf("%d%d", &n, &k)){
        init();
        int u, v, w;
        for(int i = 1; i < n; ++i){
            scanf("%d%d%d",&u,&v, &w);
            addedge(u, v, w);
        }
        dfs(1);
        ll ans = 0;
        for(int i = 2; i <= n; ++i){
            ans += (ll)we[i] * min(siz[i], k);
        }
        printf("%lld\n", ans);
    }
    return 0;
}