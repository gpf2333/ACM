#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 5e6 + 10;

bool isprime[maxn + 5];
int prime[maxn], cntp;
int phi[maxn];

int qpow(int a, int b, int mod){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

const int inv2 = qpow(2, mod - 2, mod);
const int inv6 = qpow(6, mod - 2, mod);

void init(){
    memset(isprime, 1, sizeof(isprime));
    cntp = isprime[0] = isprime[1] = 0;
    phi[1] = 1;
    for(int i = 2; i < maxn; ++i){
        if(isprime[i]){
            prime[++cntp] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= cntp && i * prime[j] < maxn; ++j){
            isprime[i * prime[j]] = 0;
            if(i % prime[j] == 0){
                phi[i * prime[j]] = phi[i] * prime[j];
                break ;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for(int i = 1; i < maxn; ++i){
        phi[i] = (phi[i - 1] + (ll)phi[i] * i % mod) % mod;
    }
}

inline int f1(int n){
    return ((ll)n * (n + 1) / 2) % mod;
}

inline int f2(int n){
    return (ll)n * (n + 1) % mod * (2LL * n + 1) % mod * (ll)inv6 % mod;
}

unordered_map<int, int>mp;
int calc(int n){
    if(n < maxn) return phi[n];
    if(mp.count(n)) return mp[n];
    int res = f2(n);
    for(int l = 2, r; l <= n; l = r + 1){
        r = n / (n / l);
        int tmp = (f1(r) - f1(l - 1) % mod + mod) % mod;
        tmp = (ll)tmp * calc(n / l) % mod;
        res = ((res - tmp) % mod + mod) % mod;
    }
    return (mp[n] = res);
}

int main(){
    init();
    mp.clear();
    int T;
    int n, a, b;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d", &n, &a, &b);
        int ans = calc(n);
        ans = ((ans - (ll)(ans + 1) * inv2 % mod) % mod + mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}