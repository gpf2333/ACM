#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 50;
vector<vector<int> >G(maxn);
int c[maxn], siz[maxn], sum[maxn];
void init(int n){
    for(int i = 0; i <= n; ++i){
        G[i].clear();
        c[i] = siz[i] = sum[i] = 0;
    }
}

void dfs(int u, int fa, ll &ans){
    siz[u] = 1;
    int temp = 0;
    for(int i = 0; i < (int)G[u].size(); ++i){
        int v = G[u][i];
        if(v == fa) continue ;
        int last = sum[c[u]];
        dfs(v, u, ans);
        siz[u] += siz[v];
        int tmp = siz[v] - (sum[c[u]] - last);
        ans -= (ll)tmp * (ll)(tmp - 1) / 2LL;
        temp += tmp;
    }
    sum[c[u]] += (temp + 1);

}

int main(){
    int n, kase = 0;
    while(~scanf("%d",&n)){
        init(n);
        for(int i = 1; i <= n; ++i){
            scanf("%d", &c[i]);
        }
        int u, v;
        for(int i = 1; i < n; ++i){
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        ll ans = (ll) n * (ll) n * (ll)(n - 1) / 2LL;
        dfs(1, -1, ans);
        for(int i = 1; i <= n; ++i){
            ans -= (ll)(n - sum[i]) * (ll)(n - sum[i] - 1) / 2LL;
        }
        printf("Case #%d: %lld\n", ++kase, ans);
    }
    return 0;
}