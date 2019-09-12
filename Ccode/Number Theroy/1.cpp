#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 10;
map<int ,int>mp;
ll qpow(ll a, ll b, int mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, x;
    cin >> n >> x;
    ll sum = 0;
    mp.clear();
    int mx = 0;
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        sum += a;
        mx = max(mx, a);
        ++mp[a];
    }
    int i = mx;
    while(mp[i] % x == 0){
        mp[i - 1] += mp[i] / x;
        --i;
    }
    if(i < 0) i = 0;
    ll ans = qpow(x, sum - i, mod);
    cout << ans << endl;
    return 0;
}