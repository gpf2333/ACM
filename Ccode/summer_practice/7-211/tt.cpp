#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll fast_pow(ll a, ll b){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

const ll inv6 = fast_pow(6, mod - 2);
const ll inv2 = fast_pow(2, mod - 2);

inline ll f(ll n){
    return n * (n + 1) % mod * (2LL * n % mod + 1LL) % mod * inv6 % mod;
}

ll calc(ll n){
    ll sq = sqrt(n);
    ll up = n / (sq + 1);
    ll res = 0;
    for(ll i = 1; i <= up; ++i){
        res = (res + i * i % mod * (n / i) % mod) % mod;
    }
    for(ll i = 1; i <= sq; ++i){
        ll tmp = ((f(n / i) - f(n / (i + 1))) % mod + mod) % mod;
        res = (res + i * tmp % mod) % mod;
    }
    return res;
}

ll get(ll n){
    ll res = (ll)n * n % mod * (n + 1LL) % mod * inv2 % mod;
    res = ((res - calc(n)) % mod + mod) % mod;
    return res;
}

int main(){
    ll n, m;
    while(cin >> n >> m){
        ll ans = get(n) * get(m) % mod;
        cout << ans << endl;
    }
    return 0;
}