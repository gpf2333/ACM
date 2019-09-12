#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;
bool isprime[maxn];
int cntp, prime[maxn], mu[maxn];
int sum[maxn];

void init(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[0] = isprime[1] = 0;
    mu[1] = 1;
    sum[0] = 0;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i, mu[i] = -1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0 ;
                break ; 
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
    memset(sum, 0, sizeof(sum));
    for(int i = 1; i < maxn; ++i){
        for(int j = i; j < maxn; j += i){
            sum[j] += mu[i] * mu[j / i];
        }
    }
}

int main(){
    init();
    int T, n, m;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        int up = min(n, m);
        ll ans = 0;
        for(int i = 1; i <= up; ++i){
            ll tmp1 = 0;
            for(int j = i; j <= n; j += i){
                tmp1 += mu[j];
            }
            ll tmp2 = 0;
            for(int j = i; j <= m; j += i){
                tmp2 += mu[j];
            }
            ans += tmp1 * tmp2 * sum[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}