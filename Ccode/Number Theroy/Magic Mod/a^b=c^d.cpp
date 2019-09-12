#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
ll gcd(ll a, ll b){
    return b ? gcd(b, a % b) : a;
}
ll qpow(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
ll solve(ll a, ll b, ll c, ll d){
    ll res = b * d % mod; // a = c, b * d
    for(int i = 1; i < 32; ++i){
        for(int j = 1; j < 32; ++j){
            if(gcd(i, j) != 1) continue ;
            ll tmpa = qpow(a, 1.0 / i);
            ll tmpc = qpow(c, 1.0 / j);
            while(qpow(tmpa, i) <= a) ++tmpa;
            while(qpow(tmpc, j) <= c) ++tmpc;
            --tmpa, --tmpc;
            res = (res + min(tmpa - 1, tmpc - 1) * min(b / j, d / i) % mod) % mod; // note -1
        }
    }
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << solve(a, b, c, d) << endl;
    }
    return 0;
}