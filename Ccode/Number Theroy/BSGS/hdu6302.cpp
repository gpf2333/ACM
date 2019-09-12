#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

ll mul(ll x, ll y, ll mod){
    return (x * y - (ll)((long double)x * y / mod) * mod + mod) % mod;
}

ll qpow(ll a, ll b, ll mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = mul(res , a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}

unordered_map<ll, ll>prime_root;
bool is_prime_root(ll p, ll x){
    if((p - 1) % 2 == 0 && qpow(x, (p - 1) / 2, p) == 1) return 0;
    if((p - 1) % 3 == 0 && qpow(x, (p - 1) / 3, p) == 1) return 0;
    return 1;
}

ll get_prime_root(ll p){
    for(ll i = 2; ; ++i){
        if(is_prime_root(p, i)) return prime_root[p] = i;
    }
}

unordered_map<ll, pii>power23;
pii getpower23(ll p){
    if(power23.count(p)) return power23[p];
    pii ret{0, 0};
    ll res = p - 1;
    while(res % 2 == 0){
        ++ret.first, res /= 2;
    }
    while(res % 3 == 0){
        ++ret.second, res /= 3;
    }
    return ret;
}

ll get_power(ll g, ll x, ll p, pii pp){
    ll phi = p - 1;
    ll tmp = g;
    ll res = 0, pw = 1;
    for(int i = 0; i < pp.first; ++i){
        phi /= 2;
        if(qpow(x, phi, p) != 1){
            x = mul(x, tmp, p);
            res += pw;
        }
        pw *= 2;
        tmp = mul(tmp, tmp, p);
    }
    for(int i = 0; i < pp.second; ++i){
        phi /= 3;
        if(qpow(x, phi, p) != 1){
            x = mul(x, tmp, p);
            res += pw;
            if(qpow(x, phi, p) != 1){
                x = mul(x, tmp, p);
                res += pw;
            }
        }
        pw *= 3;
        tmp = mul(tmp, mul(tmp, tmp, p), p);
    }
    res = (p - 1 - res) % (p - 1);
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y){
    if(!b){
        x = 1, y = 0;
        return  a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y, y = t - (a / b) * y;
    return d;
}

//solve ax + by = c return x; // x > 0
ll solve(ll a, ll b, ll c){
    ll x, y;
    ll d = exgcd(a, b, x, y);
    if(c % d) return -1;
    ll tmp = b / d;
    x = mul(x, c / d, tmp); //note!!!
    return (x % tmp + tmp) % tmp;
}

int main(){
    prime_root.clear(); power23.clear();
    ll p, a, b;
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%lld%lld", &p, &a, &b);
        ll g;
        if(prime_root.count(p)) g = prime_root[p];
        else g = get_prime_root(p);
        pii pp = getpower23(p);
        a = get_power(g, a, p, pp);
        b = get_power(g, b, p, pp);
        if(!a){
            if(!b){
                puts("1"); continue ;
            }else{
                puts("-1"); continue ;
            }
        }else{
            // cout << 2 << " "  << a << " " << b << " " << endl;
            printf("%lld\n", solve(a, p - 1, b));
        }
    }
    return 0;
}