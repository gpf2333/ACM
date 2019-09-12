#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;
const int mod = 1e9 + 7;
const int mod1 = 1004535809;
map<pair<int, int>, int>mp;

int fast_pow(int a, int b, const int mod) {
    int res = 1;
    while(b > 0) {
        if(b & 1) res = (ll)res * a % mod;
        a = (ll) a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    mp.clear();
    int n, x;
    scanf("%d",&n);
    int fir = 0, sec = 0;
    ++mp[make_pair(fir, sec)];
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        fir ^= fast_pow(2, x, mod), 
        sec ^= fast_pow(2, x, mod1);
        ++mp[make_pair(fir, sec)];
    }
    ll ans = 0;
    for(auto it : mp) {
        ans += ((ll)it.second * (it.second - 1) / 2);
    }
    printf("%lld\n", ans);
    return 0;
}