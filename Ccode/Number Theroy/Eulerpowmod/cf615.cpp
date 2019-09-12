#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int phi = mod - 1;
const int maxn = 2e5 + 10;
int pre[maxn], suf[maxn];
map<int, int>mp;
int fac[maxn][2];

ll qpow(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; ++i){
        int x;
        scanf("%d", &x);
        ++mp[x];
        pre[i] = suf[i] = 1;
    }
    pre[m] = suf[m] = 1;
    pre[m + 1] = suf[m + 1] = 1;
    int cnt = 0;
    for(auto &it: mp){
        fac[++cnt][0] = it.first;
        fac[cnt][1] = it.second; 
    }
    for(int i = 1; i <= cnt; ++i){
        pre[i] = (ll)pre[i - 1] * (fac[i][1] + 1) % phi;
    }
    for(int i = cnt; i >= 1; --i){
        suf[i] = (ll)suf[i + 1] * (fac[i][1] + 1) % phi;
    }
    ll ans = 1;
    for(int i = 1; i <= cnt; ++i){
        ll tmp = (ll)pre[i - 1] * suf[i + 1] % phi;
        tmp = tmp * ((ll)fac[i][1] * (fac[i][1] + 1) / 2 % phi) % phi;
        tmp = (tmp + phi);
        ans = ans * qpow(fac[i][0], tmp) % mod;
    }
    printf("%lld\n", ans);
    return 0;  
}