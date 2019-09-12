#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll calc(ll n, ll m){
    ll tmp1 = 0, tmp2 = 0, res = 0;
    if(m & 1){
        tmp1 += ((m >> 1) + 1);
    }else{
        tmp1 += (m >> 1);
    }
    if(n - 2 >= (n / 3) * 3){
        tmp2 += (n / 3 + 1);
    }else{
        tmp2 += n / 3;
    }
    res = tmp1 * tmp2;
    if(n % 3 == 1){
        res += m / 3;
        if(m - 2 >= (m / 3) * 3)  ++res;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n, m;
    while(cin >> n >> m){
        if(n == m && (n % 2) == 0){
            cout << 2LL * (n - 2) << endl;
            continue ;
        }
        ll ans =  max(calc(n, m), calc(m, n));
        cout << ans << endl;
    }
    return 0;
}