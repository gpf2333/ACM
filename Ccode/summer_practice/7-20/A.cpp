#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, root, total;
vector<int>G[maxn];
bool vis[maxn];
int siz[maxn], maxson[maxn];
ll ans;

void init(int n){
    for(int i = 0; i <= n; ++i){
        G[i].clear();
        vis[i] = 0;
        maxson[i] = 0;
    }
}

void getsiz(int u, int fa, int &sum){
    ++sum;
    vis[u] = 1;
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa || vis[v]) continue ;
        getsiz(v, u, sum);
    }
}

void getroot(int u, int fa) {
    siz[u] = 1, maxson[u] = 0;
    for(int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if(v == fa) continue ;
        getroot(v, u);
        siz[u] += siz[v];
        maxson[u] = max(maxson[u], siz[v]);
    }
    maxson[u] = max(maxson[u], total - siz[u]);
    if(maxson[u] < maxson[root]){ 
        root = u;
    }
}

void get(int u, int fa){
    siz[u] = 1;
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa) continue ;
        get(v, u);
        siz[u] += siz[v];
    }
}

void dfs(int u, int fa){
    for(int i = 0; i < G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa) continue ;
        dfs(v, u);
        siz[u] += siz[v];
        //ans += (ll)(siz[v] * (n - siz[v]));
    }
    ans += 1LL * (siz[u] * (n - siz[u]));
}

int main(){
    while(~scanf("%d", &n)){
        int u, v, up = n - 2;
        init(n);
        for(int i = 0; i < up; ++i){
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        int sum1 = 0, sum2 = 0;
        getsiz(1, -1, sum1);
        for(int i = 1; i <= n; ++i){
            if(!vis[i]){
                v = i;
                getsiz(i, -1, sum2);
                break ;
            }
        }
        total = sum1;
        root = 0;
        maxson[root] = sum1;
        getroot(1, root);
        u = root;

        total = sum2;
        root = 0;
        maxson[root] = sum2;
        getroot(v, root);
        v = root;

        G[u].push_back(v);
        G[v].push_back(u);
        ans = 0;
        get(1, -1);
        dfs(1, -1);
        printf("%lld\n", ans);
    }
    return 0;
}