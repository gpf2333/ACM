#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;

int n;
vector<int>G[maxn];
vector<int>vec;
bool vis[maxn];
int siz[maxn];
ll dis[maxn];
ll ans = 0;

void init(int n){
    ans = 0;
    for(int i = 0; i <= n; ++i){
        G[i].clear();
        vis[i] = 0, dis[i] = 0;
    }
    vec.clear();
}

void getsize(int u, int fa, int rt, int d){
    vis[u] = 1, siz[u] = 1;
    vec.push_back(u);
    for(int v : G[u]){
        if(v == fa) continue ; 
        getsize(v, u, rt, d + 1);
        siz[u] += siz[v];
        dis[rt] += d + 1;
    }
}

void getdis(int u, int fa){
    for(int v : G[u]){
        if(v == fa) continue ;
        dis[v] = dis[u] - siz[v] + (vec.size() - siz[v]);
        getdis(v, u);
    }
}

void getsiz(int u, int fa){
    siz[u] = 1;
    for(int v : G[u]){
        if(v == fa) continue ;
        getsiz(v, u);
        siz[u] += siz[v];
    }
}

void dfs(int u, int fa){
    for(int v : G[u]){
        if(v == fa) continue ;
        dfs(v, u);
        ans += (ll)siz[v] * (n - siz[v]);
    }
}

bool cmp(const int x, const int y){
    return dis[x] < dis[y];
}

int main(){
    while(~scanf("%d",&n)){
        init(n);
        int u, v, up = n - 2;
        for(int i = 0; i < up; ++i){
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        } 
        u = v = 0;
        for(int i = 1; i <= n; ++i){
            if(!vis[i]){
                getsize(i, -1, i, 0);
                getdis(i, -1);
                sort(vec.begin(), vec.end(), cmp);
                if(!u){
                    u = vec[0];
                }else{
                    v = vec[0];
                }
                vec.clear();
            }
            if(u && v) break ;
        }
        G[u].push_back(v);
        G[v].push_back(u);
        getsiz(1, -1);
        dfs(1, -1);
        printf("%lld\n", ans);
    }
    return 0;
}