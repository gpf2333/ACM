#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
bool isprime[maxn];
int prime[maxn], cntp, mu[maxn], phi[maxn];
int d[maxn], e[maxn],  g[maxn]; //d正除数个数, e最小质因子个数

void init(){
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    cntp = 0, mu[1] = phi[1] = d[1] = 1;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
            phi[i] = i - 1;
            e[i] = 1, d[i] = 2;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                phi[i * prime[j]] = phi[i] * prime[j];
                e[i * prime[j]] = e[i] + 1;
                d[i * prime[j]] = d[i] / (e[i] + 1) * (e[i] + 2);
                break ;
            }
            mu[i * prime[j]] = -mu[i];
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            e[i * prime[j]] = 1;
            d[i * prime[j]] = 2 * d[i];
        }
    }
    g[1] = 1;
    for(int i = 2; i < maxn; ++i){
        g[i] = (g[i - 1] + d[i - 1] + 1) % mod;
    }
    for(int i = 1; i < maxn; ++i){
        g[i] = (g[i] + g[i - 1]) % mod;
        mu[i] = (mu[i] + mu[i - 1]);
    }
}

ll calc(int n){
    ll res = 0;
    for(int l = 1, r; l <= n; l = r + 1){
        r = n / (n / l);
        ll tmp = ((mu[r] - mu[l - 1]) + mod) % mod;
        tmp = tmp * g[n / l] % mod;
        res = (res + tmp) % mod;
    }
    return res;
}

int main(){
    init();
    int n;
    while(~scanf("%d",&n)){
        printf("%lld\n", calc(n));
    }
    return 0;
}