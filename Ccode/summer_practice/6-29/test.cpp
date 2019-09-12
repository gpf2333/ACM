#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;
ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}
inline bool check(ll m, ll l, ll r){
    return (m >= l && m <= r);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll l, r, x, y;
    cin >> l >> r >> x >> y;
    ll n = y / x;
    if(y % x){
        puts("0");
        return 0;
    }
    if(n == 1){
        if(x >= l && x <= r){
            puts("1");
        }else{
            puts("0");
        }
        return 0;
    }
    ll up = sqrt((double)n), ans = 0;
    for(int i = 1; i <= up; ++i){
        if(n % i == 0){
            ll p = i, q = n / i;
            if(gcd(p, q) > 1) continue ;
            if(check(p * x, l, r) && check(q * x, l, r)) ans += 2;
        }
    }
    cout << ans << endl;
    return 0;
}