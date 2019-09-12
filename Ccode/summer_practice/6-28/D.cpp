#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;
int cntp, prime[maxn], mu[maxn];
bool isprime[maxn];
void init(){
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    mu[1] = 1;
    cntp = 0;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                break ;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

ll fast_pow(ll a, ll b, ll mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll calc(ll n, ll mod){
    ll inv4 = fast_pow(4LL, mod - 2, mod);
    ll res = 0;
    ll ntwo = n * n % mod;
    ll up = n / 2;
    for(int i = 1; i <= up; ++i){
        if(!mu[i]) continue ;
        ll tmp = ntwo * inv4 % mod * fast_pow(i * i, mod - 2, mod) % mod * ((n / i) - 1) % mod;
        tmp = (tmp * mu[i] % mod + mod) % mod;
        res = (res + tmp) % mod;
    }
    res = (res + (n * (n + 1) % mod))% mod;
    res = res *  fast_pow(3, n, mod) % mod;
    return res;
}

int main(){
    init();
    int t;
    ll n, mod;
    scanf("%d",&t);
    while(t--){
        scanf("%lld%lld",&n,&mod);
        printf("%lld\n", calc(n, mod) % mod);
    }
    return 0;
}