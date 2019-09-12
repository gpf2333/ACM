#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int maxn = 1e4 + 50;
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

int cnt[maxn];
int sum[maxn];


ll get(int n){
    return (ll)n * (ll)(n - 1) * (ll)(n - 2) * (n - 3) / 24LL;
}

int main(){
    int n;
    init();
    while(~scanf("%d", &n)){
        memset(cnt, 0, sizeof(cnt));
        memset(sum, 0, sizeof(cnt));
        int x, maxx = -1;
        for(int i = 1; i <= n; ++i){
            scanf("%d", &x);
            maxx = max(maxx, x);
            ++cnt[x];
        }
        for(int i = 1; i <= maxx; ++i){
            for(int j = i; j <= maxx; j += i){
                sum[i] += cnt[j];
            }
        }
        ll ans = 0;
        for(int i = 1; i <= maxx; ++i){
            if(!mu[i]) continue ;
            ans = (ans + (ll)mu[i] * get(sum[i]));
        }
        printf("%lld\n", ans);
    }
    return 0;
}