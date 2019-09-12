#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll>fac;
void calc(ll n){
    fac.clear();
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i ==0){
            fac.push_back(i);
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) fac.push_back(n);
}

ll solve(ll x){
    if(x <= 0) return 0;
    int n = fac.size();
    int up = (1 << n);
    ll res = x;
    for(int i = 1; i < up; ++i){
        ll tmp = 1;
        for(int j = 0; j < n; ++j){
            if(i & (1 << j)) tmp *= fac[j];
        }
        if(__builtin_parity(i)) res -= x / tmp;
        else res += x / tmp;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll l, r, k;
    cin >> l >> r >> k;
    ll x = 2 * k;
    r -= x;
    if(l > r){
        cout << 0 << endl;
        return 0;
    }   
    calc(x);
    ll ans = solve(r) - solve(l - 1);
    cout << ans << endl;
    return 0;
}