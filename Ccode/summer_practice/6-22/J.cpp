#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
const int INF = 0x3f3f3f3f;
vector<int>G[maxn];
int up = 19, d[maxn], f[maxn][21];
void init(int n){
    for(int i = 0; i <= n; ++i){
        G[i].clear();
        d[i] = 0;
    }
}

void bfs(int u){
    queue<int>q;
    q.push(u);
    d[u] = 1;
    while(!q.empty()){
        u = q.front(); q.pop();
        for(int i = 0; i < G[u].size(); ++i){
            int v = G[u][i];
            if(d[v]) continue ;
            d[v] = d[u] + 1;
            f[v][0] = u;
            for(int j = 1; j <= up; ++j){
                f[v][j] = f[f[v][j - 1]][j - 1];
            }
            q.push(v);
        }
    }
}

int lca(int x, int y){
    if(d[x] > d[y]) swap(x, y);
    for(int i = up; i >= 0; --i){
        if(d[f[y][i]] >= d[x]) y = f[y][i];
    }
    if(x == y) return x;
    for(int i = up; i >= 0; --i){
        if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}

int a[maxn], LCA[maxn];

int main(){
    int n, k, u, v;
    while(~scanf("%d%d",&n,&k)){
        init(n);
        vector<vector<int> >dp(n + 5, vector<int>(k + 5, 0));
        for(int i = 1; i <= n; ++i){
            scanf("%d",&a[i]);
        }
        for(int i = 1; i < n; ++i){
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        bfs(1);
        for(int i = 2; i <= n; ++i){
            LCA[i] = d[lca(a[i - 1], a[i])];
        }
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <= min(i, k); ++j){
                int tmp = INF;
                if(i - 1 >= j){
                    tmp = min(tmp, dp[i - 1][j]);
                }
                if(i >= 2 &&  (i - 2 >= j - 1)){
                    tmp = min(tmp, dp[i - 2][j - 1] + LCA[i]);
                }
                tmp = min(tmp, dp[i - 1][j - 1] + d[a[i]]);
                dp[i][j] = tmp;
            }
        }
        printf("%d\n", dp[n][k]);
    }
    return 0;
}