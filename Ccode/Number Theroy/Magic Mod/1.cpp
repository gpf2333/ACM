#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll qpow(ll a, int b, int mod){
    ll res = 1;
   while(b > 0){
       if(b & 1) res = res * a % mod;
       a = a * a % mod;
       b >>= 1;
   }
   return res;
}

const int inv6 = qpow(6, mod - 2, mod);

inline ll f2(ll n){
    return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
}

ll calc(ll n){
    ll ans = n * (n + 1) / 2LL % mod * n % mod, res = 0;
    for(ll l = 1, r; l <= n; l = r + 1){
        r = n / (n / l);
        res = (res + (f2(r) - f2(l - 1) % mod + mod) % mod * (n / l) % mod) % mod;
    }
    ans = ((ans - res) % mod + mod) % mod;
    return ans;
}

int main(){
    ll n, m;
    while(cin >> n >> m){
        cout << calc(n) * calc(m) % mod << endl;
    }
    return 0;
}