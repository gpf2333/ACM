#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll w;
struct tf{
    ll p, d;
    tf(ll pp = 0, ll dd = 0):p(pp),d(dd){}
};

inline ll Mod(ll a, ll p){
    a %= p;
    if(a < 0) a += p;
    return a;
}

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
        if(b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

inline ll Legendre(ll a, ll p){
    return qpow(a, (p - 1) >> 1, p);
}

tf mul(const tf &a, const tf &b, ll mod){
    tf ans;
    ans.p = (mul(a.p, b.p, mod) + mul(w, mul(a.d, b.d, mod), mod)) % mod;
    ans.d = (mul(a.p, b.d, mod) + mul(a.d, b.p, mod)) % mod;
    return ans;
}

tf qpow(tf a, ll b, ll mod){
    tf res(1, 0);
    while(b > 0){
        if(b & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

ll Sqrt(ll n, ll p){
    if(p == 2) return 1;
    if(Legendre(n, p) + 1 == p) return -1;
    int a;
    srand(time(0));
    while(1){
        a = rand() % p;
        w = Mod((ll)a * a - n, p);
        if(Legendre(w, p) + 1 == p) break ;
    }
    tf tmp(a, 1);
    tf ans = qpow(tmp, (p + 1) >> 1, p);
    return ans.p;
}

int main(){
    int T;
    ll n, x, p;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%lld", &p, &x);
        
    }
    return 0;
}