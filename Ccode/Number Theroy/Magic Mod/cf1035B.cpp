#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll calc(ll n){
    for(int i = 2; (ll)i * i <= n; ++i){
        if(n % i == 0) return i; 
    }
    return n;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    ll a, b;
    cin >> a >> b;
    ll c, d;
    for(int i = 2; i <= n; ++i){
        cin >> c >> d;
        a = __gcd(a, c * d);
        b = __gcd(b, c * d);
    }
    if(max(a, b) > 1){
        cout << calc(max(a, b)) << endl;
    }else{
        cout << -1 << endl;
    }
    return 0;
}