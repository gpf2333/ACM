#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50000 + 100;
bool isprime[maxn];
int prime[maxn], cntp, mu[maxn], g[maxn];

int get(int n){
    int res = 0;
    for(int l = 1, r; l <= n; l = r + 1){
        r = n / (n / l);
        res += (n / l) * (r - l + 1);
    }
    return res;
}

void init(){
    cntp = 0;
    memset(isprime, 1, sizeof(isprime));
    isprime[1] = isprime[0] = 0;
    mu[1] = 1;
    mu[0] = 0;
    for(int i = 2; i < maxn;  ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(!(i % prime[j])){
                mu[i * prime[j]] = 0;
                break ;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    g[0] = 0, g[1] = 1;
    for(int i = 2; i < maxn; ++i){
        mu[i] += mu[i - 1];
        g[i] = get(i);
    }
}

ll calc(int n, int m){
    if(n > m) swap(n, m);
    ll res = 0;
    for(int l = 1, r; l <= n; l = r + 1){
        r = min(n / (n / l), m / (m / l));
        res += (ll)(mu[r] - mu[l - 1]) * g[n / l] * (ll)g[m / l];
    }
    return res;
}

int main(){
    init();
    int T, n, m;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d", &n, &m);
        printf("%lld\n", calc(n, m));
    }
    return 0;
}