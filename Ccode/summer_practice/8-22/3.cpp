#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int, int>mp1, mp2;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    mp1.clear();
    mp2.clear();
    int n, p, k;
    cin >> n >> p >> k;
    for(int i = 0; i < n; ++i){
        int x;
        cin >> x;
        ++mp2[x];
        int tmp1 = (ll)x * x % p * (ll)x % p;
        int tmp2 = (ll)k * x % p;
        tmp1 = ((ll)tmp1 - tmp2 + p) % p;
        ++mp1[tmp1];
    }
    ll ans = 0;
    for(auto it = mp1.begin(); it != mp1.end(); ++it){
        ll tmp = it->second;
        ans += tmp * (tmp - 1) / 2;
    }
    for(auto it = mp2.begin(); it != mp2.end(); ++it){
        ll t = it->first;
        t = 3 * t * t % p;
        if(t == k) continue ;
        ll tmp = it->second;
        ans -= tmp * (tmp - 1) / 2;
    }
    cout << ans << endl;
    return 0;
}