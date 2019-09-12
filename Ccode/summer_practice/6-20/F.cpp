#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;

ll fast_pow(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    const ll inv3 = fast_pow(3, mod - 2);
    int T;
    ll n, m;
    cin >> T;
    while(T--){
        cin >> n >> m;
        ll tmp = (fast_pow(2, n) - 1 + mod) % mod;
        ll ans = 2LL * fast_pow(tmp, m - 1) % mod;
        if(n & 1) ans = (ans + 1 + mod) % mod;
        ans = ans * inv3 % mod;
        cout << ans << endl;
    }
    return 0;
}
