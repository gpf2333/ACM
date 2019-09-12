#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
int prime[maxn], mu[maxn];
bool isprime[maxn];
int cntp;
void init(){
    memset(isprime, true, sizeof(isprime));
    isprime[0] = isprime[1] = false;
    mu[0] = mu[1] = 1;
    cntp = 0;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            mu[i] = -1;
        }
        for(int j = 1;  j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                break ;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

ll fast_pow(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1)   res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll cnt[maxn];
int main(){
    init();
    int T, n, kase = 0;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(cnt, 0, sizeof(cnt));
        int x, maxx = 0, minn = INF;
        ll ans = 1;
        for(int i = 1; i <= n; ++i){
            scanf("%d",&x);
            maxx = max(x, maxx);
            minn = min(x, minn);
            ans = ans * x % mod;
            ++cnt[x];
        }
        for(int i = 2; i < maxn; ++i){
            cnt[i] += cnt[i - 1];
        }
        ll tmp = 0;
        for(int i = 1;i <= minn; ++i){
            if(!mu[i]){
                continue ;
            }
            ll res = 1;
            for(int l = i, k = 1; l <= maxx; l += i, ++k){
                int r = min(maxx, l + i - 1);
                res = res * fast_pow(k, cnt[r] - cnt[l - 1]) % mod;
            }
            res = (res * mu[i] % mod + mod) % mod;
            tmp = (tmp + res) % mod;
        }
        ans = ((ans - tmp) % mod + mod) % mod;
        printf("Case #%d: %lld\n", ++kase, ans);
    }
    return 0;
}