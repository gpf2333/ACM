#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll qpow(ll a, ll b, int mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll calc(int n){
    ll tmp1 = 1, tmp2 = 1;
    for(int i = 1, j = n + 1; i <= n; ++i, ++j){
        tmp1 = tmp1 * i % mod;
        tmp2 = tmp2 * j % mod;
    }
    tmp2 = tmp2 * qpow(tmp1, mod - 2, mod) % mod;
    ll res = qpow(2, 2 * n + 1, mod);
    res = qpow(res, mod - 2, mod);
    res = res * tmp2 % mod;
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int a, b;
    cin >> a >> b;
    ll ans = qpow(qpow(a, 2 * b - 1, mod), mod - 2, mod);
    ans = ans * calc(b - 1) % mod;
    cout << ans << endl;
    return 0;
}