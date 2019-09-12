#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 950;
vector<int> G[maxn], sp;
int dep[maxn], dfn[maxn];
pair<int, int> dp[11][maxn << 1];
int ans[maxn];
bool in[maxn];
void init(int n){
    for(int i = 0; i <= n; ++i){
        G[i].clear();
        dep[i] = 0;
        ans[i] = 0;
        in[i] = 0;
    }
    sp.clear(); 
}

inline void addedge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
}

void dfs(int u, int fa){
    dep[u] = dep[fa] + 1;
    dfn[u] = sp.size();
    sp.push_back(u);
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa) continue ;
        dfs(v, u);
        sp.push_back(u);
    }
}

void initrmq(){
    int n = sp.size();
    for(int i = 0; i < n; ++i){
        dp[0][i] = {dfn[sp[i]], sp[i]};
    }
    for(int i = 1; (1 << i) <= n; ++i){
        for(int j = 0; j + (1 << i) -1 < n; ++j){
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int lca(int u, int v){
    int l = dfn[u], r = dfn[v];
    if(l > r) swap(l, r);
    int k = 31 - __builtin_clz(r - l + 1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]).second;
}

int main(){
    int n, m, u, v, x;
    while(~scanf("%d", &n)){
        init(n);
        bool flag = 0;
        for(int i = 0; i < n; ++i){
            scanf("%d:(%d)", &u, &x);
            while(x){
                --x;
                scanf("%d", &v);
                in[v] = 1;
                addedge(u, v);
            }
        }
        for(int i = 1; i <= n; ++i){
            if(!in[i]){
                dfs(i, 0); break ; //需要从根节点开始访问
            }
        }
        initrmq();
        scanf("%d", &m);
        while(m--){
            scanf(" (%d %d)", &u, &v);
            if(u == v) ++ans[u];
            else ++ans[lca(u, v)];
        }
        for(int i = 1; i <= n; ++i){
            if(ans[i]){
                printf("%d:%d\n", i, ans[i]);
            }
        }
    }
    return 0;
}