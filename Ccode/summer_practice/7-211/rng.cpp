#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1e6 + 5;

int inv[maxn], sum[maxn];
ll fast_pow(ll a, int b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init(){
    inv[0] = 1;
    sum[1] = inv[1] = 1;
    for(int i = 2; i < maxn; ++i){
        inv[i] = (ll)(mod - mod / i) * (ll)inv[mod % i] % mod;
        sum[i] = (sum[i - 1] + inv[i]) % mod;
    }
}

int main(){
    init();
    int n;
    while(~scanf("%d", &n)){
        ll ans = (ll)(n + 3LL) * fast_pow(4LL * n, mod - 2) % mod;
        ll res = 0, tmp;
        for(int i = 1; i <= n; ++i){
            tmp = ((sum[n] - sum[i]) + mod) % mod;
            res = (res + i * tmp % mod) % mod;
        }
        tmp = fast_pow((ll)n * n % mod, mod - 2);
        res = (res * tmp) % mod;
        ans = (ans + res) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}