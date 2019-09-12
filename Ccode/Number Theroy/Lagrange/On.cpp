#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1e6 + 10;

int x[maxn], y[maxn];
int pl[maxn], pr[maxn], ifac[maxn];

int qpow(int a, int b, int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

//o(n) note:: x 是连续的一段取值且mod是奇素数
int lagrange(int n, int x[], int y[], int xi){
    int ans = 0;
    pl[0] = (xi - x[0]) % mod;
    pr[n + 1] = ifac[0] = ifac[1] = 1;
    for(int i = 1; i <= n; ++i) pl[i] = (ll)pl[i - 1] * (xi - x[i]) % mod;
    for(int i = n; i >= 0; --i) pr[i] = (ll)pr[i + 1] * (xi - x[i]) % mod;
    for(int i = 2; i <= n; ++i) ifac[i] = (mod - mod / i) * (ll)ifac[mod % i] % mod;
    for(int i = 2; i <= n; ++i) ifac[i] = (ll)ifac[i] * ifac[i - 1] % mod;
    for(int i = 0; i <= n; ++i){
        (ans += (ll)y[i] * (i ? pl[i - 1] : 1LL) % mod * pr[i + 1] % mod 
        * ifac[i] % mod * (((n - i ) & 1) ? -1 : 1) * (ll)ifac[n - i] % mod) %= mod;
    }
    ans = (ans + mod) % mod;
    return ans;
}

int main(){
    for(int i = 0; i < maxn; ++i) x[i] = (i + 1);
    int n, k;
    scanf("%d%d", &n, &k);
    y[0] = 1;
    for(int i = 1; i <= k + 1; ++i){
        y[i] = (qpow(i + 1, k, mod) + y[i - 1]) % mod;
    }
    printf("%d\n", lagrange(k + 1, x, y, n));
    return 0;
}