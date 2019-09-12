#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
#define pll pair<long long, long long>
pair<ll, ll>dp[65][65][65];
bool vis[65][65][65];
int a[70];
int pw[70];
ll v;

pll dfs(int pos, bool limit, int sta){
    if(pos == -1){
        return make_pair(sta == v, 0);
    }
    if(sta + pos + 1 < v){
        return make_pair(0, 0);
    }
    if(!limit && vis[v][pos][sta]){
        return dp[v][pos][sta];
    }
    int up = limit ? a[pos] : 1;
    pll res = make_pair(0, 0);
    for(int i = 0; i <= up; ++i){
        if(sta == v && i == 1) continue ;
        pll tmp = dfs(pos - 1, limit && i == up, sta + (i == 1));
        res.first += tmp.first;
        res.second = (res.second + (tmp.first % mod * (ll)i % mod * pw[pos] % mod) + tmp.second) % mod;
    }
    if(!limit){
        vis[v][pos][sta] = 1, dp[v][pos][sta] = res;
    }
    return res;
}

pll solve(ll x){
    int pos = 0;
    while(x){
        a[pos++] = (x & 1);
        x >>= 1;
    }
    if(pos < v){
        return make_pair(0, 0);
    }
    return dfs(pos - 1, 1, 0);
}

int main(){
    memset(vis, 0, sizeof(vis));
    pw[0] = 1;
    for(int i = 1; i <= 63; ++i){
        pw[i] = pw[i - 1] * 2LL % mod;
    }
    ll l, r;
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%lld%lld", &l, &r, &v);
        if(v >= 64){
            printf("0 0\n");
            continue ;
        }
        pll tmp1 = solve(r), tmp2 = solve(l - 1);
        ll cnt = tmp1.first - tmp2.first;
        ll sum = (tmp1.second - tmp2.second + mod) % mod;
        printf("%lld %lld\n", cnt, sum);
    }
    return 0;
}