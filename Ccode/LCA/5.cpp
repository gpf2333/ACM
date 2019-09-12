#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 50000 + 500;
int val[maxn], dep[maxn];
int len,f[maxn][20], up[maxn][20], down[maxn][20], Min[maxn][20], Max[maxn][20];
vector<int>G[maxn];

void init(int n){
    len = 0;
    while((1 << len) <= n) ++len;
    for(int i = 0; i <= n; ++i){
        G[i].clear();
    }
}

void dfs(int u, int fa, int d){
    dep[u] = d;
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa) continue ;
        f[v][0] = u;
        Max[v][0] = max(val[u], val[v]);
        Min[v][0] = min(val[u], val[v]);
        up[v][0] = max(0, val[u] - val[v]);
        down[v][0] = max(0, val[v] - val[u]);
        dfs(v, u, d + 1);
    }
}

void getf(int n){
    for(int j = 1; j <= len; ++j){
        for(int i = 1; i <= n; ++i){
            if(f[i][j - 1] < 0){
                f[i][j - 1] = -1;
                continue;
            }
            f[i][j] = f[f[i][j - 1]][j - 1];
            Max[i][j] = max(Max[i][j - 1], Max[f[i][j - 1]][j - 1]);
            Min[i][j] = min(Min[i][j - 1], Min[f[i][j - 1]][j - 1]);
            up[i][j] = max(up[i][j - 1], up[f[i][j - 1]][j]);
            up[i][j] = max(up[i][j], Max[f[i][j - 1]][j - 1] - Min[i][j - 1]);
            down[i][j] = max(down[i][j - 1], down[f[i][j - 1]][j - 1]);
            down[i][j] = max(down[i][j], Max[i][j - 1] - Min[f[i][j - 1]][j - 1]);
        }
    }
}

int lca(int u, int v){
    int res = 0, minn = val[u], maxx = val[v];
    if(dep[u] > dep[v]){
        for(int i = 0; i <= len; ++i){
            if((dep[u] - dep[v]) & (1 << i)){
                res = max(res, max(up[u][i], Max[u][i] - minn));
                minn = min(minn, Min[u][i]);
                u = f[u][i];
            }
        }
    }else{
        for(int i = 0; i <= len; ++i){
            if((dep[v] - dep[u]) & (1 << i)){
                res = max(res, max(down[v][i], maxx - Min[v][i]));
                maxx = max(maxx, Max[v][i]);
                v = f[v][i];
            }
        }
    }
    if(u != v){
        for(int i = len; i >= 0; --i){
            if(f[u][i] != f[v][i]){
                res = max(res, max(up[u][i], Max[u][i] - minn));
                minn = min(minn, Min[u][i]);
                res = max(res, max(down[v][i], maxx - Min[v][i]));
                maxx = max(maxx, Max[v][i]);
                u = f[u][i], v = f[v][i];
            }
        }
        minn = min(minn, f[u][0]);
        maxx = max(maxx, f[v][0]);
    }
    res = max(res, maxx - minn);
    printf("%d\n", res);
    return f[u][0];
}

int main(){
    int n;
    while(~scanf("%d",&n)){
        init(n);
        for(int i = 1; i <= n; ++i){
            scanf("%d",&val[i]);
        }
        int u, v;
        for(int i = 1; i < n; ++i){
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        f[1][0] = -1;
        dfs(1, -1, 1);
        getf(n);
        int Q;
        scanf("%d",&Q);
        while(Q--){
            scanf("%d%d", &u, &v);
            lca(u, v);
        }
    }
    return 0;
}