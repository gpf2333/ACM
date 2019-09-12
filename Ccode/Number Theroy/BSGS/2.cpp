#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

unordered_map<ll, int>mp;
ll qpow(ll a, ll b, ll mod){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

ll exbsgs(ll a, ll b, ll c){
    a %= c, b %= c;
    if(b == 1) return 0;
    int cnt = 0;
    ll t = 1;
    for(int d = gcd(a, c); d != 1; d = gcd(a, c)){
        if(b % d) return -1;
        c /= d, b /= d;
        t = (a / d * t) % c;
        ++cnt;
        if(b == t) return cnt; 
    }
    mp.clear();
    int m = ceil(sqrt((double)c));
    ll base = b;
    for(int i = 0; i < m; ++i){
        mp[base] = i;
        base = base * a % c;
    }
    base = qpow(a, m, c);
    ll tmp = t;
    for(int i = 1; i <= m + 1; ++i){
        tmp = base * tmp % c;
        if(mp.count(tmp)){
            return (ll)i * m - mp[tmp] + cnt;
        }
    }
    return -1;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int a, b, m;
        scanf("%d%d%d",&a, &b, &m);
        ll ans = exbsgs(a, b, m);
        printf("%lld\n", ans);
    }
    return 0;
}