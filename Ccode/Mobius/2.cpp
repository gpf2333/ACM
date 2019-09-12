#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e7 + 100;
int prime[maxn], mu[maxn], f[maxn], cntp;
bool isprime[maxn];
void init(){
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    mu[1] = 1, f[0] = cntp = 0;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
            f[i] = 1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                f[i * prime[j]] = mu[i];
                break ;
            }
            mu[i * prime[j]] = -mu[i];
            f[i * prime[j]] = -f[i] + mu[i];
        }
    }
    for(int i = 1; i < maxn; ++i){
        f[i] += f[i - 1];
    }
}

ll calc(int n, int m){
    if(n > m) swap(n, m);
    ll ans = 0;
    for(int l = 1, r; l <= n; l = r + 1){
        r = min(n / (n / l), m / (m / l));
        ans += ((ll)(f[r] - f[l - 1]) * (ll)(n / l) * (ll)(m / l));
    }
    return ans;
}


int main(){
    init();
    int T, n, m;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        printf("%lld\n", calc(n, m));
    }
    return 0;
}