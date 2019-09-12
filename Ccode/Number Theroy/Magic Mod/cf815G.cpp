#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e6 + 10;
const int mod = 1e9 + 7;
bool isprime[maxn];
int cntp, prime[maxn], mu[maxn];
int pw[maxn];
int b[maxn];

int qpow(int a, int b, int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

void init(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[0] = isprime[1] = 0;
    mu[1] = 1;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0; break ;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

int main(){
    init();
    int n, k;
    scanf("%d%d", &n, &k);
    pw[0] = b[0] = 0;
    for(int i = 1; i <= k; ++i) pw[i] = qpow(i, n, mod);
    ll ans = 0;
    for(int i = 1; i <= k; ++i){
        for(int j = i; j <= k; j += i){
            b[j] = (b[j] + (ll)mu[i] * (pw[j / i] - pw[j / i - 1]) % mod) % mod;
        }
        b[i] = (b[i] + b[i - 1]) % mod; 
        if(b[i] < 0) b[i] += mod;
        ans = (ans + ((ll)b[i] ^ i) % mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}