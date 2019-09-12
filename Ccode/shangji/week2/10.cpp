#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
struct Edge{
    int from, to, next, w;
}edge[maxn << 1];
int head[maxn], tot;

bool cmp(const Edge &a, const Edge &b){
    return a.w < b.w;
}

void init(){
    tot = 0;
    memset(head, -1, sizeof(head));
}

inline void addedge(const int u, const int v, const int w){
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].w = w;
    head[u] = tot++;
}

int fa[maxn], Rank[maxn];
int Find(int x){
    return (x == fa[x]) ? x : (fa[x] = Find(fa[x]));
}

bool Unite(int x, int y){
    x = Find(x), y = Find(y);
    if(x != y){
       if(Rank[x] > Rank[y]){
           fa[y] = x;
       } else{
           fa[x] = y;
           if(Rank[x] == Rank[y]) ++Rank[x];
       }
        // fa[y] = x;
        return true;
    }
    return false;
}

bool Isconnect(const int n, const int m){
    if(m < n- 1) return false;
    for(int i = 0; i <= n; ++i) fa[i] = i;
    int cnt = 0;
    for(int i = 0; i < m; ++i){
        if(Unite(edge[i].from, edge[i].to)){
            if(++cnt == n - 1) return true;
        }
    }
    return false;
}

void solve(const int n, const int m){
    sort(edge, edge + m, cmp);
    if(!Isconnect(n, m)){
        puts("Not MST");
        return ;
    }
    int cnt = 1;
    while(Isconnect(n, m - cnt)){
        printf("Delete %d edge(s): (%d,  %d,  %d)\n", cnt, edge[m - cnt].from, edge[m - cnt].to, edge[m - cnt].w);
        ++cnt;
    }
    printf("Delete %d edges(s)\n", cnt);
}

int main(){
    ios::sync_with_stdio(false);
    int n, m;
    while(cin >> n >> m){
        int u, v, w;
        init();
        for(int i = 0; i < m; ++i){
            cin >> u >> v >> w;
            addedge(u, v, w);
        }
        solve(n, m);
    }
    return 0;
}

/*
6 8
0 1 34
0 2 46
0 3 19
1 4 12
2 4 26
2 5 25
4 5 38
3 5 17
*/
