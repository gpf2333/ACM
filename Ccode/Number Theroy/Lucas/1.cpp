#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;

ll mul(ll a, ll b, ll mod){
    ll res = 0;
    while(b > 0){
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ll qpow(ll a, ll b, ll mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int fac[maxn], inv[maxn];
void init(int mod){
    fac[0] = inv[0] = inv[1] = fac[1] = 1;
    for(int i = 2; i < mod; ++i) fac[i] = (ll)i * fac[i - 1] % mod;
    inv[mod - 1] = qpow(fac[mod - 1], mod - 2, mod);
    for(int i = mod - 2; i >=0; --i){
        inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
    }
}

ll lucas(ll n, ll m, ll p){
    ll res = 1;
    while(n && m){
        ll a = n % p, b = m % p;
        if(a < b) return 0;
        res = res * fac[a] % p * inv[b] % p * inv[a - b] % p;
        n /= p, m /= p;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y){
    ll d = a;
    if(b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}

void crt(ll r[], ll m[], ll n, ll &re, ll &mo){
    mo = 1, re = 0;
    for(int i = 0; i < n; ++i){
        mo *= m[i];
    }
    for(int i = 0; i < n; ++i){
        ll x, y, tm = mo / m[i];
        exgcd(tm, m[i], x, y);
        x = (x % mo + mo) % mo;
        re = (re + mul(tm, mul(x, r[i], mo), mo)) % mo;
    }
    re = (re + mo) % mo; 
}

int main(){
    ll r[20], p[20];
    int T, k;
    ll m, n;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%lld%d", &n, &m, &k);
        for(int i = 0; i < k; ++i){
            scanf("%lld", &p[i]);
            init(p[i]);
            r[i] = lucas(n, m, p[i]);
        }
        ll re, mo;
        crt(r, p, k, re, mo);
        printf("%lld\n", re);
    }
    return 0;
}