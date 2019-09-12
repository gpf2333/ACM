#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;
int n;
int col[maxn], son[maxn], siz[maxn], cnt[maxn];
int mx, Son;
ll sum, ans[maxn];
vector<int>G[maxn];

void init(int n){
    sum = 0, mx = -1;
    for(int i = 0; i <= n; ++i){
        G[i].clear();
        cnt[i] = 0;
        ans[i] = 0;
        son[i] = 0;
    }
}

void dfs_size(int u, int fa){
    siz[u] = 1;
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa) continue ;
        dfs_size(v, u);
        siz[u] += siz[v];
        if(son[u] == 0 || siz[v] > siz[son[u]]){
            son[u] = v;
        }
    }
}

void add(int u, int fa, int val){
    cnt[col[u]] += val;
    if(cnt[col[u]] > mx){
        mx = cnt[col[u]], sum = col[u];
    }else if(cnt[col[u]] == mx){
        sum += col[u];
    }
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa || v == Son) continue ;
        add(v, u, val);
    }
}

void dfs_dsu(int u, int fa, int opt){
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa || v == son[u]) continue ;
        dfs_dsu(v, u, 0);
    }
    if(son[u]){
        dfs_dsu(son[u], u, 1);
        Son = son[u];
    }
    add(u, fa, 1);
    ans[u] = sum;
    if(son[u]){
        Son = 0;
    }
    if(!opt){
        add(u, fa, -1);
        sum = 0, mx = -1;
    }
}

int main(){
    int u, v;
    scanf("%d", &n);
    init(n);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &col[i]);
    }
    for(int i = 1; i < n; ++i){
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs_size(1, 0);
    dfs_dsu(1, 0, 0);
    for(int i = 1; i <= n; ++i){
        printf("%I64d%c", ans[i], (i == n) ? '\n' : ' ');
    }
    return 0;
}