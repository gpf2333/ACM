#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mul(ll a, ll b, ll mod){
    ll res = 0;
    while(b > 0){
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

//solve ax + by = 1
ll exgcd(ll a, ll b, ll &x, ll &y){
    if(!b){
        x = 1, y = 0;
        return  a;
    }
    ll d = exgcd(b, a % b, x, y);
    ll t = x;
    x = y, y = t - (a / b) * y;
    return d;
}

//solve ax + by = c return x; // x > 0
ll solve(ll a, ll b, ll c){
    ll x, y;
    ll d = exgcd(a, b, x, y);
    if(c % d) return -1;
    ll tmp = b / d;
    x = mul(x, c / d, tmp); //note!!!
    return (x % tmp + tmp) % tmp;
}

int main(){
    return 0;
}