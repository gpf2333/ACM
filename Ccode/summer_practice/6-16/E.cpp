#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
struct edge{
    int to, next;
}edge[maxn], invedge[maxn];
int head[maxn], tot, invhead[maxn], invtot;
int ind[maxn];
int c[maxn];
int topv[maxn];
double dp[maxn][2];
void init(int n){
    tot = invtot = 0;
    for(int i = 0; i <= n; ++i){
        head[i] = invhead[i] = -1;
        ind[i] = 0;
        dp[i][0] = dp[i][1] = 0.0;
    }
}

inline void addedge(const int u, const int v){
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
    invedge[invtot].to = u;
    invedge[invtot].next = invhead[v];
    invhead[v] = invtot++;
}

void solve(int n){
    int cnt = 0;
    std::queue<int>q;
    for(int i = 0; i < n; ++i){
        if(!ind[i]){
            q.push(i);
            topv[cnt++] = i;
        }
        dp[i][1] = c[i];
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i = head[u]; ~i; i = edge[i].next){
            int v = edge[i].to;
            if(--ind[v] == 0){
                q.push(v);
                topv[cnt++] = v;
            }
        }
    }
    for(int i = cnt - 1; i >= 0; --i){
        int u = topv[i];
        for(int j = invhead[u]; ~j; j = invedge[j].next){
            int v = invedge[j].to;
            dp[v][0] = max(dp[v][0], max(dp[u][0], dp[u][1]));
            dp[v][1] = max(dp[v][1], max(dp[u][0] / 2.0 + (double)c[v], dp[u][1] / 2.0 + (double)c[v]));
        }
    }
    double ans = max(dp[0][0], dp[0][1]);
    printf("%.6lf\n", ans);
}

int main(){
    int n, m;
    scanf("%d%d",&n, &m);
    for(int i = 0; i < n; ++i){
        scanf("%d", &c[i]);
    }
    init(n);
    int u,v;
    for(int i = 0; i < m; ++i){
        scanf("%d%d",&u, &v);
        addedge(u, v);
        ++ind[v];
    }
    solve(n);
    return 0;
}