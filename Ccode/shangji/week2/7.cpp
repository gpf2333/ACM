#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
const int maxm = 1000 + 5;
struct Edge{
    int from, to, next;
};
Edge edge[maxm];
int tot, head[maxn];
int in[maxn];
int topans[maxn];

void init(){
    tot = 0;
    memset(head, -1, sizeof(head));
    memset(in, 0, sizeof(in));
}

inline void addedge(const int u, const int v){
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void topsort(const int n){
    int len = 0;
    queue<int>q;
    for(int i = 1; i <= n; ++i){
        if(!in[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int cur = q.front(); q.pop();
        topans[len++] = cur;
        for(int i = head[cur]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if(--in[v] == 0){
                q.push(v);
            }
        }
    }
    if(len >= n){
        for(int i = 0; i < len; ++i){
            printf("%d ", topans[i]);
        }
        puts("");
    } else {
        printf("拓扑排序不存在");
    }
}

int main(){
    ios::sync_with_stdio(false);
    int n, m;
    while(cin >> n >> m){
        int u,v;
        init();
        for(int i = 0; i  < m; ++i){
            cin >> u >> v;
            addedge(u, v);
            ++in[v];
        }
        topsort(n);
    }
    return 0;
}

/*
9 11
1 3
3 4
4 6
4 7
2 3
2 4
2 5
5 6
1 8
8 9
9 7
*/