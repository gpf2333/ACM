#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e6 + 50;

int mod, inv4, inv6;

int qpow(int a, int b, int mod){
    int res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}

bool isprime[maxn];
int cntp, prime[maxn], phi[maxn];
void init(int mod){
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
        phi[i] = (phi[i - 1] + (ll)phi[i] * i % mod * i % mod) % mod; //note!!!
    }
}

inline int f2(ll n){
    return n % mod * (n + 1) % mod * (2LL * n % mod + 1LL) % mod * inv6 % mod;
}

inline int f3(ll n){
    int res = n % mod * (n + 1) % mod;
    return (ll)res * res % mod * inv4 % mod;
}

unordered_map<ll, int>mp;
int calc(ll n){
    if(n < maxn) return phi[n];
    if(mp.count(n)) return mp[n];
    int res = f3(n);
    for(ll l = 2, r; l <= n; l = r + 1){
        r = n / (n / l);
        int tmp = ((f2(r) - f2(l - 1)) % mod + mod) % mod;
        tmp = (ll)calc(n / l) * tmp % mod;
        res = ((res - tmp) % mod + mod) % mod;
    }
    return mp[n] = res;
}

int solve(ll n){
    int res = 0;
    for(ll l = 1, r; l <= n; l = r + 1){
        r = n / (n / l);
        int tmp = ((calc(r) - calc(l - 1) % mod) + mod) % mod;
        tmp = (ll)tmp * f3(n / l) % mod;
        res = (res + tmp) % mod;
    }
    return res;
}

int main(){
    ll n;
    scanf("%d%lld", &mod, &n);
    inv4 = qpow(4, mod - 2, mod), inv6 = qpow(6, mod - 2, mod);
    init(mod); 
    mp.clear();
    printf("%d\n", solve(n));
    return 0;
}