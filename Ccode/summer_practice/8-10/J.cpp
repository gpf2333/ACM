#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define Mod(a, mod) (a % mod + mod) % mod
const int maxn = 1e7 + 10;
const int mod = 998244353;
 
int qpow(int a, int b, int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}
 
int fac[maxn], invf[maxn];
void calcfact(){
    fac[0] = 1;
    for(int i = 1; i < maxn; ++i) fac[i] = (ll)fac[i - 1] * i % mod;
    invf[maxn - 1] = qpow(fac[maxn - 1], mod - 2, mod);
    for(int i = maxn - 2; ~i; --i){
        invf[i] = (ll)invf[i + 1] * (i + 1) % mod;
    }
}
 
inline int C(ll n, ll m){
    if(n < m || n < 0 || m < 0) return 0;
    return (ll)fac[n] * invf[m] % mod * (ll)invf[n - m] % mod;
}
 
struct Node{
    int t, p;
}a[maxn];
 
bool cmp(const Node &a, const Node &b){
    if(a.t == b.t) return a. p < b.p;
    return a.t < b.t;
}
 
int dp[maxn], sum[maxn];
int g[3005][2];
 
int main(){
    calcfact();
    int L, d, m;
    scanf("%d%d%d", &L, &d, &m);
    for(int i = 1; i <= m; ++i){
        scanf("%d%d", &a[i].t, &a[i].p);
    }
    a[0].t = a[0].p  = 0;  
    sort(a + 1, a + m + 1, cmp);
    dp[0] = 1, sum[0] = dp[0];
    for(int i = 1; i <= L; ++i){
        dp[i] = (i < d) ? 0 : sum[i - d];
        sum[i] = (sum[i - 1] + dp[i]) % mod;
    }
    ll ans = dp[L];
    g[0][0] = 1;
    for(int i = 1; i <= m; ++i){
        for(int j = 0; j < i; ++j){
            int tmpt = a[i].t - a[j].t;
            int tmpp = a[i].p - a[j].p;
            if(tmpt < 0 || tmpp - (ll)tmpt * d < 0) continue ;
            int tmp = C(tmpp - (ll)tmpt * d + tmpt - 1, tmpt - 1);
            g[i][0] = (g[i][0] + (ll)g[j][1] * tmp % mod) % mod;
            g[i][1] = (g[i][1] + (ll)g[j][0] * tmp % mod) % mod;
        }
        ans = (ans + (ll)Mod(g[i][0]- g[i][1], mod) * dp[L - a[i].p] % mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}